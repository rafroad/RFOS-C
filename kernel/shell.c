#include <helper.h>
#include <keyboard.h>
#include <printf.h>
#include <stdbool.h>
#include <irq.h>
#include "shell.h"
#include <liballoc.h>


void shellinit(void) {
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
            char* str = malloc(4);
            if (str != NULL) {
                printf("Allocated %d pages at address: %p\n", 4, str);
            } else {
                printf("Allocation failed for %d pages.\n", 4);
            }
            str[0]='h';str[1]='e';str[2]='y';str[3]='\0';
            printf("%s\n",str);
            free(str);
            printf("freed memory from %p\n",str);
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
