#include <helper.h>
#include <keyboard.h>
#include <printf.h>
#include <stdbool.h>
#include <irq.h>
#include "shell.h"
#include <liballoc.h>
#include <termfunc.h>
#include <helper.h>

char option[][1000]={"test","hello","clear"};


void shellinit(void) {
    drawmultextnum(option,3);
    printf_(">");
}

void shell_option(char* input) {
    switch(atoi(input)) {
        case 1:
            printf_("test\n");
            break;
        case 2:
            printf("hello from RFOS \n");
            break;
        case 3:
            termclear();
            drawostitle();
            drawmultextnum(option,3);
            break;
        default:
            printf_("invalid input\n");
            break;
    }
    printf_(">");  // Print new prompt
}

void process_shell_input(char* input) {
    shell_option(input);
}
