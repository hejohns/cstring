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
        explicit bin(index_type size) : reversed(false){
            contents.resize(size);
        }
        std::deque<T> contents;
        bool reversed;
    };
    struct coord{
        index_type bin;
        index_type pos;
    };
    explicit revdeque(index_type size) 
    : size(size){
        index_type extra = size-(index_type)(floor(sqrt(size)) * floor(sqrt(size)));
        if(extra > 0){ //tac extras on back
            bin_list.reserve(floor(sqrt(size))+1);
            for(index_type i=0; i<floor(sqrt(size)); i++){
                bin_list.emplace_back((index_type)floor(sqrt(size)));
            }
            bin_list.emplace_back(extra);
        }
        else{ //size is pefect square
            bin_list.reserve(sqrt(size));
            for(index_type i=0; i<sqrt(size); i++){
                bin_list.emplace_back((index_type)sqrt(size));
            }
        }
    }
    template <typename InputIterator>
    explicit revdeque(InputIterator start, InputIterator end){
        for(index_type i=0; start != end; i++){
        }
    }
    T& operator[](index_type pos){
        index_type bin = 0;
        while(pos >= bin_list[bin].contents.size()){
            pos -= bin_list[bin].contents.size(); 
            bin++;
        }
        if(bin_list[bin].reversed){
            return *(bin_list[bin].contents.rbegin()+pos);
        }
        else{
            return bin_list[bin].contents[pos];
        }
    }
    void revert(index_type start, index_type end){ //[start, end)
        assert(end != 0);
        coord start_c = loc(start);
        coord end_c = loc(end);
        if(end_c.pos == 0){
            end_c.bin--;
            end_c.pos = bin_list[end_c.bin].contents.size();
        }
        if(start_c.bin == end_c.bin){
            revert_helper(bin_list[start_c.bin], start_c.pos, end_c.pos);
        }
        else{
            // mark middle bins as reversed
            for(index_type i=start_c.bin+1; i < end_c.bin; i++){
                bin_list[i].reversed = !bin_list[i].reversed;
            }
            if(bin_list[start_c.bin].contents.size()-start_c.pos < bin_list[start_c.bin].contents.size()/2
                    && end_c.pos < bin_list[end_c.pos].contents.size()/2){
                if(bin_list[start_c.bin].contents.size()-start_c.pos < ){
                }
                else{
                }
            }
            else if(bin_list[start_c.bin].contents.size()-start_c.pos > bin_list[start_c.bin].contents.size()/2
                    && end_c.pos > bin_list[end_c.pos].contents.size()/2){
                if(start_c.pos < bin_list[end_c.pos].contents.size()-end_c.pos){
                    std::vector<T> tmp(bin_list[start_c].contents.begin(), bin_list[start_c].contents.begin()+start_c.pos);
                    bin_list[start_c.bin].contents.erase(bin_list[start_c.bin].contents.begin(), bin_list[start_c].contents.begin()+start_c.pos);
                    for(index_type i=0; i < bin_list[end_c.bin].contents.size()-end_c.pos){
                    }
                }
                else{
                }
                bin tmp = bin_list[start_c.bin];
                bin_list[start_c.bin] = bin_list[end_c.bin];
                bin_list[end_c.bin] = tmp;
            }
            else{
            }
        }
    }
    private:
    coord loc(index_type pos){
        index_type bin = 0;
        while(pos >= bin_list[bin].contents.size()){
            pos -= bin_list[bin].contents.size(); 
            bin++;
        }
        return coord{.bin = bin, .pos = pos};
    }
    void revert_helper(bin& bin, index_type start_pos, index_type end_pos){
        if(end_pos-start_pos < bin.contents.size()/2){
            auto begin = (bin.reversed)? bin.contents.rbegin() : bin.contents.begin();
            std::reverse(begin+start_pos, begin+end_pos);
        }
        else if(start_pos == 0 && end_pos == bin.contents.size()){
            bin.reversed = !bin.reversed;
        }
        else{
            if(!bin.reversed){
                auto begin = bin.contents.begin();
                auto end = bin.contents.end();
#define REVDEQUE_HELPER_FB(FRONT, BACk) \
            do{\
                if(start_pos < bin.contents.size()-end_pos){\
                    std::vector<T> tmp(begin, begin+start_pos);\
                    bin.contents.erase(begin, begin+start_pos);\
                    for(index_type i=0; i < bin.contents.size()-end_pos; i++){\
                        bin.contents.emplace_ ## FRONT(bin.contents.BACK());\
                        bin.contents.pop_ ## BACK();\
                    }\
                    for(index_type i=0; i < start_pos; i++){\
                        bin.contents.emplace_ ## BACK(tmp.back());\
                        tmp.pop_back();\
                    }\
                }\
                else{\
                    std::vector<T> tmp(begin+end_pos, end);\
                    bin.contents.erase(begin+end_pos, end);\
                    for(index_type i=0; i < start_pos; i++){\
                        bin.contents.emplace_ ## BACK(bin.contents.FRONT());\
                        bin.contents.pop_ ## FRONT();\
                    }\
                    for(index_type i=0; i < bin.contents.size()-end_pos; i++){\
                        bin.contents.emplace_ ## FRONT(tmp.back());\
                        tmp.pop_back();\
                    }\
                }\
            } while(false)
                REVDEQUE_HELPER_FB(front, back);
            }
            else{
                auto begin = bin.contents.rbegin();
                auto end = bin.contents.rend();
                REVDEQUE_HELPER_FB(back, front);
            }
            bin.reversed = !bin.reversed;
        }
    }
    private:
    std::vector<bin> bin_list;
    index_type size;
};

#endif /* REVDEQUE_H */
