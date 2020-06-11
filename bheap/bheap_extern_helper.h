// bheap_extern_helper.h
/*
 * Don't include ifndef guards so that multiple bheaps of 
 * different types can be declared (just be careful). 
 */

/* When using this header, put something like
 * #define BHEAP_TYPE int
 * #include "bheap.h"
 * 
 * (BHEAP_TYPE is not defined here)
 */
/* Either mark all functions as and only inlclude
 * this file in .c files, or mark all functions extern and
 * put all the BHEAP_TYPEs you want into a single
 * .c for all your other code to link against.
 *
 * By default, all functions will be marked so it's 
 * more convenient when you really just use one pq anyways.
 * If you want the extern version, use
 * make bheap_extern.h
 * If I actually need it someday, I'll make a .h to correspond
 * to bheap_extern.h
 * 
 * The downside to this macro abuse is that things like
 * function call type mismatch will invoke pages of compiler 
 * errors (flashbacks to C++ templates) :(
 */

#include <stdlib.h>
#include <stdbool.h>

#ifndef BHEAP_TYPE
#error
#endif

#define BHEAP_DEFINE(T)                                    \
    typedef struct bheap_ ## T{                            \
        T *arr;                                            \
        /* const function pointer to hopefully encourage inlining */\
        bool (*const less)(const T *, const T *);          \
        size_t size;                                       \
        size_t capacity;                                   \
    } bheap_ ## T;                                         \
                                                           \
void bheap_ ## T ## _init(bheap_ ## T *pq, size_t size){\
    pq->arr = malloc(size*sizeof(T));                      \
    pq->size = 0;                                          \
    pq->capacity = size;                                   \
}                                                          \
                                                           \
void bheap_ ## T ## _free(bheap_ ## T *pq){         \
    free(pq->arr);                                         \
    pq->arr = NULL;                                        \
}                                                          \
                                                           \
void bheap_ ## T ## _siftDown(bheap_ ## T *pq, size_t index){\
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
void bheap_ ## T ## _siftUp(bheap_ ## T *pq, size_t index){\
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
void bheap_ ## T ## _make_heap(bheap_ ## T *pq){    \
    /* Floyd's heap algorithm */                           \
    if(pq->size <= 1){                                     \
        return;                                            \
    }                                                      \
    size_t height = 0;                                     \
    for(size_t sz = pq->size >> 1; sz; height++, sz >>= 1){\
    }                                                      \
    for(size_t i=(1<<height)-2; i > 0; i--){              \
        bheap_ ## T ## _siftDown(pq, i);                   \
    }                                                      \
    bheap_ ## T ## _siftDown(pq, 0);                       \
}                                                          \
                                                           \
void bheap_ ## T ## _push(bheap_ ## T *pq, const T value){\
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
    (pq->arr)[pq->size] = value;                           \
    pq->size++;                                            \
    bheap_ ## T ## _siftUp(pq, pq->size-1);                \
}                                                          \
                                                           \
void bheap_ ## T ## _push_by_ref(bheap_ ## T *pq, const T *value){\
    bheap_ ## T ## _push(pq, *value);                      \
}                                                          \
                                                           \
void bheap_ ## T ## _pop(bheap_ ## T *pq){          \
    if(pq->size > 0){                                      \
        (pq->arr)[0] = (pq->arr)[pq->size-1];              \
        pq->size--;                                        \
        bheap_ ## T ## _siftDown(pq, 0);                   \
    }                                                      \
    else{                                                  \
        exit(EXIT_FAILURE);                                \
    }                                                      \
}                                                          \
                                                           \
/* BHEAP_DEFINE(T) */

#define BHEAP_DEFINE_HELPER(x) BHEAP_DEFINE(x)
BHEAP_DEFINE_HELPER(BHEAP_TYPE)
#undef BHEAP_TYPE
