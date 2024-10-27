#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>

#ifndef _CURSOR_H_
#define _CURSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void setcursorpos(int x,int y);
uint16_t get_cursor_position(void);
void disable_cursor();

#ifdef __cplusplus
}
#endif

#endif
