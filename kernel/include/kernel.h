#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <string.h>
#include <helper.h>
#include <irq.h>
#include <shell.h>

#define OSVER "RFOS-V1.0-TEST"

#if defined(__linux__)
#error "You are not using a cross-compiler use it"
#endif

#ifndef _KERNEL_H_
#define _KERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

void kernel_main(void);

#ifdef __cplusplus
}
#endif

#endif
