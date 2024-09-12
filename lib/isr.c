#include "isr.h"

void exception_handler() {
    printf_("interupt detected");
    __asm__ volatile ("hlt");
}
