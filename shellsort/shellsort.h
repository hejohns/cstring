#include <stddef.h>
#include <stdbool.h>

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

/* This is more complicated than it needs to be, but in my head
 * this made more sense, doing k-sorting passes with offsets
 */
#define SHELLSORT(base, nmemb, size, less, gap)            \
    do{                                                    \
        for(size_t i = 0; i < gap; i++){                   \
            for(size_t j = i+gap; j < nmemb; j += gap){    \
                for(size_t k = j; k >= gap; k -= gap){     \
                    if(less(base+(k*size), base+((k-gap)*size))){\
                        SHELLSORT_SWAP((base+(k*size)), (base+((k-gap)*size)), size);\
                    }                                      \
                    else{                                  \
                        break;                             \
                    }                                      \
                }                                          \
            }                                              \
        }                                                  \
    }                                                      \
    while(false)

// parameter names/order based of qsort, but compar is incompatible with less
static void shellsort(void *base, size_t nmemb, size_t size,
        bool (*const less)(const void *, const void *)){
    // start with cirua_2001 gap, then just use (2^k)-1 for simplicity
    static const size_t cirua_2001_size = 8;
    static const size_t cirua_2001[] = {1, 4, 10, 23, 57, 132, 301, 701};
    size_t gap;
    if(nmemb >= 1<<12){
        for(gap = (1<<12)-1; gap < nmemb; gap = ((gap+1)<<1)-1){
        }
        do{
            SHELLSORT(base, nmemb, size, less, gap);
            gap = ((gap+1)>>1)-1;
        } while(gap > cirua_2001[cirua_2001_size-1]);
    }
    for(size_t gap_index = cirua_2001_size; gap_index > 0; gap_index--){
        gap = cirua_2001[gap_index-1];
        if(gap >= nmemb){
            continue;
        }
        SHELLSORT(base, nmemb, size, less, gap);
    }
}
