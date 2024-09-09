#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>


__attribute__((aligned(0x10)))
static idt_desc_t idt[256];

static idtr_t idtr;

__attribute__((noreturn))
void exception_handler(void);
void exception_handler(){
    __asm__ volatile ("cli; hlt");
}
