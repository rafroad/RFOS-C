#include "irq.h"
#include <stdio.h>
#include <keyboard.h>

/*

REMEMBER TO RUN STOPIT BEFORE READING A PORT TO PREVENT SYSTEM CRASH

*/

// read something from a port
unsigned char inportb(unsigned int port){
    unsigned char ret;
    asm volatile("inb %%dx,%%al":"=a"(ret):"d"(port));
    return ret;
}


// write something to a port
void outportb(unsigned int port,unsigned char value){
    asm volatile("outb %%al, %%dx"::"d"(port),"a"(value));
}

void stopit(void){
    asm("cli");
}
