//cstring.c
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cstring.h"


static size_t cstring_size(char* ptr){
    /* helper
     */
    // size_t keeping track of size is directly before char*
    size_t* begOfMallocedMem = (size_t*)(ptr-sizeof(size_t));
    return *begOfMallocedMem;
}

char* cstring_init(char** ptr, size_t size){
    // +sizeof(size_t) to keep track of size
    *ptr = calloc(sizeof(size_t)+size, 1);
    size_t* begOfMallocedMem = (size_t*)(*ptr);
    *begOfMallocedMem = size;
    *ptr += sizeof(size_t);
    *(*ptr+size-1) = '\0';
    return *ptr;
}

void cstring_free(char** ptr){
    free(*ptr-sizeof(size_t));
    *ptr = NULL;
}

int cstring_vsprintf(char** ptr, const char* format, va_list ap){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list args2;
    va_copy(args2, ap);
    int len = vsnprintf(*ptr, cstring_size(*ptr), format, ap);
    if(len < 0){
        //snprintf returns negative len if error occurred
        **ptr = '\0';
        return -1;
    }
    else if(len >= (int)cstring_size(*ptr)){
        char* tmp = *ptr-sizeof(size_t);
        char* tmp2 = realloc(tmp, CSTRING_MULTIPLIER*(sizeof(size_t)+len+1));
        if(tmp == NULL){
            fprintf(stderr, \
                "could not allocate memory for string. Attmempting to continue...\n");
        }
        else{
            tmp = tmp2;
            *(size_t*)tmp = len;
            *ptr = tmp+sizeof(size_t);
            // second argument is max number of bytes to write, including null byte
            // hence, +1
            vsnprintf(*ptr, len+1, format, args2);
        }
    }
    va_end(args2);
    return len;
}

int cstring_sprintf(char** ptr, const char* format, ...){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list args, args2;
    va_start(args, format);
    // create copy of args since vsnprintf destroys fourth arg
    va_copy(args2, args);
    int len = vsnprintf(*ptr, cstring_size(*ptr), format, args);
    // args is left undefined, unusable
    va_end(args);
    if(len < 0){
        //snprintf returns negative len if error occurred
        **ptr = '\0';
        return -1;
    }
    else if(len >= (int)cstring_size(*ptr)){
        char* tmp = *ptr-sizeof(size_t);
        char* tmp2 = realloc(tmp, CSTRING_MULTIPLIER*(sizeof(size_t)+len+1));
        if(tmp == NULL){
            fprintf(stderr, \
                "could not allocate memory for string. Attmempting to continue...\n");
        }
        else{
            tmp = tmp2;
            *(size_t*)tmp = len;
            *ptr = tmp+sizeof(size_t);
            vsnprintf(*ptr, len+1, format, args2);
        }
    }
    va_end(args2);
    return len;
}

char* cstring_strcat(char** dest, char* src){
    size_t destLen = strlen(*dest);
    size_t srcLen = strlen(src);
    if(destLen + srcLen >= cstring_size(*dest)){
        // *dest not large enough to hold resultant string
        // this is really just emulating strdup in order to adhere to iso c
        CSTRING(destCpy, CSTRING_MULTIPLIER*(destLen+srcLen+1));
        cstring_sprintf(&destCpy, "%s%s", *dest, src);
        /* silently replace *dest with destCpy so *dest
         * does not need to realloc everytime one byte is concatonated
         *
         * tune CSTRING_MULTIPLIER to reduce memory wastage/increase
         * frequency of calls to realloc
         */
        cstring_free(dest);
        *dest = destCpy;
        return destCpy;
    }
    else{
        // *dest is large enough to hold resultant string
        char* nextByte = (*dest)+destLen;
        memcpy(nextByte, src, strlen(src)+1);
        return *dest;
    }
}
