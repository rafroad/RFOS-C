#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <helper.h>
#include <termfunc.h>
#include <string.h>
#include <gdt.h>
#include <idt.h>
#define OSVER "RFOS-V1.0-TEST"

#if defined(__linux__)
#error "You are not using a cross-compiler use it"
#endif


void kernel_main(void){
    init_gdt();
    idt_init();
    terminal_init();
    drawostitle();
    printf_(">");
}
