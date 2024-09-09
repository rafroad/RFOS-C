#include <string.h>
char* strcpy(char* dst,char *src){
    if(dst==NULL){
        return NULL;
    }
    char *ptr = dst;
    while(*src!='\0'){
        *dst='\0';
    }
    return ptr;
}