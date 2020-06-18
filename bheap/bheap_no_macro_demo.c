// bheap.c

#include "bheap_no_macros.h"

// max pq
bool less_int(const void* left, const void* right){
    return *(int*)left < *(int*)right;
}

int main(void){
    int ints[8] = {8, 3, 7, 2, 5, 9, 8, 10};
    bheap pq = {.arr = ints, .less = &less_int, .elt_size = sizeof(int), .size = 8, .capacity = 8};
    bheap_make_heap(&pq);
    bheap pq2 = {.less = &less_int, .elt_size = sizeof(int)};
    bheap_init(&pq2, 10);
    int tmp = 5;
    bheap_push(&pq2, &tmp);
    tmp = 3;
    bheap_push(&pq2, &tmp);
    tmp = 8;
    bheap_push(&pq2, &tmp);
    tmp = 1;
    bheap_push(&pq2, &tmp);
    tmp = 0;
    bheap_push(&pq2, &tmp);
    bheap_free(&pq2);
    return 0;
}
