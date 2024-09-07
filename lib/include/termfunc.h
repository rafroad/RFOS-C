#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _TERMFUNC_H_
#define _TERMFUNC_H_

#ifdef __cplusplus
extern "C" {
#endif



static inline uint16_t vga_entry(unsigned char uc,uint8_t color);
void putentryat(unsigned char c,uint8_t color,size_t x,size_t y);
void putcharus(char c);
void terminal_init(void);
void terminal_setcolor(uint8_t color);
void termdellastline(void);
void termscroll(int line);
size_t printcentre(void);


#ifdef __cplusplus
}
#endif

#endif