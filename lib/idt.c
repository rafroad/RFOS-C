#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>

typedef struct idt32
{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
<<<<<<< HEAD
    uint8_t type_attributes;
    uint16_t offset_2;
}__attribute__((packed));
=======

};

__attribute__((aligned(0x10)))
static idt_entry_t idt[256]

typedef struct idtr_t{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed))

static idtr_t idtr;
>>>>>>> e9e8d8d (add basic idt)
