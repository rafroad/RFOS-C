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

void setup_pic();
void pic_send_eoi(uint8_t irq);

#ifdef __cplusplus
}
#endif

#endif
