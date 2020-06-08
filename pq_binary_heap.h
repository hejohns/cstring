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
#include <stdbool.h>

#ifndef PQ_BINARY_HEAP_TYPE
#error
#endif

#define PQ_BINARY_HEAP_DEFINE(T)                           \
    typedef struct pq_binary_heap_ ## T{                   \
        T *arr;                                            \
        /* const function pointer to hopefully encourage inlining */\
        bool (*const less)(const T *, const T *);          \
        size_t size;                                       \
        size_t capacity;                                   \
    } pq_binary_heap_ ## T;                                \
                                                           \
static void pq_binary_heap_ ## T ## _init(pq_binary_heap_ ## T *pq, size_t size){\
    pq->arr = malloc(size*sizeof(T));                      \
    pq->size = 0;                                          \
    pq->capacity = size;                                   \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _free(pq_binary_heap_ ## T *pq){\
    free(pq->arr);                                         \
    pq->arr = NULL;                                        \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _siftDown(pq_binary_heap_ ## T *pq, size_t index){\
    size_t index_lchild; /* left child or lesser child */  \
    while(2*index+1 <= pq->size-1){                        \
        index_lchild = 2*index+1;                          \
        if(index_lchild+1 <= pq->size-1){                  \
            if(pq->less(pq->arr+index_lchild, pq->arr+index_lchild+1)){\
                ++index_lchild;                            \
            }                                              \
        }                                                  \
        if(pq->less(pq->arr+index_lchild, pq->arr+index)){ \
            break;                                         \
        }                                                  \
        else{                                              \
            T tmp = (pq->arr)[index];                      \
            (pq->arr)[index] = (pq->arr)[index_lchild];    \
            (pq->arr)[index_lchild] = tmp;                 \
        }                                                  \
        index = index_lchild;                              \
    }                                                      \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _siftUp(pq_binary_heap_ ## T *pq, size_t index){\
    while(index != 0){                                     \
        if(pq->less(pq->arr+((index-1)/2), pq->arr+index)){\
            {                                              \
                T tmp = (pq->arr)[(index-1)/2];            \
                (pq->arr)[(index-1)/2] = (pq->arr)[index]; \
                (pq->arr)[index] = tmp;                    \
            }                                              \
            index = (index-1)/2;                           \
        }                                                  \
        else{                                              \
            break;                                         \
        }                                                  \
    }                                                      \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _make_heap(pq_binary_heap_ ## T *pq){\
    /* Floyd's heap algorithm */                           \
    if(pq->size <= 1){                                     \
        return;                                            \
    }                                                      \
    size_t height = 0;                                     \
    for(size_t sz = pq->size >> 1; sz; height++, sz >>= 1){\
    }                                                      \
    while(--height){                                       \
        for(size_t i=0; i < (2<<(height-1)); i++){         \
            pq_binary_heap_ ## T ## _siftDown(pq, (2<<(height-1))-1+i);\
        }                                                  \
    }                                                      \
    pq_binary_heap_ ## T ## _siftDown(pq, 0);              \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _push(pq_binary_heap_ ## T *pq, const T *value){\
    if(!(pq->size < pq->capacity)){                        \
        T* tmp = realloc(pq->arr, 2*(pq->size*sizeof(T))); \
        if(tmp){                                           \
            pq->arr = tmp;                                 \
            pq->capacity *= 2;                             \
        }                                                  \
        else{                                              \
            exit(EXIT_FAILURE);                            \
        }                                                  \
    }                                                      \
    (pq->arr)[pq->size] = *value;                          \
    pq->size++;                                            \
}                                                          \
                                                           \
static void pq_binary_heap_ ## T ## _pop(pq_binary_heap_ ## T *pq){\
    (pq->arr)[0] = (pq->arr)[pq->size-1];                  \
    pq->size--;                                            \
    pq_binary_heap_ ## T ## _siftDown(pq, 0);              \
}                                                          \
                                                           \
/* PQ_BINARY_HEAP_DEFINE(T) */

#define PQ_BINARY_HEAP_DEFINE_HELPER(x) PQ_BINARY_HEAP_DEFINE(x)
PQ_BINARY_HEAP_DEFINE_HELPER(PQ_BINARY_HEAP_TYPE)
#undef PQ_BINARY_HEAP_TYPE
