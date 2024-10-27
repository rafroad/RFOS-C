#include "fs.h"
#include <string.h>

// Reads the FAT32 HEADER information from a buffer
void readHeader(struct FAT32_HEADER *hdr,  const unsigned char buffer[512])
{
    memcpy(hdr->OEM_NAME, buffer+0x03, 8);

    hdr->A_BF_BPB_BytesPerSector    = *(DW*)(buffer + 0x0B);
    hdr->A_BF_BPB_SectorsPerCluster = *(DB*)(buffer + 0x0D);
    hdr->A_BF_BPB_ReservedSectors   = *(DW*)(buffer + 0x0E);
    hdr->A_BF_BPB_NumberOfFATs      = *(DB*)(buffer + 0x10);
    hdr->A_BF_BPB_RootEntries       = *(DW*)(buffer + 0x11);
    hdr->A_BF_BPB_TotalSectors      = *(DW*)(buffer + 0x13);
    hdr->A_BF_BPB_MediaDescriptor   = *(DB*)(buffer + 0x15);
    hdr->A_BF_BPB_SectorsPerFAT     = *(DW*)(buffer + 0x16);
    hdr->A_BF_BPB_SectorsPerTrack   = *(DW*)(buffer + 0x18);
    hdr->A_BF_BPB_Heads             = *(DW*)(buffer + 0x1A);
    hdr->A_BF_BPB_HiddenSectors     = *(DD*)(buffer + 0x1C);
    hdr->A_BF_BPB_BigTotalSectors   = *(DD*)(buffer + 0x20);
    hdr->A_BF_BPB_BigSectorsPerFat  = *(DD*)(buffer + 0x24);
    hdr->A_BF_BPB_ExtFlags          = *(DW*)(buffer + 0x28);
    hdr->A_BF_BPB_FS_Version        = *(DW*)(buffer + 0x2A);
    hdr->A_BF_BPB_RootDirStrtClus   = *(DD*)(buffer + 0x2C);
    hdr->A_BF_BPB_FSInfoSec         = *(DW*)(buffer + 0x30);
    hdr->A_BF_BPB_BkUpBootSec       = *(DW*)(buffer + 0x32);
    hdr->A_BF_BPB_Reserved1         = *(DW*)(buffer + 0x34);
    hdr->A_BF_BPB_Reserved2         = *(DW*)(buffer + 0x38);
    hdr->A_BF_BPB_Reserved3         = *(DW*)(buffer + 0x3C);
    hdr->A_BF_BPB_DriveNum          = *(DB*)(buffer + 0x40);
    hdr->A_BF_BPB_Reserved4         = *(DB*)(buffer + 0x41);
    hdr->A_BF_BPB_Signature         = *(DB*)(buffer + 0x42);
    hdr->A_BF_BPB_VolumeID          = *(DD*)(buffer + 0x43);

    memcpy(hdr->A_BF_BPB_VolumeLabel, buffer+0x47, 11);
    memcpy(hdr->A_BF_BPB_FAT_Name,    buffer+0x52, 8);

    hdr->LBA_FAT_Location        = *(DD*)(buffer + 0x5A);
    hdr->LBA_Cluster_Location    = *(DD*)(buffer + 0x5E);
    hdr->Scale_SectorsPerCluster = *(DB*)(buffer + 0x62);
    hdr->Mask_SectorRotation     = *(DB*)(buffer + 0x63);
}
#define OFFSET_ATTRIB 0x0B
#define OFFSET_CLUS_HI 0x14
#define OFFSET_CLUS_LO 0x1A
#define OFFSET_SIZE 0x1C
#define FLAG_LFN 0x0F

const char LFN_idxs[] = {1,3,5,7,9,14,16,18,20,22,24,28,30};

struct FAT32_HEADER fileSys;

int  FATSecIdx=-1;
unsigned int  FATBuffer[128];

int  ClusterSecIdx=-1;
unsigned char ClusterBuffer[2048];

char sysPath[256];

struct File currentDir;
int dirClusterIndex=-1;

