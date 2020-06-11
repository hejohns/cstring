#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>

bool less_int(const void *left, const void *right){
    return *(int*)left < *(int*)right;
}

int main(void){
    const size_t arr_size = 1<<20;
    std::vector<int> arr(arr_size);
    srand(0);
    for(size_t i=0; i<arr_size; i++){
        arr[i] = rand()%1000;
    }
    std::sort(arr.begin(), arr.end(), std::less<int>());
    return 0;
}
