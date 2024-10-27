#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#include "cursor.h"


static const size_t VGA_WIDTH=80;
static const size_t VGA_HEIGHT=25;


void enable_cursor(uint8_t cursor_start, uint8_t cursor_end){
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, (inportb(0x3D5) & 0xC0) | cursor_start);

	outportb(0x3D4, 0x0B);
	outportb(0x3D5, (inportb(0x3D5) & 0xE0) | cursor_end);
}

void setcursorpos(int x,int y){
    uint16_t pos = y * VGA_WIDTH + x;
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (uint8_t) (pos & 0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t get_cursor_position(void)
{
    uint16_t pos=0;
    outportb(0x3D4, 0x0F);
    pos |= inportb(0x3D5);
    outportb(0x3D4, 0x0E);
    pos |= ((uint16_t)inportb(0x3D5)) << 8;
    return pos;
}

void disable_cursor()
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
}
