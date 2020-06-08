// pq_binary_heap.c
/* 
 * Test header preprocessor output
 */

// define the type of the stored elements here
#define PQ_BINARY_HEAP_TYPE int
#include "pq_binary_heap.h"
#define PQ_BINARY_HEAP_TYPE double
#include "pq_binary_heap.h"

// max pq
bool less_int(const int* left, const int* right){
    return *left < *right;
}

// min pq
bool less_double(const double* left, const double* right){
    return *left > *right;
}

int main(void){
    pq_binary_heap_int pq_int = {.less=&less_int};
    pq_binary_heap_int_init(&pq_int, 8);
    pq_binary_heap_double pq_double = {.less=&less_double};
    pq_binary_heap_double_init(&pq_double, 8);
    return 0;
}
