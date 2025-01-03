#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

void init_kb();
void init_kb_fallback(void);
void keyboard_handler(void*);
bool check_rel_key(char c, char list[], int listSize);
void reset_buffer(void);
#ifdef __cplusplus
}
#endif

#endif
