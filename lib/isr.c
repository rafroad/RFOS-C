#include "isr.h"

void exception_handler() {
    printf_("interupt");
    __asm__ volatile ("hlt");
}
