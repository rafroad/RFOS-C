#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>

#ifndef _IDT_H_
#define _IDT_H_

#ifdef __cplusplus
extern "C" {
#endif

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);
extern void* isr_stub_table[];
void int_handler();

#ifdef __cplusplus
}
#endif

#endif
