#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#define GDT_SIZE 6

#ifndef _GDT_H_
#define _GDT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GDT_ENTRY{
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t base16_23;

    uint8_t accessed:1;
    uint8_t r_w:1;
    uint8_t direction:1;
    uint8_t executable:1;
    uint8_t reserved:1;
    uint8_t privilage_level:1;
    uint8_t present:1;

    uint8_t limit_16_19:4;
    uint8_t reserved_2:2;
    uint8_t size:1;
    uint8_t granularity:1;
    uint8_t base24_31;


}__attribute__((packed)) GDT_ENTRY;

typedef struct GDT_INFO
{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed)) GDT_INFO;



void gdtinit(void);
void gdt_fill_entry(int index,bool exec,uint8_t privilage_level);
void refresh_ss(void);


#ifdef __cplusplus
}
#endif

#endif