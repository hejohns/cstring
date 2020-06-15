// revdeque.h
#ifndef REVDEQUE_H
#define REVDEQUE_H

#include <cstddef>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>
#include <cassert>

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
        assert(end != 0);
        coord start_c = loc(start);
        coord end_c = loc(end);
        if(end_c.pos == 0){
            end_c.bin--;
            end_c.pos = top[end_c.bin].contents.size;
        }
        if(start_c.bin < end_c.bin){
            revert_helper(top[start_c.bin], start_c.pos, top[start_c.bin].contents.size());
        }
        for(index_type i=start_c.bin+1; i < end_c.bin; i++){
            revert_helper(top[i], 0, top[i].contents.size());
        }
        if(true){
            revert_helper(top[end_c.bin], 0, end_c.pos);
        }
        std::reverse(top.begin()+start_c.bin, top.begin()+end_c.bin);
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
            if(start_pos < bin.contents.size()-end_pos){
                std::vector<T> tmp((std::vector<T>::size_type)start_pos);
                std::copy(bin.contents.begin(), bin.contents.begin()+start_pos, tmp.begin());
                bin.contents.erase(bin.contents.begin(), bin.contents.begin()+start_pos);
                for(index_type i=0; i < bin.contents.size()-end_pos; i++){
                    bin.contents.emplace_front(bin.contents.back());
                    bin.contents.pop_back();
                }
                for(index_type i=0; i < start_pos; i++){
                    bin.contents.emplace_back(tmp.back());
                    tmp.pop_back();
                }
                bin.reversed = !bin.reversed;
            }
            else{
                std::vector<T> tmp((std::vector<T>::size_type)bin.contents.size()-end_pos);
                std::copy(bin.contents.begin()+(end_pos-1), bin.contents.end(), tmp.begin());
                bin.contents.erase(bin.contents.begin()+(end_pos-1), bin.contents.end());
                for(index_type i=0; i < start_pos; i++){
                    bin.contents.emplace_back(bin.contents.front());
                    bin.contents.pop_front();
                }
                for(index_type i=0; i < bin.contents.size()-end_pos; i++){
                    bin.contents.emplace_front(tmp.back());
                    tmp.pop_back();
                }
                bin.reversed = !bin.reversed;
            }
        }
    }
    private:
    std::vector<bin> top;
    index_type size;
};

#endif /* REVDEQUE_H */
