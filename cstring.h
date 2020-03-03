//cstring.h
#ifndef CSTRING_H
#define CSTRING_H

/* https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
 */
#define CSTRING_OVERLOAD(_1, _2, DEMANGLE, ...) DEMANGLE
#define CSTRING(...) CSTRING_OVERLOAD(__VA_ARGS__, CSTRING2, CSTRING1)(__VA_ARGS__)

#define CSTRING1(name) \
    char* name;\
    cstring_init(&name, 32);

#define CSTRING2(name, size) \
    char* name;\
    cstring_init(&name, size);

/* BE CAREFUL
 * cstring* expects address of char* associated with cstring
 * to modify char* if necessary
 *
 * NEVER pass char* directly into a cstring function
 */

/* REQUIRES:
 * MODIFIES:
 * EFFECTS:
 */
char* cstring_init(char** ptr, size_t size);

/* REQUIRES:
 * MODIFIES:
 * EFFECTS:
 */
void cstring_free(char** ptr);

/* REQUIRES:
 * MODIFIES:
 * EFFECTS:
 */
int cstring_vsprintf(char** ptr, const char* format, va_list ap);

/* REQUIRES:
 * MODIFIES:
 * EFFECTS:
 */
int cstring_sprintf(char** str, const char* format, ...);

/* REQUIRES:
 * MODIFIES:
 * EFFECTS:
 */
char* cstring_strcat(char** dest, char* src);

#endif /* CSTRING_H */
