// bheap_extern.h

#include <stddef.h>
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
void bheap_ ## T ## _init(bheap_ ## T *pq, size_t size);   \
                                                           \
void bheap_ ## T ## _free(bheap_ ## T *pq);                \
                                                           \
void bheap_ ## T ## _siftDown(bheap_ ## T *pq, size_t index);\
                                                           \
void bheap_ ## T ## _siftUp(bheap_ ## T *pq, size_t index);\
                                                           \
void bheap_ ## T ## _make_heap(bheap_ ## T *pq);           \
                                                           \
void bheap_ ## T ## _push(bheap_ ## T *pq, const T value); \
                                                           \
void bheap_ ## T ## _push_by_ref(bheap_ ## T *pq, const T *value);\
                                                           \
void bheap_ ## T ## _pop(bheap_ ## T *pq);                 \
                                                           \
/* BHEAP_DEFINE(T) */

#define BHEAP_DEFINE_HELPER(x) BHEAP_DEFINE(x)
BHEAP_DEFINE_HELPER(BHEAP_TYPE)
#undef BHEAP_TYPE
