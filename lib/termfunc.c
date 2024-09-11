#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "termfunc.h"
#include <printf.h>
#include <helper.h>

enum vga_color{
    VGA_BLACK=0,
    VGA_WHITE=15,
    VGA_LIGHT_GREY=7,
};



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
    char c;
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

void putcharkb(char c){
    unsigned char uc=c;
    putentryat(uc,terminal_color,terminal_column,terminal_row);
    if(++terminal_column==VGA_WIDTH){
        terminal_column=0;
        if(++terminal_row==VGA_HEIGHT){
            termdellastline();
            termscroll(1);
            terminal_column=VGA_HEIGHT-1;
        }
    }
    if(terminal_row == VGA_HEIGHT){
        termscroll(1);
        termdellastline();
        terminal_row=VGA_HEIGHT-1;
    }

}


void putcharus(char c){
    unsigned char uc=c;
    putentryat(uc,terminal_color,terminal_column,terminal_row);
    if(++terminal_column==VGA_WIDTH){
        terminal_column=0;
        if(++terminal_row==VGA_HEIGHT){
            termdellastline();
            termscroll(1);
            terminal_column=VGA_HEIGHT-1;
        }
    }
    else if(c=='\n'){
        terminal_column=0;
        terminal_row++;
    }
    else if(c=='\t'){
        for(int i=0;i<3;i++){
            terminal_column++;
        }
    }
    else if(c=='\v'){
        for(int i=0;i<3;i++){
            terminal_row++;
        }
    }
    if(terminal_row == VGA_HEIGHT){
            termscroll(1);
            termdellastline();
            terminal_row=VGA_HEIGHT-1;
        }
    }


void terminal_init(void){
    terminal_row=0;
    terminal_column=0;
    terminal_color=vga_entry_color(VGA_BLACK,VGA_LIGHT_GREY);
    terminal_buffer=(uint16_t*) 0xB8000;
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

size_t printcentre(void){
    terminal_column=VGA_WIDTH/2;
}

void termclear(){
    for(uint16_t i=-1;i<=terminal_buffer;i++){
        terminal_buffer[i]=0x00;
        terminal_buffer=0;
    }
}
