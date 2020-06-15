// revdeque.h
#ifndef REVDEQUE_H
#define REVDEQUE_H

#include <cstddef>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>

template <typename T, typename index_type = size_t>
class revdeque{
    public:
    struct bin{
        //bin() : reversed(false){}
        explicit bin(index_type size) : contents{size}, reversed(false){}
        std::deque<T> contents;
        bool reversed;
    };
    struct coord{
        index_type bin;
        index_type pos;
    };
    explicit revdeque(index_type size) 
    : size(size){
        top.reserve(floor(sqrt(size))+1);
        for(index_type i=0; i<floor(sqrt(size)); i++){
            top.emplace_back((index_type)floor(sqrt(size)));
        }
        top.emplace_back(size-(index_type)(
                    floor(sqrt(size)) * floor(sqrt(size))
                    ));
    }
    template <typename InputIterator>
    explicit revdeque(InputIterator start, InputIterator end){
        for(index_type i=0; start != end; i++){
        }
    }
    T& operator[](index_type pos){
        index_type bin = 0;
        while(pos >= top[bin].size()){
            pos -= top[bin].size(); 
            bin++;
        }
        if(top[bin].reversed){
            return *(top[bin].contents.rbegin()+pos);
        }
        else{
            return top[bin].contents[pos];
        }
    }
    void revert(index_type start, index_type end){ //[start, end)
        coord start_c = loc(start);
        coord end_c = loc(end);
    }
    private:
    coord loc(index_type pos){
        coord ret = { .bin = 0, .pos = 0};
        while(pos >= top[bin].size()){
            pos -= top[bin].size(); 
            ret.bin++;
        }
        ret.pos = pos;
        return ret;
    }
    void revert_helper(bin& bin, index_type start_pos, index_type end_pos){
        if(end_pos-start_pos < bin.contents.size()/2){
            std::reverse(bin.contents.begin()+start_pos, bin.contents.begin()+end_pos);
        }
        else if(start_pos == 0 && end_pos == bin.contents.size()){
            bin.reversed = !bin.reversed;
        }
        else{
            if(start_c.pos < bin.contents.size()-end_c.pos){
            }
            else{
            }
        }
    }
    private:
    std::vector<bin> top;
    index_type size;
};

#endif /* REVDEQUE_H */
