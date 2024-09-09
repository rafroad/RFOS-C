.PHONY: all main

allrun:
	make all
	make run

all:
	make clean
	make kernelmain
	make libc-rel
	make libhelp
	make coresys
	 ~/opt/cross/bin/i686-elf-gcc -T boot/linker.ld -o build/RFOS.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	 cp build/RFOS.bin isodir/boot/RFOS.bin
	 cp build/RFOS.bin isodir/boot/RFOS.bin
	 cp boot/grub.cfg isodir/boot/grub/grub.cfg
	 ~/opt/grub/bin/grub-mkrescue -o RFOS.iso isodir
	# echo "run 'make run' to run qemu"

debug:
	make clean
	~/opt/cross/bin/i686-elf-as boot/boot.s -o build/boot.o
	~/opt/cross/bin/i686-elf-gcc -c kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	make libc-debug
	make libhelp-debug
	make coresys-debug
	~/opt/cross/bin/i686-elf-gcc -T boot/linker.ld -o build/RFOS-debug.bin -ffreestanding -g -nostdlib build/*.o -lgcc -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	echo "run 'make debugrun....' to run qemu "


libc-rel:
	~/opt/cross/bin/i686-elf-gcc -c libc/stdio/printf.c -o build/printf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/stdio/puts.c -o build/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/stdlib/abort.c -o build/abort.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memcmp.c -o build/memcmp.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memcpy.c -o build/memcpy.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memmove.c -o build/memmove.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memset.c -o build/memset.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/strlen.c -o build/strlen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/strcpy.c -o build/strcpy.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include

libc-debug:
	~/opt/cross/bin/i686-elf-gcc -c libc/stdio/printf.c -o build/printf.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/stdio/puts.c -o build/stdio.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/stdlib/abort.c -o build/abort.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memcmp.c -o build/memcmp.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memcpy.c -o build/memcpy.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memmove.c -o build/memmove.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/memset.c -o build/memset.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/strlen.c -o build/strlen.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c libc/string/strcpy.c -o build/strcpy.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include



libhelp:
	~/opt/cross/bin/i686-elf-gcc -c lib/termfunc.c -o build/termfunc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c lib/helper.c -o build/helper.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include

libhelp-debug:
	~/opt/cross/bin/i686-elf-gcc -c lib/termfunc.c -o build/termfunc.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c lib/helper.c -o build/helper.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include


kernelmain:
	~/opt/cross/bin/i686-elf-as boot/boot.s -o build/boot.o
	~/opt/cross/bin/i686-elf-gcc -c kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include

coresys:
	~/opt/nasm/bin/nasm -felf32 lib/isr.s -o build/isr-s.o
	~/opt/cross/bin/i686-elf-gcc -c lib/isr.c -o build/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c lib/idt.c -o build/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c lib/gdt.c -o build/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include

coresys-debug:
	~/opt/nasm/bin/nasm -felf32 lib/isr.s -o build/isr-s.o
	~/opt/cross/bin/i686-elf-gcc -c lib/isr.c -o build/isr.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c lib/idt.c -o build/idt.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include
	~/opt/cross/bin/i686-elf-gcc -c lib/gdt.c -o build/gdt.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./libc/include -I ./lib/include -I ./drivers/include -I ./kernel/include

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
