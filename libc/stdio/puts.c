#include <stdio.h>
#include <printf.h>

int puts(const char* str){
    return printf_("%s\n",str);
}