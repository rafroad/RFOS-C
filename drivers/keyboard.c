#include "keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include <irq.h>
#include <stdio.h>
#include <termfunc.h>
#define DATA_PORT 0x60


uint8_t lastkey = 0;
uint8_t *keycache = 0;
uint16_t key_loc = 0;
uint8_t __kbd_enabled = 0;

void init_kb(void){
    char keypressed[1000]="";
    int i=0;
    stopit();
    outportb(DATA_PORT, 0xF4);
    if(inportb(DATA_PORT) != 0xFA){
        printf_("fail to init keyboard");
    }
    while (true) {
        if(inportb(0x60)!= 0xFA){
            char key=inportb(0x60);
            putcharus(key);
            outportb(DATA_PORT, 0xF4);
        }
    }
}

int returnkey(char keycode){
    char alphabet[][100]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n",
        "o","p","q","r","s","t","u","v","w","x","y","z"};
}

void testps2(){
    printf_("0x60: %x\n",inportb(0x60));
    printf_("0x68: %x\n",inportb(0x68));
    stopit();
    outportb(0x60, 0xF2);
    printf_("success writing to port 0x60 value 0xF2\n");
    printf_("0x60: %x\n",inportb(0x60));
    printf_("0x68: %x\n",inportb(0x68));
    stopit();
    outportb(0x60, 0xF0);
    printf_("success writing to port 0x60 value 0xF0\n");
    printf_("0x60: %x\n",inportb(0x60));
    stopit();
    outportb(0x60, 0);
    printf_("success writing to port 0x60 value 0\n");
    printf_("0x60: %x\n",inportb(0x60));
    stopit();
    outportb(0x60, 0xF4);
    printf_("success writing to port 0x60 value 0xF4\n");
    printf_("0x60: %x\n",inportb(0x60));
    printf_("0x68: %x\n",inportb(0x68));

}
