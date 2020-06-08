// pq_bh.c
/* 
 * Test header preprocessor output
 */

// define the type of the stored elements here
#define PQ_BH_TYPE int
#include "pq_bh.h"
#define PQ_BH_TYPE double
#include "pq_bh.h"

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
    pq_bh_int pq_int = {.less=&less_int};
    pq_bh_int_init(&pq_int, 8);
    pq_bh_int_push_by_ref(&pq_int, &ints[0]);
    pq_bh_int_push_by_ref(&pq_int, &ints[1]);
    pq_bh_int_push_by_ref(&pq_int, &ints[2]);
    pq_bh_int_push_by_ref(&pq_int, &ints[3]);
    pq_bh_int_push_by_ref(&pq_int, &ints[4]);
    pq_bh_int_push_by_ref(&pq_int, &ints[5]);
    pq_bh_int_push_by_ref(&pq_int, &ints[6]);
    pq_bh_int_push_by_ref(&pq_int, &ints[7]);
    pq_bh_double pq_double = {.less=&less_double};
    pq_bh_double_init(&pq_double, 8);
    memcpy(pq_double.arr, doubles, 8*sizeof(double));
    pq_double.size = 8;
    pq_bh_double_make_heap(&pq_double);
    /* free the pqs */
    pq_bh_int_free(&pq_int);
    pq_bh_double_free(&pq_double);
    return 0;
}
