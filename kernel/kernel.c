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

void testwrite(){
    stopit();
    outportb(0x60, 0x10);
    printf_("success writing to port 0x60 value 0x10\n");
    printf_("test read for 0x60: %i\n",inportb(0x60));
}


void kernel_main(void){
    init_gdt();
    idt_init();
    terminal_init();
    drawostitle();
    testwrite();
}
