#include <helper.h>
#include <keyboard.h>
#include <printf.h>
#include <stdbool.h>
#include "shell.h"

void shellinit(){
    while(true){
        printf_(">");
        for(;;){
            asm("hlt");
        }
    }
}
void shell_option(int option){
    switch(option){
        case 1:
        printf_("test");
        break;
    }
    shellinit();
}
