#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#define GDT_SIZE 6

#ifndef _GDT_H_
#define _GDT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*

SPEC OS GDT CODE

*/

void init_gdt();

#ifdef __cplusplus
}
#endif

#endif
