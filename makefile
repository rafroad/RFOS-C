.PHONY: all main

allrun:
	make all
	make run

all:
	make clean
	make kernelmain
	make libc
	make libhelp
	~/opt/cross/bin/i686-elf-gcc -T boot/linker.ld -o build/RFOS.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/termfunc.o build/helper.o build/printf.o build/stdio.o build/abort.o build/memcmp.o build/memcpy.o build/memmove.o build/memset.o build/strlen.o build/strcpy.o -lgcc -I ./lib/libc/include -I ./lib/include
	cp build/RFOS.bin isodir/boot/RFOS.bin
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	~/opt/grub/bin/grub-mkrescue -o RFOS.iso isodir 
	echo "run 'make run' to run qemu"
debug:
	make clean
	~/opt/cross/bin/i686-elf-as boot/boot.s -o build/boot.o
	~/opt/cross/bin/i686-elf-gcc -c kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	make lib-debug
	make libhel-debug
	~/opt/cross/bin/i686-elf-gcc -T boot/linker.ld -o build/RFOS-debug.bin -ffreestanding -g -nostdlib build/boot.o build/kernel.o build/termfunc.o build/helper.o build/printf.o build/stdio.o build/abort.o build/memcmp.o build/memcpy.o build/memmove.o build/memset.o build/strlen.o build/strcpy.o -lgcc -I ./lib/libc/include -I ./lib/include
	qemu-system-i386 -s -S -kernel build/RFOS-debug.bin

libc:
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/stdio/printf.c -o build/printf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include 
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/stdio/puts.c -o build/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/stdlib/abort.c -o build/abort.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include 
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memcmp.c -o build/memcmp.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memcpy.c -o build/memcpy.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memmove.c -o build/memmove.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memset.c -o build/memset.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/strlen.c -o build/strlen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/strcpy.c -o build/strcpy.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include

lib-debug:
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/stdio/printf.c -o build/printf.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include 
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/stdio/puts.c -o build/stdio.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/stdlib/abort.c -o build/abort.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include 
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memcmp.c -o build/memcmp.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memcpy.c -o build/memcpy.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memmove.c -o build/memmove.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/memset.c -o build/memset.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/strlen.c -o build/strlen.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/libc/string/strcpy.c -o build/strcpy.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include



libhelp:
	~/opt/cross/bin/i686-elf-gcc -c lib/termfunc.c -o build/termfunc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/helper.c -o build/helper.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include

libhel-debug:
	~/opt/cross/bin/i686-elf-gcc -c lib/termfunc.c -o build/termfunc.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include
	~/opt/cross/bin/i686-elf-gcc -c lib/helper.c -o build/helper.o -std=gnu99 -ffreestanding -g -Wall -Wextra -I ./lib/libc/include -I ./lib/include


kernelmain:
	~/opt/cross/bin/i686-elf-as boot/boot.s -o build/boot.o
	~/opt/cross/bin/i686-elf-gcc -c kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./lib/libc/include -I ./lib/include

coresys:
	

clean:
	rm -rf build/*.o
	rm -rf build/*.bin
	rm -rf *.sym

cleaniso:
	rm -rf *.iso


run:
	qemu-system-i386 -cdrom RFOS.iso
