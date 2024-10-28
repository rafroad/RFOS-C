#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "termfunc.h"
#include <printf.h>
#include <helper.h>
#include <cursor.h>

enum vga_color{
    VGA_BLACK=0,
    VGA_WHITE=15,
    VGA_LIGHT_GREY=7,
};

#define BACKSPACE 0x08

static const size_t VGA_WIDTH=80;
static const size_t VGA_HEIGHT=25;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

static inline uint8_t vga_entry_color(enum vga_color fg,enum vga_color bg){
    return bg | fg << 4;
}
static inline uint16_t vga_entry(unsigned char uc,uint8_t color){
    return (uint16_t) uc | (uint16_t) color<<8;
}


void termscroll(int line){
    size_t i;
    for(int j=0;j<line;j++){
        for(i=0;i<VGA_HEIGHT;i++){
            for(size_t y=0;y<VGA_WIDTH;y++){
                terminal_buffer[i*VGA_WIDTH+y]=terminal_buffer[(i+1)*VGA_WIDTH+y];
            }
        }
    }
}

void putentryat(unsigned char c,uint8_t color,size_t x,size_t y){
    const size_t index=y*VGA_WIDTH+x;
    if(c=='\n'){
        c=0x00;
    }
    else if(c=='\t'){
        c=0x00;
    }
    else if(c=='\v'){
        c=0x00;
    }
    else if(c=='\\'){
        c=0x5C;
    }
    else if(c=='\?'){
        c=0x3F;
    }
    terminal_buffer[index]=vga_entry(c,color);
}

void putcharus(char c) {
    unsigned char uc = c;

    // Handle special characters
    switch (uc) {
        case '\n':
            terminal_column = 0;
            terminal_row++;
            break;

        case '\r':
            terminal_column = 0;
            break;

        case '\t':
            // Move to next tab stop (every 4 columns)
            terminal_column = (terminal_column + 4) & ~3;
            break;

        case '\v':
            terminal_row += 3;  // Vertical tab - move down 3 lines
            break;

        default:
            // Regular character
            putentryat(uc, terminal_color, terminal_column, terminal_row);
            terminal_column++;
            break;
    }

    update_cursor_position();
}

void terminal_init(void){
    terminal_row=0;
    terminal_column=0;
    terminal_color=vga_entry_color(VGA_BLACK,VGA_LIGHT_GREY);
    terminal_buffer=(uint16_t*) 0xB8000;
    enable_cursor(0,VGA_WIDTH);
    // disable_cursor();
    for(size_t y=0; y<VGA_HEIGHT;y++){
        for(size_t x=0;x<VGA_WIDTH;x++){
            const size_t index=y*VGA_WIDTH+x;
            terminal_buffer[index]=vga_entry(' ',terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color){
    terminal_color=color;
}

void termdellastline(void){
    for(int i=0;i<VGA_WIDTH-1;i++){
        putentryat(' ',terminal_color,i,VGA_HEIGHT-1);
    }
}
void termdellastchar(void) {
    if (terminal_column > 0) {
        terminal_column--;
    }
    else if (terminal_row > 0) {
        terminal_row--;
        terminal_column = VGA_WIDTH - 1;
    }

    // Clear the character at current position
    putentryat(0x00, terminal_color, terminal_column, terminal_row);
    setcursorpos(terminal_column, terminal_row);
}


void terminal_newline(){
    terminal_column=0;
    terminal_row++;
}

size_t printcentre(void){
    terminal_column=VGA_WIDTH/2;
}

void termclear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    terminal_row = 0;
    terminal_column = 0;
    setcursorpos(0, 0);
}

void update_cursor_position(void) {
    // Handle horizontal wrapping
    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
    }
    // Handle backwards wrapping
    else if (terminal_column < 0) {
        terminal_column = VGA_WIDTH - 1;
        terminal_row--;
    }

    // Handle vertical bounds and scrolling
    if (terminal_row >= VGA_HEIGHT) {
        termscroll(1);
        termdellastline();
        terminal_row = VGA_HEIGHT - 1;
    }
    else if (terminal_row < 0) {
        terminal_row = 0;
        terminal_column = 0;
    }

    setcursorpos(terminal_column, terminal_row);
}

void handle_backspace(void) {
    if (terminal_column > 0) {
        terminal_column--;
    }
    else if (terminal_row > 0) {
        terminal_row--;
        terminal_column = VGA_WIDTH - 1;
    }
    else {
        // At top-left corner, nothing to delete
        return;
    }

    // Clear the character at new cursor position
    putentryat(0x00, terminal_color, terminal_column, terminal_row);
    update_cursor_position();
}
