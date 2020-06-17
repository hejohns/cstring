// vector_benchmark.cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "revdeque.h"

int main(){
    const size_t sz = 300*300;
    std::vector<unsigned int> reference(sz);
    for(size_t i=0; i<sz; i++){
        reference[i] = i;
    }
    for(unsigned int h=0; h < 1<<1; h++){
        for(unsigned int i=sz-3; i >= 2; i--){
            for(auto j=reference.begin()+1; j+i < reference.end(); j++){
                std::reverse(j, j+i);
            }
        }
    }
    for(auto it = reference.begin(); it != reference.end(); it++){
        std::cout<<*it<<' ';
    }
    return 0;
}

