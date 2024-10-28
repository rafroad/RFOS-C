#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _PAGING_H_
#define _PAGING_H_

#ifdef __cplusplus
extern "C" {
#endif

int liballoc_lock();
int liballoc_unlock();
void* liballoc_alloc(int);
int liballoc_free(void*,int);
void liballoc_init();
void liballoc_dump();
void liballoc_status();

#ifdef __cplusplus
}
#endif

#endif
