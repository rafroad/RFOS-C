#include <helper.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void){
    #if defined(__is_libk)
        criterror("kernel panic");
    #else
        milderror("abort");
    #endif
    while(1){}
    __builtin_unreachable();
}

