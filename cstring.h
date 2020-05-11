//cstring.h
#ifndef CSTRING_H
#define CSTRING_H
#include <stdlib.h>
#include <stdarg.h>

/* BE CAREFUL
 * cstring* expects address of char* associated with cstring
 * to modify char* if necessary
 *
 * NEVER pass char* directly into a cstring function
 */

char* cstring_init(char** ptr, size_t size);

void cstring_free(char** ptr);

size_t cstring_capacity(char* ptr);

int cstring_sprintf(char** ptr, const char* format, ...);

int cstring_vsprintf(char** ptr, const char* format, va_list ap);

char* cstring_strcat(char** dest, char* src);

void cstring_reserve(char** ptr, size_t size);

void cstring_shrink_to_fit(char** ptr);

#endif /* CSTRING_H */
