#include <irq.h>
#include <printf.h>
#include "pic.h"
#include "include/pic.h"
#include <stdint.h>
#include <idt.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI		0x20



void pic_init() {
    outportb(PIC1_COMMAND, 0x11);
    outportb(PIC2_COMMAND, 0x11);
    outportb(PIC1_DATA, 0x20);
    outportb(PIC2_DATA, 0x28);
    outportb(PIC1_DATA, 0x04);
    outportb(PIC2_DATA, 0x02);
    outportb(PIC1_DATA, 0x01);
    outportb(PIC2_DATA, 0x01);
    outportb(0x21 , 0xfd);
    outportb(0xA1 , 0xff);
    asm("sti");
    // asm("ret");
}

void pic_send_eoi(uint8_t irq)
{
	if(irq >= 8)
		outportb(PIC2_COMMAND,PIC_EOI);

	outportb(PIC1_COMMAND,PIC_EOI);
}

void pic_1_send_eoi(){
   	outportb(PIC1_COMMAND,PIC_EOI);
}
