// revdeque_test.cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "revdeque.h"

int main(){
    const size_t sz = 10000;
    revdeque<unsigned int, unsigned int> revdeque_inst(sz);
    std::vector<unsigned int> reference(sz);
    for(size_t i=0; i<sz; i++){
        revdeque_inst[i] = i;
        reference[i] = i;
    }
    revdeque_inst.revert(1, 190);
    std::reverse(reference.begin()+1, reference.begin()+190);
    for(size_t i=0; i<sz; i++){
        if(revdeque_inst[i] != reference[i]){
            std::cout << "Failed\n";
            assert(0);
            exit(EXIT_FAILURE);
        }
    }
    revdeque_inst.revert(0, 100);
    std::reverse(reference.begin(), reference.begin()+100);
    for(size_t i=0; i<sz; i++){
        if(revdeque_inst[i] != reference[i]){
            std::cout << "Failed\n";
            assert(0);
            exit(EXIT_FAILURE);
        }
    }
    revdeque_inst.revert(48, 152);
    std::reverse(reference.begin()+48, reference.begin()+152);
    for(size_t i=0; i<sz; i++){
        if(revdeque_inst[i] != reference[i]){
            std::cout << "Failed\n";
            assert(0);
            exit(EXIT_FAILURE);
        }
    }
    revdeque_inst.revert(49, 151);
    std::reverse(reference.begin()+49, reference.begin()+151);
    for(size_t i=0; i<sz; i++){
        if(revdeque_inst[i] != reference[i]){
            std::cout << "Failed\n";
            assert(0);
            exit(EXIT_FAILURE);
        }
    }
    /*
    revdeque_inst.revert(70, 110);
    std::reverse(reference.begin()+70, reference.begin()+110);
    revdeque_inst.revert(90, 110);
    std::reverse(reference.begin()+90, reference.begin()+110);
    revdeque_inst.revert(10, 90);
    std::reverse(reference.begin()+10, reference.begin()+90);
    revdeque_inst.revert(20, 80);
    std::reverse(reference.begin()+20, reference.begin()+80);
    revdeque_inst.revert(10, 580);
    std::reverse(reference.begin()+10, reference.begin()+580);
    revdeque_inst.revert(410, 580);
    std::reverse(reference.begin()+410, reference.begin()+580);
    revdeque_inst.revert(0, 100);
    std::reverse(reference.begin(), reference.begin()+100);
    revdeque_inst.revert(50, 150);
    std::reverse(reference.begin()+50, reference.begin()+150);
    revdeque_inst.revert(70, 110);
    std::reverse(reference.begin()+70, reference.begin()+110);
    revdeque_inst.revert(540, 545);
    std::reverse(reference.begin()+540, reference.begin()+545);
    revdeque_inst.revert(540, 545);
    std::reverse(reference.begin()+540, reference.begin()+545);
    revdeque_inst.revert(40, 545);
    std::reverse(reference.begin()+40, reference.begin()+545);
    revdeque_inst.revert(40, 595);
    std::reverse(reference.begin()+40, reference.begin()+595);
    revdeque_inst.revert(2, 99);
    std::reverse(reference.begin()+2, reference.begin()+99);
    revdeque_inst.revert(2, 101);
    std::reverse(reference.begin()+2, reference.begin()+101);
    revdeque_inst.revert(237, 737);
    std::reverse(reference.begin()+237, reference.begin()+737);
    revdeque_inst.revert(0, 999);
    std::reverse(reference.begin()+0, reference.begin()+999);
    revdeque_inst.revert(100, 199);
    std::reverse(reference.begin()+100, reference.begin()+199);
    revdeque_inst.revert(1, 9);
    std::reverse(reference.begin()+1, reference.begin()+9);
    revdeque_inst.revert(1, 100);
    std::reverse(reference.begin()+1, reference.begin()+100);
    */
    for(size_t i=0; i<sz; i++){
        if(revdeque_inst[i] != reference[i]){
            std::cout << "Failed\n";
            assert(0);
            exit(EXIT_FAILURE);
        }
    }
    std::cout << "Ok\n";
    return 0;
}
