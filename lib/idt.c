#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>

struct idt32
{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    
};
