#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#
#ifndef _PIC_H_
#define _PIC_H_

#ifdef __cplusplus
extern "C" {
#endif

void pic_init();
void pic_send_eoi(uint8_t irq);
void pic_1_send_eoi();

#ifdef __cplusplus
}
#endif

#endif
