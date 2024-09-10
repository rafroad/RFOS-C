#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>


#ifndef _IRQ_H_
#define _IRQ_H_

#ifdef __cplusplus
extern "C" {
#endif

void outportb(unsigned int port,unsigned char value);
unsigned char inportb(unsigned int port);
void stopit(void);

#ifdef __cplusplus
}
#endif

#endif
