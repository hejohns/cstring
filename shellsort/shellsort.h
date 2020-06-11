#include <stddef.h>
#include <stdbool.h>

// parameter names/order based of qsort, but compar is incompatible with less
static void shellsort(void *base, size_t nmemb, size_t size,
        bool (*const less)(const void *, const void *)){
    // start with cirua_2001 gap, then just use (2^k)-1 for simplicity
    static const size_t cirua_2001_size = 8;
    static const size_t cirua_2001[cirua_2001_size] = {1, 4, 10, 23, 57, 132, 301, 701};
    if(nmemb >= 1<<12){
    }
    for(size_t gap_index = cirua_2001_size; gap_index > 0 && cirua_2001[gap_index-1] < nmemb; gap_index--){
        size_t gap = cirua_2001[gap_index-1];
        for(size_t i = 0; i < gap; i++){
            for(size_t j = i+gap; j < nmemb; j += gap){
                for(size_t k = j; k >= gap; k -= gap){
                    if(less(base+(k*size), base+((k-gap)*size))){
                        char tmp[size];
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
}
