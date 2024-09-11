#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#define INT_KEYBOARD 0x00000009

#ifndef _IRQ_H_
#define _IRQ_H_

#ifdef __cplusplus
extern "C" {
#endif

void outportb(unsigned int port,unsigned char value);
unsigned char inportb(unsigned int port);
void stopit(void);

struct cpu_state {
  uint32_t cr2;
  uint32_t ebp;
  uint32_t edi;
  uint32_t esi;
  uint32_t edx;
  uint32_t ecx;
  uint32_t ebx;
  uint32_t eax;
} __attribute__((packed));

void enable_keyboard_interrupts();
uint32_t interrupt_handler(struct cpu_state cpu, uint32_t interrupt_number, uint32_t error_code, uint32_t eip);

#ifdef __cplusplus
}
#endif

#endif
