#include "qsort_vla.h"

int less_int(const void *left, const void *right, const void *arg){
    return *(int*)left - *(int*)right;
}

int main(void){
    const size_t arr_size = 1<<20;
    int* arr = malloc(arr_size*sizeof(int));
    srand(0);
    for(size_t i=0; i<arr_size; i++){
        arr[i] = rand()%1000;
    }
    qsort_vla(arr, arr_size, sizeof(int), &less_int, NULL);
    return 0;
}
