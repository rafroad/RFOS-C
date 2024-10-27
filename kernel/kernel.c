#include "kernel.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <helper.h>
#include <stdio.h>
#include <termfunc.h>
#include <string.h>
#include <gdt.h>
#include <idt.h>
#include <irq.h>
#include <pic.h>
#include <shell.h>
#include <paging.h>
#include <fs.h>

void kernel_main(void){
    init_gdt();
    idt_init();
    pic_init();
    liballoc_init();
    terminal_init();
    printf("GDT IDT PIC AND LIBALLOC SUCCESS\n");
    if(loadFileSystem()){
        printf_("success init fs\n");
    }
    else{
        printf_("ERROR fail to init fs\n");
    }
    drawostitle();
    shellinit();
    for(;;) {
        asm("hlt");  // Wait for next interrupt
    }
}
