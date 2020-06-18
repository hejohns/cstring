// shellsort.h
#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <stddef.h>
#include <stdbool.h>

/* cc -DSHELLSORT_USE_VLA to use vla/memcpy for SHELLSORT_SWAP
 * Default is as in glibc, to be safe and only use a char buffer
 */
#ifdef SHELLSORT_USE_VLA
#include <string.h>
#define SHELLSORT_SWAP(a, b, size)                         \
    do{                                                    \
        char tmp[size];                                    \
        memcpy(tmp, a, size);                              \
        memcpy(a, b, size);                                \
        memcpy(b, tmp, size);                              \
    } while(false)
#else
// from glibc's qsort SWAP macro
#define SHELLSORT_SWAP(a, b, size)                         \
    do{                                                    \
        size_t sz = size;                                  \
        char *A = a;                                       \
        char *B = b;                                       \
        do{                                                \
            char tmp = *A;                                 \
            *A++ = *B;                                     \
            *B++ = tmp;                                    \
        } while(--sz > 0);                                 \
    } while(false)
#endif

#define SHELLSORT_CONCATONATE(a, b) a ## b

/* Do a gap-insertion sort on all subsequences concurrently
 *
 * Gives better slightly cache locality than doing a full
 * gap-sort on each subsequence before moving onto the next
 */
#define SHELLSORT(base, nmemb, size, less, gap, id)        \
    do{                                                    \
        for(size_t i = gap; ; i += gap){                   \
            for(size_t j = 0; j < gap; j++){               \
                if(j+i >= nmemb){                          \
                    goto SHELLSORT_CONCATONATE(done, id);  \
                }                                          \
                for(size_t k = j+i; k >= j+gap; k -= gap){\
                    if(less(base+(k*size), base+((k-gap)*size))){\
                        SHELLSORT_SWAP((base+(k*size)), (base+((k-gap)*size)), size);\
                    }                                      \
                    else{                                  \
                        break;                             \
                    }                                      \
                }                                          \
            }                                              \
        }                                                  \
done ## id:;                                               \
    }                                                      \
    while(false)

// parameter names/order based of qsort, but compar is incompatible with less
static void shellsort(void *const base, size_t nmemb, size_t size,
        bool (*const less)(const void *, const void *)){
    // start with cirua_2001 gap, then just use (2^k)-1 for simplicity
    static const size_t cirua_2001_size = 8;
    static const size_t cirua_2001[] = {1, 4, 10, 23, 57, 132, 301, 701};
    size_t gap;
    if(nmemb >= 1<<12){
        for(gap = (1<<12)-1; ((gap+1)<<1)-1 < nmemb; gap = ((gap+1)<<1)-1){
        }
        do{
            SHELLSORT(base, nmemb, size, less, gap, 1);
            gap = ((gap+1)>>1)-1;
        } while(gap > cirua_2001[cirua_2001_size-1]);
    }
    for(size_t gap_index = cirua_2001_size; gap_index > 0; gap_index--){
        gap = cirua_2001[gap_index-1];
        if(gap >= nmemb){
            continue;
        }
        SHELLSORT(base, nmemb, size, less, gap, 2);
    }
}

#endif /* SHELLSORT_H */
