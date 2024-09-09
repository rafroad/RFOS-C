## RF OS BUT IN C
current list of things to work on:
1. GDT (code working thanks to (https://github.com/jakeSteinburger/SpecOS/blob/main/sys/gdt.c))
2. IDT (basic exist thanks to osdev tutorial)
3. KB input (OTW tm)
4. Basic shell
5. All of the old RF OS in CosmosOS

## COMPILE STEP
These instructions assume you are using a linux or unixlike operating system
1. follow the https://wiki.osdev.org/GCC_Cross-Compiler to get a cross compiler using GCC version 13.2.0 GDB version 14.1 and Binutils version 2.41
2. install the cross compiler to $HOME/opt/cross
3. unpack the grub tar in package/ and compile then install into $HOME/opt/grub
4. get nasm from source and compile then install into $HOME/opt/nasm
5. get qemu from your distro package manager
6. run 'make allrun' to compile with -O2 then run qemu or run 'make debug' to compile with -g or run 'make debugrun' to run with gdb support or run 'debugrunnogdb' to run with qemu serial monitor
