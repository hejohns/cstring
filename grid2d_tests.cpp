#include "grid2d.h"

int main(){
    grid2d<int> ar(10000, 10000);
    for(size_t i=0; i<ar.M; i++){
        for(size_t j=0; j<ar.N; j++){
            ar[i][j] = 1;
        }
    }
    return 0;
}
