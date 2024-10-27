#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>


#ifndef _SHELL_H_
#define _SHELL_H_

#ifdef __cplusplus
extern "C" {
#endif

void shellinit();
void shell_option(char option[]);
void process_shell_input(char* input);

#ifdef __cplusplus
}
#endif

#endif
