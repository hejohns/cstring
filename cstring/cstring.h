//cstring.h
#ifndef CSTRING_H
#define CSTRING_H

#ifdef __cplusplus
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

// change int to something smaller if allowable.
// However, you will get lots of conversion warnings/errors.
/* Don't use anything larger than int since *printf functions don't play well 
 * with types larger than int.
 * Anyways, why would you want a single cstring that long??
 *
 * There are some casts to hide conversion warnings if you choose a small type
 * It is up to you to make sure no overflows occur
 */
typedef int cstring_size_type;

// change multiplier to something smaller if string lengths are relatively short
static const int CSTRING_MULTIPLIER = 2;


static inline cstring_size_type cstring_capacity(const char* ptr){
    // cstring_size_type keeping track of capacity is directly before char*
    return *(cstring_size_type*)(ptr-sizeof(cstring_size_type));
}

// just to be clear, size is "nice" usable size, not total size allocated by *alloc
static inline void cstring_safe_realloc(char** ptr, cstring_size_type size){
    // not really meant to be called by user
    char* tmp = (char*)realloc(*ptr-sizeof(cstring_size_type), sizeof(cstring_size_type)+size+1);
    if(tmp == NULL){
        /*
        fprintf(stderr,
            "%s, %s, %d: could not allocate memory for cstring."
            "Attmempting to continue...\n", __FILE__, __func__, __LINE__);
        */
        // Unless you really want to keep going no matter what, exit immediatly
        // Helps to debug the real issue
        exit(EXIT_FAILURE);
    }
    else{
        *(cstring_size_type*)tmp = size;
        *ptr = tmp+sizeof(cstring_size_type);
    }
}

static inline char* cstring_init(char** ptr, cstring_size_type size){
    // +sizeof(cstring_size_type) to keep track of size
    *ptr = (char*)calloc(sizeof(cstring_size_type)+size+1, 1);
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }
    *(cstring_size_type*)(*ptr) = size;
    *ptr += sizeof(cstring_size_type);
    // not necessary strictly speaking
    //*(*ptr+size) = '\0';
    return *ptr;
}

static inline void cstring_free(char** ptr){
    free(*ptr-sizeof(cstring_size_type));
    *ptr = NULL;
}

static inline int cstring_vsprintf(char** ptr, const char* format, va_list ap){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list args2;
    va_copy(args2, ap);
    int len = vsnprintf(*ptr, cstring_capacity(*ptr)+1, format, ap);
    if(len < 0){
        // snprintf returns negative len if error occurred
        **ptr = '\0';
        // pass on len for handling by caller
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

static inline char* cstring_strcat(char** dest, const char* src){
    cstring_size_type destLen = (cstring_size_type)strlen(*dest);
    cstring_size_type srcLen = (cstring_size_type)strlen(src);
    if(destLen + srcLen > cstring_capacity(*dest)){
        // *dest not large enough to hold resultant string
        cstring_safe_realloc(dest, destLen+srcLen);
    }
        memcpy((*dest)+destLen, src, srcLen+1);
        return *dest;
}

static inline void cstring_reserve(char** ptr, cstring_size_type size){
    // If new capacity is greater, reallocate storage. Otherwise does nothing
    if(sizeof(cstring_size_type)+size+1 > (size_t)cstring_capacity(*ptr)){
        cstring_safe_realloc(ptr, size);
    }
}

static inline void cstring_shrink_to_fit(char** ptr){
    cstring_safe_realloc(ptr, (cstring_size_type)strlen(*ptr));
}

#ifdef __cplusplus
}
#endif

#endif /* CSTRING_H */