// Identifies if a drive exists and selects it
// Uses ATA PIO mode with command ECh
bool identify()
{
	char status=-1;
	char buffer[512];

	outportb(0x1F6, 0xA0);	// Set Master Drive (0xA0) or Slave Drive (0xB0)
	outportb(0x1F2, 0x00);	// Set Sector count to 0
	outportb(0x1F3, 0x00);	// Set LBA lo to 0
	outportb(0x1F4, 0x00);	// Set LBA mid to 0
	outportb(0x1F5, 0x00);	// Set LBA hi to 0

	outportb(0x1F7, 0xEC);	// Issue IDENTIFY command
	status=inportb(0x1F7);	// Wait and Read status

	// If Status is 0, the drive does not exist
	if(status == 0)
	{	return false;
	}

	// Keep polling untill BSY is cleared
	while ((status & 0x80) != 0)
	{	status = inportb(0x1F7);
	}

	// If LBAmid and LBAhi are non zero, not an ATA drive
	if (inportb(0x1F4)!=0 || inportb(0x1F5)!=0)
	{	return false;
	}

	// Keep polling untill DRQ or ERR are set
	while ((status & 0x09) == 0);
	{	status = inportb(0x1F7);
	}

	// If ERR is clear, read 512 bytes (256 words)
	if((status & 0x01) == 0)
	{	for(long i=0; i<512; i+=2)
		{	*(short*)(buffer+i) = inportb(0x1F0);
		}
		return true;
	}
	return false;
}

// Reads sectors starting from some LBA address into a buffer
// Uses ATA PIO mode with command 20h
bool readSector(short sectors, long LBA, char* buffer)
{
	char status=inportb(0x1F7);

	// Shall be set to one
	outportb(0x1F6, 0x40);

	// Number of sectors to read
	outportb(0x1F2, (sectors & 0xFF));

	// LBA position of the data
	outportb(0x1F3, (LBA & 0xFF));
	outportb(0x1F4, (LBA >> 8 ) & 0xFF);
	outportb(0x1F5, (LBA >> 16 ) & 0xFF);

	// READ SECTOR(S) - 20h
	outportb(0x1F7, 0x20);

    // For S number of sectors
    for(int s = 0; s < sectors; s++)
    {
        // Poll the status while it's BSY, or till DRQ or ERR is set
        status = inportb(0x1F7);
        while ((status & 0x80) != 0 || (status & 0x09) == 0)
        {	status = inportb(0x1F7);
        }

        // If ERR is not set, read the data
        if((status & 0x01) == 0)
        {   for(long i = 0; i < 512; i += 2)
            {*(short*)(buffer+i+s*512) = inportb(0x1F0);
            }
        }
        else
        {   return false;
        }
    }

    return true;
}

// Loads a new sector from the File Allocation Table into the memory
// Updates the index of which sector is loaded
bool load_FATSect(int offset)
{
    int LBA_Sector = fileSys.LBA_FAT_Location + offset;
    if(readSector(1, LBA_Sector, (char*)FATBuffer))
    {   FATSecIdx = offset;
        return true;
    }

    return false;
}

// Loads a new Cluster into the memory
// Updates the index of which cluster is loaded
bool load_Cluster(int index)
{
    int clusterSize = fileSys.A_BF_BPB_SectorsPerCluster;
    int offset      = (index-2) * clusterSize;
    int LBA_Sector  = fileSys.LBA_Cluster_Location + offset;

    if(readSector(clusterSize, LBA_Sector, (char*)ClusterBuffer))
    {   ClusterSecIdx = index;
        return true;
    }

    return false;
}

// Traverses the File Allocation Table to find the clusters
// of a file/directory. Max size of a file is 8 clusters
bool traverseFAT(int startCluster, int clusters[8])
{
    int FAT_offset;
    int cluster_offset;
    clusters[0] = startCluster;

    for(int i=1; i<8; i++)
    {
        if(clusters[i-1] == 0x0FFFFFFF)
        {   break;
        }

        // Load another sector from the FAT if it's out of reach
        // Each Sector contains 128 cluster indexes
        FAT_offset = clusters[i-1] >> 7;
        if(FAT_offset != FATSecIdx)
        {   if(!load_FATSect(FAT_offset))
            {   return false;
            }
        }

        // Set the value of the next cluster using the offset
        // In this sector of the FAT
        cluster_offset = clusters[i-1] & 0x7F;
        clusters[i] = FATBuffer[cluster_offset];
    }

    return true;
}

// Replace the current directory's clusters with a new one
// Reads the first cluster and sets the directory cluster index to 0
bool openDirectory(struct File directory)
{
    if(load_Cluster(directory.clusters[0]))
    {   dirClusterIndex = 0;
        return true;
    }

    return false;
}

// Loads the file system on a drive and opens the Root directory
// by traversing its cluster indexes and loading the first cluster
bool loadFileSystem()
{
    char buffer[512];

    if(identify())
    {
        if(readSector(1, 1, buffer))
        {
            readHeader(&fileSys, buffer);
            if(traverseFAT(fileSys.A_BF_BPB_RootDirStrtClus, currentDir.clusters))
            {
                if(openDirectory(currentDir))
                {   return true;
                }
            }
        }
    }

    return false;
}
