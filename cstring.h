//cstring.h
#ifndef CSTRING_H
#define CSTRING_H

#ifdef _cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* BE CAREFUL
 * cstring* expects address of char* associated with cstring
 * to modify char* if necessary
 *
 * NEVER pass char* directly into a cstring function
 */

static const int CSTRING_MULTIPLIER = 2;


static inline size_t cstring_capacity(char* ptr){
    // size_t keeping track of capacity is directly before char*
    size_t* begOfMallocedMem = (size_t*)(ptr-sizeof(size_t));
    return *begOfMallocedMem;
}

static void cstring_safe_realloc(char** ptr, size_t size){
    // not really meant to be called by user
    char* tmp = (char*)realloc(*ptr-sizeof(size_t), sizeof(size_t)+size+1);
    if(tmp == NULL){
        fprintf(stderr,\
            "%s, %s, %d: could not allocate memory for cstring."\
            "Attmempting to continue...\n", __FILE__, __func__, __LINE__);
    }
    else{
        *ptr = tmp+sizeof(size_t);
    }
}

static char* cstring_init(char** ptr, size_t size){
    // +sizeof(size_t) to keep track of size
    *ptr = (char*)calloc(sizeof(size_t)+size+1, 1);
    size_t* begOfMallocedMem = (size_t*)(*ptr);
    *begOfMallocedMem = size;
    *ptr += sizeof(size_t);
    *(*ptr+size) = '\0';
    return *ptr;
}

static inline void cstring_free(char** ptr){
    free(*ptr-sizeof(size_t));
    *ptr = NULL;
}

static int cstring_vsprintf(char** ptr, const char* format, va_list ap){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list args2;
    va_copy(args2, ap);
    int len = vsnprintf(*ptr, cstring_capacity(*ptr)+1, format, ap);
    if(len < 0){
        //snprintf returns negative len if error occurred
        **ptr = '\0';
        return len;
    }
    else if(len > (int)cstring_capacity(*ptr)){
        cstring_safe_realloc(ptr, CSTRING_MULTIPLIER*(len));
        vsnprintf(*ptr, len+1, format, args2);
    }
    else{
    }
    va_end(args2);
    return len;
}

static int cstring_sprintf(char** ptr, const char* format, ...){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list args;
    va_start(args, format);
    int ret = cstring_vsprintf(ptr, format, args);
    va_end(args);
    return ret;
}

static char* cstring_strcat(char** dest, char* src){
    size_t destLen = strlen(*dest);
    size_t srcLen = strlen(src);
    if(destLen + srcLen >= cstring_capacity(*dest)){
        // *dest not large enough to hold resultant string
        // this is really just emulating strdup
        char* destCpy;
        cstring_init(&destCpy, destLen+srcLen+1);
        cstring_sprintf(&destCpy, "%s%s", *dest, src);
        /* silently replace *dest with destCpy
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
        // haven't look at generated code but it's written like so
        // to not recalculate strlen (vs using strcat)
        char* nextByte = (*dest)+destLen;
        memcpy(nextByte, src, strlen(src)+1);
        return *dest;
    }
}

static inline void cstring_reserve(char** ptr, size_t size){
    // If new capacity is greater, reallocate storage. Otherwise does nothing
    if(sizeof(size_t)+size+1 > cstring_capacity(*ptr)){
        cstring_safe_realloc(ptr, size);
    }
}

static inline void cstring_shrink_to_fit(char** ptr){
    cstring_safe_realloc(ptr, strlen(*ptr));
}

#ifdef _cplusplus
}
#endif

#endif /* CSTRING_H */
