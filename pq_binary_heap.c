// pq_binary_heap.c
/* 
 * Test header preprocessor output
 */

// define the type of the stored elements here
#define PQ_BINARY_HEAP_TYPE int
#include "pq_binary_heap.h"
#define PQ_BINARY_HEAP_TYPE double
#include "pq_binary_heap.h"

int main(void){
    pq_binary_heap_int pq_int;
    pq_binary_heap_double pq_double;
    return 0;
}
