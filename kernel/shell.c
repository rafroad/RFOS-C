#include <helper.h>
#include <keyboard.h>
#include <printf.h>
#include <stdbool.h>
#include <irq.h>
#include "shell.h"
#include <liballoc.h>
#include <termfunc.h>
#include <tasks.h>
#include <helper.h>

char option[][1000]={"test","hello","clear"};


void shellinit(void) {
    printf_(">");
    for(;;) {
        asm("hlt");  // Wait for next interrupt
    }
}

void shell_option(char* input) {
    if(strcmp(input, "test")==0){
        printf_("test\n");
    }
    else if(strcmp(input,"hello")==0){
        printf("hello from RFOS \n");
    }
    else if(strcmp(input, "clear")==0){
        termclear();
        drawostitle();
    }
    else if(strcmp(input,"ramlist")==0){
        liballoc_status();
    }
    else if(strcmp(input,"ramdump")==0){
        liballoc_dump();
    }
    else if(strcmp(input,"multitasking")==0){
        test_multitasking();
    }
    else{
        printf_("no such command\n");
    }
    printf_(">");
}

void process_shell_input(char* input) {
    shell_option(input);
}

void inlineinputtest(char* input){
    printf_("%s\n",input);
}
