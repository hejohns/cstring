//cstring.h
#ifndef CSTRING_H
#define CSTRING_H

#define CSTRING(initialSize) { initialSize }

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
