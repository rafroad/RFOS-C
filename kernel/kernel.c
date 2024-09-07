#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <helper.h>
#include <termfunc.h>
#include <string.h>
#define OSVER "RFOS-V1.0-TEST"

#if defined(__linux__)
#error "You are not using a cross-compiler use it"
#endif

void test(void){
    int i=0;
    while(true){
        printf_("Test: %i |  ",i);
        i++;
    }
}

void kernel_main(void){
    terminal_init();
    drawostitle();
    test();
}
