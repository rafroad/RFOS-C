#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#include "gdt.h"

struct GDT_ENTRY{
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


}


void encoded_gdt_entry(uint8_t *target, struct GDTINPUT source){

}