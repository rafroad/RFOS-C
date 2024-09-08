#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <helper.h>
#include <termfunc.h>
#include <string.h>
#include <gdt.h>
#define OSVER "RFOS-V1.0-TEST"

#if defined(__linux__)
#error "You are not using a cross-compiler use it"
#endif


void kernel_main(void){
    gdt_init();
    terminal_init();
    drawostitle();
    printf_(">");
    refresh_ss();
    printf_("reload success");
}
