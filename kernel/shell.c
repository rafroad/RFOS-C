#include <helper.h>
#include <keyboard.h>
#include <printf.h>
#include <stdbool.h>
#include <irq.h>
#include "shell.h"

void shellinit(void) {
    printf_(">");
}

void shell_option(char* input) {
    switch(atoi(input)) {
        case 1:
            printf_("test\n");
            break;
        case 2:
            printf("%s")
        default:
            printf_("invalid input\n");
            break;
    }
    printf_(">");  // Print new prompt
}

void process_shell_input(char* input) {
    shell_option(input);
}
