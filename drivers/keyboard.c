#include "keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include <irq.h>
#include <stdio.h>
#include <string.h>
#include <termfunc.h>
#include <shell.h>
#define DATA_PORT 0x60
#define SIGNAL_PORT 0x64
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define RELEASE_BIT 0x80  // Bit that indicates key release

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

// Buffer to store typed characters
static char input_buffer[256];
static size_t buffer_pos = 0;

bool inscanf=false;

char characterTable[] = {
    0,    27,   '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',
    '-',  '=',  0,    9,    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
    'o',  'p',  '[',  ']',  0,    0,    'a',  's',  'd',  'f',  'g',  'h',
    'j',  'k',  'l',  ';',  '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',  0,    ' ',  0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0x1B, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0x0E, 0x1C, 0,    0,    0,
    0,    0,    0,    0,    0,    '/',  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
    0,    0,    0,    0,    0,    0,    0,    0x2C,
};
char shiftedCharacterTable[] = {
    0,    27,   '!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',  '(',  ')',
    '_',  '+',  0,    9,    'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',
    'O',  'P',  '{',  '}',  0,    0,    'A',  'S',  'D',  'F',  'G',  'H',
    'J',  'K',  'L',  ':',  '"',  '~',  0,    '|',  'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  0,    '*',  0,    ' ',  0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0x1B, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0x0E, 0x1C, 0,    0,    0,
    0,    0,    0,    0,    0,    '?',  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
    0,    0,    0,    0,    0,    0,    0,    0x2C,
};

char relkey[]={0x81,
0x82,	  	0x83,	  0x84,	  	0x85,	  	0x86,	  	0x87,	  0x88,	  	0x89,	  	0x8A,	  	0x8B,0x8C,  	0x8D,
0x8E,0x8F, 0x90, 	0x91, 	0x92, 	0x93, 0x94, 	0x95, 	0x96, 	0x97, 0x98, 	0x99, 	0x9A, 	0x9B, 0x9C, 	0x9D, 	0x9E, 	0x9F,
0xA0, 	0xA1, 	0xA2, 	0xA3, 0xA4, 	0xA5, 	0xA6, 	0xA7, 0xA8, 	0xA9, 	0xAA, 	0xAB, 0xAC, 	0xAD, 	0xAE, 	0xAF, 0xB0, 	0xB1,
0xB2,  	0xB3,  0xB4,  	0xB5,  	0xB6,  	0xB7,  0xB8,  	0xB9,  	0xBA,  	0xBB,  0xBC,  	0xBD,  	0xBE, 	0xBF,  0xC0,  	0xC1,  	0xC2,  	0xC3,
0xC4,  	0xC5,  	0xC6,  	0xC7,  0xC8,  	0xC9,  	0xCA,  	0xCB,  0xCC,  	0xCD, 	0xCE,  	0xCF,  0xD0,  	0xD1,  	0xD2,  	0xD3,  0xD7,  0xD8,
};

void init_kb(void){
    outportb(DATA_PORT, 0xF4);
    outportb(DATA_PORT, 0xF0);
    outportb(DATA_PORT, 0x02);
}

void keyboardtype(void) {
    unsigned char scancode = inportb(DATA_PORT);

    // Ignore key releases (when highest bit is set)
    if (scancode & RELEASE_BIT) {
        outportb(0x20, 0x20);  // Send EOI
        return;
    }

    // Handle key press events
    if (scancode == BACKSPACE) {
        if (buffer_pos > 0) {
            buffer_pos--;
            termdellastchar();  // Use dedicated function to remove character
        }
    }
    else if (scancode == ENTER) {
        putcharus('\n');
        input_buffer[buffer_pos] = '\0';
        process_shell_input(input_buffer);
        buffer_pos = 0;
    }
    else {
        // Check if we have a valid character for this scancode
        char c = characterTable[scancode];
        if (c && buffer_pos < sizeof(input_buffer) - 1) {
            input_buffer[buffer_pos++] = c;
            putcharus(c);
        }
    }

    outportb(0x20, 0x20);  // Send EOI
}

__attribute__((interrupt))
void keyboard_handler(void* _) {
    asm volatile("pushf");
    asm volatile("cli");
    keyboardtype();
    // Restore interrupt state
    asm volatile("popf");
}

bool check_rel_key(char c, char list[], int listSize) {
    for (int i = 0; i < listSize; i++) {
        if (c == list[i]) {
            return false;
        }
    }
    return true;
}

void reset_buffer(void){
    buffer_pos = 0;
}
