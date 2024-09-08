#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#include "gdt.h"

GDT_ENTRY gdt[GDT_SIZE];
GDT_INFO info;

void gdt_init(void){
    gdt_fill_entry(1,true, 0);
    gdt_fill_entry(2,false, 0);
    gdt_fill_entry(3,true,3);
    gdt_fill_entry(4,false,3);
    info.size=sizeof(GDT_ENTRY)*GDT_SIZE-1;
    info.offset=(uint32_t)&gdt;
    __asm__("lgdt %0" ::"m"(info));
}

void gdt_fill_entry(int index,bool exec,uint8_t privilage_level){
    gdt[index].limit_0_15 = 0xFFF;
    gdt[index].base_0_15 = 0x0000;
    gdt[index].base16_23 = 0x00;

    gdt[index].accessed = 0;
    gdt[index].r_w = 1;
    gdt[index].executable = exec;
    gdt[index].reserved = 1;
    gdt[index].privilage_level = privilage_level;
    gdt[index].present = 1;

    gdt[index].limit_16_19 = 0xf;
    gdt[index].reserved_2 = 0;
    gdt[index].size = 1;
    gdt[index].base24_31 = 0x00;

}

void refresh_ss(void){
    __asm__ (
        "jmp 0xFFF\n"           
        ".reload_CS:\n"
        "mov $0x10, %%ax\n"     
        "mov %%ax, %%ds\n"      
        "mov %%ax, %%es\n"      
        "mov %%ax, %%fs\n"     
        "mov %%ax, %%gs\n"      
        "mov %%ax, %%ss\n"    
        "ret\n"                 
        :                       
        :                       
        : "ax"                  
    );
}