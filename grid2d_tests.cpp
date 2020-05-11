#include "grid2d.h"

int main(){
    grid2d<int> ar(1000, 1000);
    ar.at(0,0) = 1;
    ar[1][1] = 2;
    return 0;
}
