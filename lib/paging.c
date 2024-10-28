#include <stdint.h>
#include <stddef.h>
#include "paging.h"

#define PAGE_SIZE 4096  // Example page size
#define MAX_PAGES 1024  // Example maximum number of pages
#define MAX_REGIONS 256  // Maximum number of tracked regions


static volatile int interrupts_enabled = 1; // Flag for interrupt state
static char memory_pool[MAX_PAGES * PAGE_SIZE]; // Memory pool for allocation
static int pages_allocated = 0; // Track the number of pages currently allocated

struct memory_region {
    void* start_addr;
    int num_pages;
    int in_use;
};

static int num_regions = 0;
static struct memory_region memory_regions[MAX_REGIONS];

static inline void disable_interrupts() {
    asm volatile ("cli"); // Clear interrupt flag (disable interrupts)
    interrupts_enabled = 0;
}
static inline void enable_interrupts() {
    asm volatile ("sti"); // Set interrupt flag (enable interrupts)
    interrupts_enabled = 1;
}
int liballoc_lock() {
    disable_interrupts(); // Lock by disabling interrupts
    return 0; // Success
}
int liballoc_unlock() {
    enable_interrupts(); // Unlock by enabling interrupts
    return 0; // Success
}


// Modified allocation function to track allocations
void* liballoc_alloc(int num_pages) {
    if (num_pages <= 0 || pages_allocated + num_pages > MAX_PAGES || num_regions >= MAX_REGIONS) {
        return NULL;
    }

    void* allocated_memory = (void*)(memory_pool + (pages_allocated * PAGE_SIZE));

    // Record the allocation
    memory_regions[num_regions].start_addr = allocated_memory;
    memory_regions[num_regions].num_pages = num_pages;
    memory_regions[num_regions].in_use = 1;
    num_regions++;

    pages_allocated += num_pages;
    return allocated_memory;
}

// Modified free function to update tracking
int liballoc_free(void* ptr, int num_pages) {
    if (ptr < (void*)memory_pool || ptr >= (void*)(memory_pool + sizeof(memory_pool))) {
        return -1;
    }

    // Find and mark the region as free
    for (int i = 0; i < num_regions; i++) {
        if (memory_regions[i].start_addr == ptr && memory_regions[i].in_use) {
            memory_regions[i].in_use = 0;
            pages_allocated -= num_pages;
            return 0;
        }
    }

    return -1; // Region not found
}

// Initialize tracking system
void liballoc_init() {
    for (int i = 0; i < sizeof(memory_pool); i++) {
        memory_pool[i] = 0;
    }

    for (int i = 0; i < MAX_REGIONS; i++) {
        memory_regions[i].start_addr = NULL;
        memory_regions[i].num_pages = 0;
        memory_regions[i].in_use = 0;
    }

    pages_allocated = 0;
    num_regions = 0;
}

// Function to list all allocated memory regions
void liballoc_dump() {
    liballoc_lock();  // Protect against concurrent access

    printf_("Memory Allocation Map:\n");
    printf_("---------------------\n");
    printf_("Total Pages: %d/%d (Used/Max)\n", pages_allocated, MAX_PAGES);
    printf_("Memory Regions: %d/%d (Used/Max)\n", num_regions, MAX_REGIONS);
    printf_("\nActive Allocations:\n");

    for (int i = 0; i < num_regions; i++) {
        if (memory_regions[i].in_use) {
            size_t start = (size_t)memory_regions[i].start_addr;
            size_t end = start + (memory_regions[i].num_pages * PAGE_SIZE);

            printf_("Region %d:\n", i);
            printf_("  Start: 0x%x\n", start);
            printf_("  End:   0x%x\n", end);
            printf_("  Pages: %d\n", memory_regions[i].num_pages);
            printf_("  Size:  %d bytes\n", memory_regions[i].num_pages * PAGE_SIZE);
            printf_("---------------------\n");
        }
    }

    // Calculate fragmentation
    int free_regions = 0;
    int largest_free_block = 0;
    int current_free_block = 0;

    for (int i = 0; i < num_regions; i++) {
        if (!memory_regions[i].in_use) {
            free_regions++;
            current_free_block += memory_regions[i].num_pages;
        } else {
            if (current_free_block > largest_free_block) {
                largest_free_block = current_free_block;
            }
            current_free_block = 0;
        }
    }

    printf_("\nMemory Statistics:\n");
    printf_("Free Regions: %d\n", free_regions);
    printf_("Largest Free Block: %d pages (%d bytes)\n",
           largest_free_block,
           largest_free_block * PAGE_SIZE);

    liballoc_unlock();
}

// Helper function to get human readable size
void format_size(size_t size, char* buffer) {
    const char* units[] = {"B", "KB", "MB", "GB"};
    int unit = 0;
    double formatted_size = (double)size;

    while (formatted_size >= 1024 && unit < 3) {
        formatted_size /= 1024;
        unit++;
    }

    if (unit == 0) {
        printf_(buffer, "%d B", (int)formatted_size);
    } else {
        printf_(buffer, "%.2f %s", formatted_size, units[unit]);
    }
}

// Function to get a summary of memory usage
void liballoc_status() {
    liballoc_lock();

    size_t total_allocated = pages_allocated * PAGE_SIZE;
    size_t total_available = MAX_PAGES * PAGE_SIZE;
    char allocated_str[32], available_str[32];

    format_size(total_allocated, allocated_str);
    format_size(total_available, available_str);

    printf_("Memory Status:\n");
    printf_("Used:      %s (%d pages)\n", allocated_str, pages_allocated);
    printf_("Available: %s (%d pages)\n", available_str, MAX_PAGES);
    printf_("Usage:     %.1f%%\n",
           (float)pages_allocated / MAX_PAGES * 100);

    liballoc_unlock();
}
