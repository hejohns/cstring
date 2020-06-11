#include <stdlib.h>
#include "shellsort++.h"

bool less_int(const void *left, const void *right){
    return *(int*)left < *(int*)right;
}

int main(void){
    const size_t arr_size = 1<<20;
    int* arr = malloc(arr_size*sizeof(int));
    srand(0);
    for(size_t i=0; i<arr_size; i++){
        arr[i] = rand()%1000;
    }
    shellsort(arr, arr_size, sizeof(int), &less_int);
    return 0;
}
