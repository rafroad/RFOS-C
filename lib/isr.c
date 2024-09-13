#include "isr.h"
#include <idt.h>
#include <keyboard.h>

void exception_handler(void*) {
    printf_("interupt detected");
    pic_1_send_eoi();
    asm("hlt");
}
