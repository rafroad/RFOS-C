# Minimum CMake version and project
cmake_minimum_required(VERSION 3.16)
project(RFOS C ASM)

# Set toolchain-specific variables with exact paths from Makefile
set(CMAKE_C_COMPILER "$ENV{HOME}/opt/cross/bin/i686-elf-gcc")
set(CMAKE_ASM_COMPILER "$ENV{HOME}/opt/nasm/bin/nasm")
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS s)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(GRUB_MKRESCUE "$ENV{HOME}/opt/grub/bin/grub-mkrescue")

# Compiler flags exactly as in Makefile
set(COMMON_INCLUDES
    ${CMAKE_SOURCE_DIR}/libc/include
    ${CMAKE_SOURCE_DIR}/lib/include
    ${CMAKE_SOURCE_DIR}/drivers/include
    ${CMAKE_SOURCE_DIR}/kernel/include
)

# Define flags exactly as in Makefile
set(COMMON_FLAGS "-std=gnu99 -ffreestanding -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} -O2")
set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} -g")

# Interrupt-specific flags
set(INTERRUPT_FLAGS_RELEASE "${COMMON_FLAGS} -mgeneral-regs-only -O2")
set(INTERRUPT_FLAGS_DEBUG "${COMMON_FLAGS} -mgeneral-regs-only -g")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-ffreestanding -nostdlib -lgcc")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} -O2")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} -g")

# Create library targets
# LibC
add_library(libc STATIC
    libc/stdio/printf.c
    libc/stdio/puts.c
    libc/stdlib/abort.c
    libc/string/memcmp.c
    libc/string/memcpy.c
    libc/string/memmove.c
    libc/string/memset.c
    libc/string/strlen.c
    libc/string/strcpy.c
)
target_include_directories(libc PRIVATE ${COMMON_INCLUDES})

# Helper library
add_library(libhelp STATIC
    lib/termfunc.c
    lib/helper.c
)
target_include_directories(libhelp PRIVATE ${COMMON_INCLUDES})

# Core system library
add_library(coresys STATIC
    lib/isr.s
    lib/isr.c
    lib/idt.c
    lib/gdt.c
    lib/irq.c
    lib/pic.c
)
set_source_files_properties(lib/isr.c PROPERTIES
    COMPILE_FLAGS "${INTERRUPT_FLAGS_RELEASE}")
target_include_directories(coresys PRIVATE ${COMMON_INCLUDES})

# Drivers library
add_library(drivers STATIC
    drivers/keyboard.c
)
set_source_files_properties(drivers/keyboard.c PROPERTIES
    COMPILE_FLAGS "${INTERRUPT_FLAGS_RELEASE}")
target_include_directories(drivers PRIVATE ${COMMON_INCLUDES})

# Kernel components
add_library(kernel_components STATIC
    kernel/kernel.c
    kernel/shell.c
)
target_include_directories(kernel_components PRIVATE ${COMMON_INCLUDES})

# Boot assembly
add_library(boot STATIC
    boot/boot.s
)

# Main executable
add_executable(RFOS.bin boot/boot.s)
target_link_libraries(RFOS.bin
    boot
    kernel_components
    libc
    libhelp
    coresys
    drivers
)
set_target_properties(RFOS.bin PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/boot/linker.ld)
set_target_properties(RFOS.bin PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/boot/linker.ld")

# Create isodir structure
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/isodir/boot/RFOS.bin
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/isodir/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:RFOS.bin> ${CMAKE_BINARY_DIR}/isodir/boot/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/boot/grub.cfg ${CMAKE_BINARY_DIR}/isodir/boot/grub/
    DEPENDS RFOS.bin
)

# ISO creation
add_custom_target(iso
    COMMAND ${GRUB_MKRESCUE} -o ${CMAKE_BINARY_DIR}/RFOS.iso ${CMAKE_BINARY_DIR}/isodir
    DEPENDS ${CMAKE_BINARY_DIR}/isodir/boot/RFOS.bin
)

# QEMU targets
add_custom_target(run
    COMMAND qemu-system-i386 -cdrom ${CMAKE_BINARY_DIR}/RFOS.iso
    DEPENDS iso
)

add_custom_target(debugrun
    COMMAND qemu-system-i386 -s -S -kernel ${CMAKE_BINARY_DIR}/RFOS.bin -monitor stdio
    DEPENDS RFOS.bin
)

add_custom_target(debugrunnogdb
    COMMAND qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/RFOS.bin -monitor stdio
    DEPENDS RFOS.bin
)

# Clean targets
add_custom_target(cleanall
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.sym
)

add_custom_target(cleaniso
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.iso
)
