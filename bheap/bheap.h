// bheap.h
#ifndef BHEAP_H
#define BHEAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BHEAP_GROWTH_FACTOR 2

/* cc -DBHEAP_USE_VLA to use vla/memcpy for BHEAP_SWAP
 * Default is as in glibc, to be safe and only use a char buffer
 */
#ifdef BHEAP_USE_VLA
#define BHEAP_SWAP(a, b, size)                             \
    do{                                                    \
        char tmp[size];                                    \
        memcpy(tmp, a, size);                              \
        memcpy(a, b, size);                                \
        memcpy(b, tmp, size);                              \
    } while(false)
#else
// from glibc's qsort SWAP macro
#define BHEAP_SWAP(a, b, size)                             \
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

typedef struct bheap{
    void *arr;
    /* const function pointer to hopefully encourage inlining */
    bool (*const less)(const void *, const void *);
    /* to enforce that element type should be known at compile time */
    const size_t elt_size;
    size_t size;
    size_t capacity;
} bheap;

static void bheap_init(bheap *const pq, size_t size){
    pq->arr = malloc(size*pq->elt_size);
    if(!pq->arr && size){ //malloc failure
        exit(EXIT_FAILURE);
    }
    pq->size = 0;
    pq->capacity = size;
}

static void bheap_free(bheap *const pq){
    free(pq->arr);
    pq->arr = NULL;
    pq->size = 0;
    pq->capacity = 0;
}

static void bheap_siftDown(bheap *const pq, size_t index){
    /* O(log(height of tree - height of index)) */
    size_t index_lchild; /* left child or lesser child */
    while(2*index+1 <= pq->size-1){
        index_lchild = 2*index+1;
        if(index_lchild+1 <= pq->size-1){
            if(pq->less(pq->arr + index_lchild*pq->elt_size, pq->arr + (index_lchild+1)*pq->elt_size)){
                index_lchild++;
            }
        }
        if(pq->less(pq->arr + index_lchild*pq->elt_size, pq->arr + index*pq->elt_size)){
            break;
        }
        else{
            BHEAP_SWAP((pq->arr + (index_lchild*pq->elt_size)), (pq->arr + (index*pq->elt_size)), pq->elt_size);
        }
        index = index_lchild;
    }
}

static void bheap_siftUp(bheap *const pq, size_t index){
    /* O(log(height of index)) */
    while(index != 0){
        if(pq->less(pq->arr+((index-1)/2)*pq->elt_size, pq->arr+index*pq->elt_size)){
            BHEAP_SWAP((pq->arr + (((index-1)/2)*pq->elt_size)), (pq->arr + (index*pq->elt_size)), pq->elt_size);
            index = (index-1)/2;
        }
        else{
            break;
        }
    }
}

static void bheap_make_heap(bheap *const pq){
    /* Floyd's heap algorithm */
    /* O(size) */
    if(pq->size <= 1){
        return;
    }
    size_t height = 0;
    for(size_t sz = pq->size >> 1; sz; height++, sz >>= 1){}
    for(size_t i=(1<<height)-2; i > 0; i--){
        bheap_siftDown(pq, i);
    }
    bheap_siftDown(pq, 0);
}

static void bheap_push(bheap *const pq, const void *value){
    /* O(log size) */
    if(!(pq->size < pq->capacity)){
        void *tmp = realloc(pq->arr, BHEAP_GROWTH_FACTOR*(pq->size*pq->elt_size));
        if(tmp){
            pq->arr = tmp;
            pq->capacity *= BHEAP_GROWTH_FACTOR;
        }
        else{
            exit(EXIT_FAILURE); //realloc failure
        }
    }
    memcpy(pq->arr + (pq->size)*pq->elt_size, value, pq->elt_size);
    pq->size++;
    bheap_siftUp(pq, pq->size-1);
}

static void bheap_pop(bheap *const pq){
    /* O(log size) */
    if(pq->size > 0){
        memcpy(pq->arr, pq->arr + (pq->size-1), pq->elt_size);
        pq->size--;
        bheap_siftDown(pq, 0);
    }
    else{
        exit(EXIT_FAILURE); //Can't pop from an empty heap
    }
}

static void heapsort(void *const base, size_t nmemb, size_t size,
        bool (*const less)(const void *, const void *)){
    bheap tmp = {.arr = base, .less = less, .elt_size = size, .size = nmemb};
    bheap_make_heap(&tmp);
    for(size_t i=nmemb-1; i > 0; i--){
        BHEAP_SWAP((tmp.arr + (i)*tmp.elt_size), tmp.arr, tmp.elt_size);
        tmp.size--;
        bheap_siftDown(&tmp, 0);
    }
}

#endif /* BHEAP_H */
