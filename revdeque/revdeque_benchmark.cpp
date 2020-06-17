// revdeque_benchmark.cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "revdeque.h"

int main(){
    const size_t sz = 10*10;
    revdeque<unsigned int, unsigned int> revdeque_inst(sz);
    std::vector<unsigned int> reference(sz);
    for(size_t i=0; i<sz; i++){
        revdeque_inst[i] = i;
        reference[i] = i;
    }
    for(unsigned int h=0; h < 1<<1; h++){
        for(unsigned int i=sz-3; i >= 2; i--){
            for(unsigned int j=1; j+i < sz; j++){
                revdeque_inst.revert(j, j+i);
                std::reverse(reference.begin()+j, reference.begin()+j+i);
                for(unsigned int k=0; k<sz; k++){
                    if(revdeque_inst[k] != reference[k]){
                        std::cerr << "Failed\n";
                        assert(0);
                    }
                }
            }
        }
    }
    std::cout << "Ok\n";
    /*
    for(unsigned int i=0; i<sz; i++){
        std::cout<<revdeque_inst[i]<<' ';
    }
    */
    return 0;
}

