#include "kernel.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <helper.h>
#include <termfunc.h>
#include <string.h>
#include <gdt.h>
#include <idt.h>
#include <irq.h>
#include <pic.h>
#include <shell.h>

void kernel_main(void){
    init_gdt();
    idt_init();
    pic_init();
    terminal_init();
    drawostitle();
    init_kb();
}
