// pq_binary_heap.h
/*
 * Don't include ifndef guards so that multiple pq_binary_heaps of 
 * different types can be declared (just be careful). 
 */

/* When using this header, put something like
 * #define PQ_BINARY_HEAP_TYPE int
 * #include "pq_binary_heap.h"
 * 
 * (PQ_BINARY_HEAP_TYPE is not defined here)
 */
/* Either mark all functions as static and only inlclude
 * this file in .c files, or mark all functions extern and
 * put all the PQ_BINARY_HEAP_TYPEs you want into a single
 * .c for all your other code to link against.
 * By default, all functions will be marked static so it's 
 * more convenient when you really just use one pq anyways.
 */

#include <stdlib.h>

#ifndef PQ_BINARY_HEAP_TYPE
#error
#endif

#define PQ_BINARY_HEAP_DEFINE(T)                           \
    typedef struct pq_binary_heap_ ## T{                   \
        T *arr;                                            \
    } pq_binary_heap_ ## T;                                \
                                                           \
static void pq_binary_heap_ ## T ## _init(pq_binary_heap_ ## T *pq, size_t size){\
    pq->arr = malloc(size*sizeof(T));                      \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _free(pq_binary_heap_ ## T *pq){\
    free(pq->arr);                                         \
    pq->arr = NULL;                                        \
}

#define PQ_BINARY_HEAP_DEFINE_HELPER(x) PQ_BINARY_HEAP_DEFINE(x)
PQ_BINARY_HEAP_DEFINE_HELPER(PQ_BINARY_HEAP_TYPE)
#undef PQ_BINARY_HEAP_TYPE
