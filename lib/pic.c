#include <irq.h>
#include <printf.h>
#include "pic.h"
#include <stdint.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI		0x20

void pic_test(){
    printf_("%u\n",inportb(PIC1_COMMAND));
    printf_("%u\n",inportb(PIC1_DATA));
    printf_("%u\n",inportb(PIC2_COMMAND));
    printf_("%u\n",inportb(PIC2_DATA));
    printf_("sending command to %i\n",PIC1_COMMAND);


}

void setup_pic() {
    outportb(PIC1_COMMAND, 0x11);
    outportb(PIC2_COMMAND, 0x11);
    stopit();
    outportb(PIC1_COMMAND, 0x20);
    outportb(PIC2_COMMAND, 0x28);
    stopit();
    outportb(PIC1_DATA, 0x4);
    outportb(PIC2_DATA, 0x2);
    stopit();
    outportb(PIC1_DATA, 0x1);
    outportb(PIC2_DATA, 0x1);
    stopit();
    outportb(PIC1_DATA, 0x0);
    outportb(PIC2_DATA, 0x0);
    stopit();
}

void receive_inter(unsigned char inter){

}

void PIC_sendEOI(uint8_t irq)
{
	if(irq >= 8)
		outportb(PIC2_COMMAND,PIC_EOI);

	outportb(PIC1_COMMAND,PIC_EOI);
}
