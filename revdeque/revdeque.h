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
            revert_within_single_bin(bin_list[start_c.bin], start_c.pos, end_c.pos);
        }
        else{
            // mark middle bins as reversed
            for(index_type i=start_c.bin+1; i < end_c.bin; i++){
                bin_list[i].reversed = !bin_list[i].reversed;
            }
            if(bin_list[start_c.bin].contents.size()-start_c.pos < bin_list[start_c.bin].contents.size()/2
                    && end_c.pos < bin_list[end_c.pos].contents.size()/2){
                revert_small_range_across_two_bins(bin_list[start_c.bin], bin_list[end_c.bin], start_c.pos, end_c.pos);
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
    void revert_within_single_bin(bin& bin, index_type start_pos, index_type end_pos){
        if(end_pos-start_pos < bin.contents.size()/2){ //range to be reversed is relatively small
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
#define REVERT_WITHIN_SINGLE_BIN_HELPER_FB(FRONT, BACk) \
            do{\
                if(start_pos < bin.contents.size()-end_pos){\
                    std::vector<T> tmp(begin, begin+start_pos);\
                    bin.contents.erase(begin, begin+start_pos);\
                    for(index_type i=0; i < bin.contents.size()-end_pos; i++){\
                        bin.contents.emplace_ ## FRONT(bin.contents.BACK());\
                        bin.contents.pop_ ## BACK();\
                    }\
                    while(!tmp.empty()){\
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
                    while(!tmp.empty()){\
                        bin.contents.emplace_ ## FRONT(tmp.back());\
                        tmp.pop_back();\
                    }\
                }\
            } while(false)
                REVERT_WITHIN_SINGLE_BIN_HELPER_FB(front, back);
            }
            else{
                auto begin = bin.contents.rbegin();
                auto end = bin.contents.rend();
                REVERT_WITHIN_SINGLE_BIN_HELPER_FB(back, front);
            }
            bin.reversed = !bin.reversed;
        }
    }
    void revert_small_range_across_two_bins(bin& bin1, bin& bin2, index_type start_pos, index_type end_pos){
        if(bin1.contents.size()-start_c.pos < end_c.pos){
            if(!bin_list[start_c.bin].reversed && !bin_list[end_c.bin].reversed){
                auto begin1 = bin_list[start_c.bin].contents.begin();
                auto end1 = bin_list[start_c.bin].contents.end();
                auto begin2 = bin_list[end_c.bin].contents.begin();
                auto end2 = bin_list[end_c.bin].contents.end();
#define REVDEQUE_REVERT_FBFB(FRONT1, BACK1, FRONT2, BACK2) \
            do{\
                std::vector<T> tmp(begin1+start_c.pos, end1);\
                bin_list[start_c.bin].contents.erase(begin1+start_c.pos, end1);\
                for(index_type i=0; i < end_c.pos; i++){\
                    bin_list[start_c.bin].contents.emplace_ ## BACK1(bin_list[end_c.bin].contents.FRONT2);\
                    bin_list[end_c.bin].contents.pop_ ## FRONT2();\
                }\
                while(!tmp.empty()){\
                    bin_list[end_c.bin].contents.emplace_ ## FRONT2(tmp.back());\
                    tmp.pop_back();\
                }\
            } while(false)
                REVDEQUE_REVERT_FBFB(front, back, front, back);
            }
            else if(!bin_list[start_c.bin].reversed && bin_list[end_c.bin].reversed){
                auto begin1 = bin_list[start_c.bin].contents.begin();
                auto end1 = bin_list[start_c.bin].contents.end();
                auto begin2 = bin_list[end_c.bin].contents.rbegin();
                auto end2 = bin_list[end_c.bin].contents.rend();
                REVDEQUE_REVERT_FBFB(front, back, back, front);
            }
            else if(bin_list[start_c.bin].reversed && !bin_list[end_c.bin].reversed){
                auto begin1 = bin_list[start_c.bin].contents.rbegin();
                auto end1 = bin_list[start_c.bin].contents.rend();
                auto begin2 = bin_list[end_c.bin].contents.begin();
                auto end2 = bin_list[end_c.bin].contents.end();
                REVDEQUE_REVERT_FBFB(back, front, front, back);
            }
            else{
                auto begin1 = bin_list[start_c.bin].contents.rbegin();
                auto end1 = bin_list[start_c.bin].contents.rend();
                auto begin2 = bin_list[end_c.bin].contents.rbegin();
                auto end2 = bin_list[end_c.bin].contents.rend();
                REVDEQUE_REVERT_FBFB(back, front, back, front);
            }
        }
        else{
            if(!bin_list[start_c.bin].reversed && !bin_list[end_c.bin].reversed){
                auto begin1 = bin_list[start_c.bin].contents.begin();
                auto end1 = bin_list[start_c.bin].contents.end();
                auto begin2 = bin_list[end_c.bin].contents.begin();
                auto end2 = bin_list[end_c.bin].contents.end();
#define REVDEQUE_REVERT_FBFB2(FRONT1, BACK1, FRONT2, BACK2) \
            do{\
                std::vector<T> tmp(begin2, begin2+end_c.pos);\
                bin_list[end_c.bin].contents.erase(begin2, begin2+end_c.pos);\
                for(index_type i=0; i < end_c.pos; i++){\
                    bin_list[end_c.bin].contents.emplace_ ## FRONT2(bin_list[start_c.bin].contents.BACK1);\
                    bin_list[start_c.bin].contents.pop_ ## BACK1();\
                }\
                while(!tmp.empty()){\
                    bin_list[start_c.bin].contents.emplace_ ## BACK1(tmp.back());\
                    tmp.pop_back();\
                }\
            } while(false)
                REVDEQUE_REVERT_FBFB2(front, back, front, back);
            }
            else if(!bin_list[start_c.bin].reversed && bin_list[end_c.bin].reversed){
                auto begin1 = bin_list[start_c.bin].contents.begin();
                auto end1 = bin_list[start_c.bin].contents.end();
                auto begin2 = bin_list[end_c.bin].contents.rbegin();
                auto end2 = bin_list[end_c.bin].contents.rend();
                REVDEQUE_REVERT_FBFB2(front, back, back, front);
            }
            else if(bin_list[start_c.bin].reversed && !bin_list[end_c.bin].reversed){
                auto begin1 = bin_list[start_c.bin].contents.rbegin();
                auto end1 = bin_list[start_c.bin].contents.rend();
                auto begin2 = bin_list[end_c.bin].contents.begin();
                auto end2 = bin_list[end_c.bin].contents.end();
                REVDEQUE_REVERT_FBFB2(back, front, front, back);
            }
            else{
                auto begin1 = bin_list[start_c.bin].contents.rbegin();
                auto end1 = bin_list[start_c.bin].contents.rend();
                auto begin2 = bin_list[end_c.bin].contents.rbegin();
                auto end2 = bin_list[end_c.bin].contents.rend();
                REVDEQUE_REVERT_FBFB2(back, front, back, front);
            }
        }
    }
    private:
    std::vector<bin> bin_list;
    index_type size;
};

#endif /* REVDEQUE_H */
