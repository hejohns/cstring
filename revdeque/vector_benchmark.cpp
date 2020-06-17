// vector_benchmark.cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "revdeque.h"

int main(){
    const size_t sz = 50*50;
    std::vector<unsigned int> reference(sz);
    for(size_t i=0; i<sz; i++){
        reference[i] = i;
    }
    for(unsigned int h=0; h < 1<<1; h++){
        for(unsigned int i=sz-3; i >= 2; i--){
            for(unsigned int j=1; j+i < sz; j++){
                std::reverse(reference.begin()+j, reference.begin()+j+i);
            }
        }
    }
    for(unsigned int i=0; i<sz; i++){
        std::cout<<reference[i]<<' ';
    }
    return 0;
}

