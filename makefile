.PHONY: all main libc boot
CC = ~/opt/cross/bin/i686-elf-gcc
CFLAGSREL = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I libc/include -I lib/include -I drivers/include -I kernel/include
CFLAGSDEB =	-std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
ASMB = ~/opt/nasm/bin/nasm
LFREL = -ffreestanding -O2 -nostdlib build/*.o -lgcc -I libc/include -I lib/include -I drivers/include -I kernel/include
LFDEB = -ffreestanding -g -nostdlib build/*.o -lgcc -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include

allrun:
	make all
	make run

all:
	make clean
	make boot
	make kernel-rel
	make libc-rel
	make libhelp
	make coresys
	make driver-rel
	$(CC) -T boot/linker.ld -o build/RFOS.bin $(LFREL)
	cp build/RFOS.bin isodir/boot/RFOS.bin
	cp build/RFOS.bin isodir/boot/RFOS.bin
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	~/opt/grub/bin/grub-mkrescue -o RFOS.iso isodir
	#run 'make run' to run qemu

debug:
	make clean
	make boot
	$(CC) -c kernel/kernel.c -o build/kernel.o $(CFLAGSDEB)
	make libc-debug
	make libhelp-debug
	make coresys-debug
	make driver-deb
	$(CC) -T boot/linker.ld -o build/RFOS-debug.bin $(LFDEB)
	#run 'make debugrun....' to run qemu

boot:
	~/opt/cross/bin/i686-elf-as boot/boot.s -o build/boot.o

libc-rel:
	$(CC) -c libc/stdio/printf.c -o build/printf.o $(CFLAGSREL)
	$(CC) -c libc/stdio/puts.c -o build/stdio.o $(CFLAGSREL)
	$(CC) -c libc/stdlib/abort.c -o build/abort.o $(CFLAGSREL)
	$(CC) -c libc/string/memcmp.c -o build/memcmp.o $(CFLAGSREL)
	$(CC) -c libc/string/memcpy.c -o build/memcpy.o $(CFLAGSREL)
	$(CC) -c libc/string/memmove.c -o build/memmove.o $(CFLAGSREL)
	$(CC) -c libc/string/memset.c -o build/memset.o $(CFLAGSREL)
	$(CC) -c libc/string/strlen.c -o build/strlen.o $(CFLAGSREL)
	$(CC) -c libc/string/strcpy.c -o build/strcpy.o $(CFLAGSREL)

libc-debug:
	$(CC) -c libc/stdio/printf.c -o build/printf.o $(CFLAGSDEB)
	$(CC) -c libc/stdio/puts.c -o build/stdio.o $(CFLAGSDEB)
	$(CC) -c libc/stdlib/abort.c -o build/abort.o $(CFLAGSDEB)
	$(CC) -c libc/string/memcmp.c -o build/memcmp.o $(CFLAGSDEB)
	$(CC) -c libc/string/memcpy.c -o build/memcpy.o $(CFLAGSDEB)
	$(CC) -c libc/string/memmove.c -o build/memmove.o $(CFLAGSDEB)
	$(CC) -c libc/string/memset.c -o build/memset.o $(CFLAGSDEB)
	$(CC) -c libc/string/strlen.c -o build/strlen.o $(CFLAGSDEB)
	$(CC) -c libc/string/strcpy.c -o build/strcpy.o $(CFLAGSDEB)

libhelp:
	$(CC) -c lib/termfunc.c -o build/termfunc.o $(CFLAGSREL)
	$(CC) -c lib/helper.c -o build/helper.o $(CFLAGSREL)

libhelp-debug:
	$(CC) -c lib/termfunc.c -o build/termfunc.o $(CFLAGSDEB)
	$(CC) -c lib/helper.c -o build/helper.o $(CFLAGSDEB)

coresys:
	$(ASMB) -felf32 lib/isr.s -o build/isrs.o
	$(CC) -c lib/isr.c -o build/isr.o $(CFLAGSREL)
	$(CC) -c lib/idt.c -o build/idt.o $(CFLAGSREL)
	$(CC) -c lib/gdt.c -o build/gdt.o $(CFLAGSREL)
	$(CC) -c lib/irq.c -o build/irq.o $(CFLAGSREL)
	$(CC) -c lib/pic.c -o build/pic.o $(CFLAGSREL)


coresys-debug:
	$(ASMB) -felf32 lib/isr.s -o build/isrs.o
	$(CC) -c lib/isr.c -o build/isr.o $(CFLAGSDEB)
	$(CC) -c lib/idt.c -o build/idt.o $(CFLAGSDEB)
	$(CC) -c lib/gdt.c -o build/gdt.o $(CFLAGSDEB)
	$(CC) -c lib/irq.c -o build/irq.o $(CFLAGSDEB)
	$(CC) -c lib/pic.c -o build/pic.o $(CFLAGSDEB)

driver-rel:
	$(CC) -c drivers/keyboard.c -o build/keyboard.o $(CFLAGSREL)

driver-deb:
	$(CC) -c drivers/keyboard.c -o build/keyboard.o $(CFLAGSDEB)

kernel-rel:
	$(CC) -c kernel/kernel.c -o build/kernel.o $(CFLAGSREL)
	$(CC) -c kernel/shell.c -o build/shell.o $(CFLAGSREL)

kernel-deb5:
	$(CC) -c kernel/kernel.c -o build/kernel.o $(CFLAGSDEB)
	$(CC) -c kernel/shell.c -o build/shell.o $(CFLAGSDEB)

clean:
	rm -rf build/*.o
	rm -rf build/*.bin
	rm -rf *.sym

cleaniso:
	rm -rf *.iso

run:
	qemu-system-i386 -cdrom RFOS.iso

debugrun:
	make debug
	qemu-system-i386 -s -S -kernel build/RFOS-debug.bin -monitor stdio

debugrunnogdb:
	make debug
	qemu-system-i386 -kernel build/RFOS-debug.bin -monitor stdio
