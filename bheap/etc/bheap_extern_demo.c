#define BHEAP_TYPE int
#include "bheap_extern.h"
#define BHEAP_TYPE double
#include "bheap_extern.h"

#include <string.h>

// max pq
bool less_int(const int* left, const int* right){
    return *left < *right;
}

// min pq
bool less_double(const double* left, const double* right){
    return *left > *right;
}

int main(void){
    int ints[8] = {8, 3, 7, 2, 5, 9, 8, 10};
    double doubles[8] = {8, 3, 7, 2, 5, 9, 8, 10};
    bheap_int pq_int = {.less=&less_int};
    bheap_int_init(&pq_int, 8);
    bheap_int_push_by_ref(&pq_int, &ints[0]);
    bheap_int_push_by_ref(&pq_int, &ints[1]);
    bheap_int_push_by_ref(&pq_int, &ints[2]);
    bheap_int_push_by_ref(&pq_int, &ints[3]);
    bheap_int_push_by_ref(&pq_int, &ints[4]);
    bheap_int_push_by_ref(&pq_int, &ints[5]);
    bheap_int_push_by_ref(&pq_int, &ints[6]);
    bheap_int_push_by_ref(&pq_int, &ints[7]);
    bheap_double pq_double = {.less=&less_double};
    bheap_double_init(&pq_double, 8);
    memcpy(pq_double.arr, doubles, 8*sizeof(double));
    pq_double.size = 8;
    bheap_double_make_heap(&pq_double);
    /* make pq from existing array */
    // just don't push past size or a realloc on an array will occur
    bheap_int pq_int_exist = {.arr=ints, .less=&less_int, .size=8, .capacity=8};
    bheap_int_make_heap(&pq_int_exist);
    /* free the pqs */
    bheap_int_free(&pq_int);
    bheap_double_free(&pq_double);
    bheap_int_free(&pq_int);
    return 0;
}
