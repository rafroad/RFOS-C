#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <helper.h>
#include <termfunc.h>
#include <string.h>
#include <gdt.h>
#include <idt.h>
#include "kernel.h"

void kernel_main(void){
    init_gdt();
    idt_init();
    terminal_init();
    drawostitle();
    printf_(">");
    printf_("mission success");
}
