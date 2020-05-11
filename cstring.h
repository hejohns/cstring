//cstring.h
#ifndef CSTRING_H
#define CSTRING_H

#ifdef _cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdarg.h>

/* BE CAREFUL
 * cstring* expects address of char* associated with cstring
 * to modify char* if necessary
 *
 * NEVER pass char* directly into a cstring function
 */

inline char* cstring_init(char** ptr, size_t size);

inline void cstring_free(char** ptr);

inline size_t cstring_capacity(char* ptr);

int cstring_sprintf(char** ptr, const char* format, ...);

int cstring_vsprintf(char** ptr, const char* format, va_list ap);

char* cstring_strcat(char** dest, char* src);

inline void cstring_reserve(char** ptr, size_t size);

inline void cstring_shrink_to_fit(char** ptr);

#ifdef _cplusplus
}
#endif

#endif /* CSTRING_H */
