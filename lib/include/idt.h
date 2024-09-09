#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#define IDT_MAX_DESCRIPTORS 256
#define IDT_CPU_EXCEPTION_COUNT	32

#ifndef _IDT_H_
#define _IDT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint16_t	base_low;
	uint16_t	cs;
	uint8_t	    ist;
	uint8_t     attributes;
	uint16_t    base_mid;
	uint32_t    base_high;
	uint32_t    rsv0;
} __attribute__((packed)) idt_desc_t;

typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;




#ifdef __cplusplus
}
#endif
