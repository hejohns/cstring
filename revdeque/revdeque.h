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
            for(index_type i=0; i<(index_type)floor(sqrt(size)); i++){
                bin_list.emplace_back((index_type)floor(sqrt(size)));
            }
            bin_list.emplace_back(extra);
            bins = (index_type)floor(sqrt(size))+1;
        }
        else{ //size is pefect square
            bin_list.reserve(sqrt(size));
            for(index_type i=0; i<(index_type)sqrt(size); i++){
                bin_list.emplace_back((index_type)sqrt(size));
            }
            bins = (index_type)floor(sqrt(size));
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
        assert(start < end); //this has been the cause of many horrors :(
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
            reverse_bin_list(start_c.bin+1, end_c.bin); //reverse middle bins in bin_list
            if(bin_list[start_c.bin].contents.size()-start_c.pos < bin_list[start_c.bin].contents.size()/2
                    && end_c.pos < bin_list[end_c.bin].contents.size()/2){
                revert_small_range_across_two_bins(bin_list[start_c.bin], bin_list[end_c.bin], start_c.pos, end_c.pos);
            }
            else if(bin_list[start_c.bin].contents.size()-start_c.pos > bin_list[start_c.bin].contents.size()/2
                    && end_c.pos > bin_list[end_c.bin].contents.size()/2){
                if(start_c.pos == 0 && end_c.pos == bin_list[end_c.bin].contents.size()){
                    // do not call revert_large if bin1 and bin2 are whole reverts
                }
                else{
                    revert_large_range_across_two_bins(bin_list[start_c.bin], bin_list[end_c.bin], start_c.pos, end_c.pos);
                }
                // mark the two bins as reversed
                bin_list[start_c.bin].reversed = !bin_list[start_c.bin].reversed;
                bin_list[end_c.bin].reversed = !bin_list[end_c.bin].reversed;
                // swap bins in bin_list
                bin_list[start_c.bin].contents.swap(bin_list[end_c.bin].contents);
                bool tmp = bin_list[start_c.bin].reversed;
                bin_list[start_c.bin].reversed = bin_list[end_c.bin].reversed;
                bin_list[end_c.bin].reversed = tmp;
            }
            else{ //I don't know whats a good method here
                revert_small_range_across_two_bins(bin_list[start_c.bin], bin_list[end_c.bin], start_c.pos, end_c.pos);
            }
            bin_list[start_c.bin].contents.shrink_to_fit();
            bin_list[end_c.bin].contents.shrink_to_fit();
            balance(start_c.bin);
            balance(end_c.bin);
        }
    }
    private:
    coord loc(index_type pos){
        index_type bin = 0;
        while(pos >= bin_list[bin].contents.size()){
            pos -= bin_list[bin].contents.size(); 
            bin++;
        }
        return coord{bin, pos};
    }
    void revert_within_single_bin(bin& bin, index_type start_pos, index_type end_pos){
        if(end_pos-start_pos < bin.contents.size()/2){ //range to be reversed is relatively small
            if(bin.reversed){
                auto begin = bin.contents.rbegin();
                std::reverse(begin+start_pos, begin+end_pos);
            }
            else{
                auto begin = bin.contents.begin();
                std::reverse(begin+start_pos, begin+end_pos);
            }
        }
        else if(start_pos == 0 && end_pos == bin.contents.size()){
            bin.reversed = !bin.reversed;
        }
        else{
            if(!bin.reversed){
                auto begin = bin.contents.begin();
                auto end = bin.contents.end();
                (void)begin;
                (void)end;
#define REVERT_WITHIN_SINGLE_BIN_HELPER_FB(FRONT, BACK) \
            do{\
                if(start_pos < bin.contents.size()-end_pos){\
                    std::vector<T> tmp(begin, begin+start_pos);\
                    std::reverse(begin+end_pos, end);\
                    index_type bin_sz = (index_type)bin.contents.size();\
                    for(index_type i=0; i<start_pos; i++){\
                        bin.contents.pop_ ## FRONT();\
                    }\
                    for(index_type i=0; i < bin_sz-end_pos; i++){\
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
                    std::reverse(tmp.begin(), tmp.end());\
                    std::reverse(begin, begin+start_pos);\
                    index_type bin_sz = (index_type)bin.contents.size();\
                    for(index_type i=0; i < bin_sz-end_pos; i++){\
                        bin.contents.pop_ ## BACK();\
                    }\
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
                (void)begin;
                (void)end;
                REVERT_WITHIN_SINGLE_BIN_HELPER_FB(back, front);
            }
            bin.reversed = !bin.reversed;
        }
    }
    void revert_small_range_across_two_bins(bin& bin1, bin& bin2, index_type start_pos, index_type end_pos){
        if(bin1.contents.size()-start_pos < end_pos){
            if(!bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
#define REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(FRONT1, BACK1, FRONT2, BACK2) \
            do{\
                std::vector<T> tmp(begin1+start_pos, end1);\
                std::reverse(tmp.begin(), tmp.end());\
                std::reverse(begin2, begin2+end_pos);\
                index_type bin1_sz = (index_type)bin1.contents.size();\
                for(index_type i=0; i<bin1_sz-start_pos; i++){\
                    bin1.contents.pop_ ## BACK1();\
                }\
                for(index_type i=0; i < end_pos; i++){\
                    bin1.contents.emplace_ ## BACK1(bin2.contents.FRONT2());\
                    bin2.contents.pop_ ## FRONT2();\
                }\
                while(!tmp.empty()){\
                    bin2.contents.emplace_ ## FRONT2(tmp.back());\
                    tmp.pop_back();\
                }\
            } while(false)
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(front, back, front, back);
            }
            else if(!bin1.reversed && bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(front, back, back, front);
            }
            else if(bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(back, front, front, back);
            }
            else{
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(back, front, back, front);
            }
        }
        else{
            if(!bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
#define REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(FRONT1, BACK1, FRONT2, BACK2) \
            do{\
                std::vector<T> tmp(begin2, begin2+end_pos);\
                std::reverse(begin1+start_pos, end1);\
                index_type bin1_sz = (index_type)bin1.contents.size();\
                for(index_type i=0; i<end_pos; i++){\
                    bin2.contents.pop_ ## FRONT2();\
                }\
                for(index_type i=0; i < bin1_sz-start_pos; i++){\
                    bin2.contents.emplace_ ## FRONT2(bin1.contents.BACK1());\
                    bin1.contents.pop_ ## BACK1();\
                }\
                while(!tmp.empty()){\
                    bin1.contents.emplace_ ## BACK1(tmp.back());\
                    tmp.pop_back();\
                }\
            } while(false)
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(front, back, front, back);
            }
            else if(!bin1.reversed && bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(front, back, back, front);
            }
            else if(bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(back, front, front, back);
            }
            else{
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_SMALL_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(back, front, back, front);
            }
        }
    }
    void revert_large_range_across_two_bins(bin& bin1, bin& bin2, index_type start_pos, index_type end_pos){
        if(start_pos < bin2.contents.size()-end_pos){
            if(!bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
#define REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(FRONT1, BACK1, FRONT2, BACK2) \
            do{\
                std::vector<T> tmp(begin1, begin1+start_pos);\
                std::reverse(begin2+end_pos, end2);\
                index_type bin2_sz = (index_type)bin2.contents.size();\
                for(index_type i=0; i<start_pos; i++){\
                    bin1.contents.pop_ ## FRONT1();\
                }\
                for(index_type i=0; i < bin2_sz-end_pos; i++){\
                    bin1.contents.emplace_ ## FRONT1(bin2.contents.BACK2());\
                    bin2.contents.pop_ ## BACK2();\
                }\
                while(!tmp.empty()){\
                    bin2.contents.emplace_ ## BACK2(tmp.back());\
                    tmp.pop_back();\
                }\
            } while(false)
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(front, back, front, back);
            }
            else if(!bin1.reversed && bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(front, back, back, front);
            }
            else if(bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(back, front, front, back);
            }
            else{
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB(back, front, back, front);
            }
        }
        else{
            if(!bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
#define REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(FRONT1, BACK1, FRONT2, BACK2) \
            do{\
                std::vector<T> tmp(begin2+end_pos, end2);\
                std::reverse(tmp.begin(), tmp.end());\
                std::reverse(begin1, begin1+start_pos);\
                index_type bin2_sz = (index_type)bin2.contents.size();\
                for(index_type i=0; i<bin2_sz-end_pos; i++){\
                    bin2.contents.pop_ ## BACK2();\
                }\
                for(index_type i=0; i < start_pos; i++){\
                    bin2.contents.emplace_ ## BACK2(bin1.contents.FRONT1());\
                    bin1.contents.pop_ ## FRONT1();\
                }\
                while(!tmp.empty()){\
                    bin1.contents.emplace_ ## FRONT1(tmp.back());\
                    tmp.pop_back();\
                }\
            } while(false)
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(front, back, front, back);
            }
            else if(!bin1.reversed && bin2.reversed){
                auto begin1 = bin1.contents.begin();
                auto end1 = bin1.contents.end();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(front, back, back, front);
            }
            else if(bin1.reversed && !bin2.reversed){
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.begin();
                auto end2 = bin2.contents.end();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(back, front, front, back);
            }
            else{
                auto begin1 = bin1.contents.rbegin();
                auto end1 = bin1.contents.rend();
                auto begin2 = bin2.contents.rbegin();
                auto end2 = bin2.contents.rend();
                (void)begin1;
                (void)end1;
                (void)begin2;
                (void)end2;
                REVERT_LARGE_RANGE_ACROSS_TWO_BINS_HELPER_FBFB2(back, front, back, front);
            }
        }
    }
    void balance_push_left(index_type bin){
        if(bin == 0){
            return;
        }
        if(bin_list[bin].contents.size()/2 > size/bins){
            if(bin_list[bin-1].contents.size() < bin_list[bin].contents.size()){
                if(!bin_list[bin-1].reversed && !bin_list[bin].reversed){
#define BALANCE_PUSH_LEFT_HELPER_FBFB(FRONT1, BACK1, FRONT2, BACK2) \
                do{\
                    /*index_type bin_sz = bin_list[bin].contents.size()*/;\
                    for(index_type i=0; i < size/bins; i++){\
                        bin_list[bin-1].contents.emplace_ ## BACK1(bin_list[bin].contents.FRONT2());\
                        bin_list[bin].contents.pop_ ## FRONT2();\
                    }\
                } while(false)
                    BALANCE_PUSH_LEFT_HELPER_FBFB(front, back, front, back);
                }
                else if(!bin_list[bin-1].reversed && bin_list[bin].reversed){
                    BALANCE_PUSH_LEFT_HELPER_FBFB(front, back, back, front);
                }
                else if(bin_list[bin-1].reversed && !bin_list[bin].reversed){
                    BALANCE_PUSH_LEFT_HELPER_FBFB(back, front, front, back);
                }
                else{
                    BALANCE_PUSH_LEFT_HELPER_FBFB(back, front, back, front);
                }
                balance_push_left(bin-1);
            }
        }
    }
    void balance(index_type bin){ //not sure how to do this yet
        /*
         * Right now, I'm just trying to approximately equalize the "flow"
         * pushing to the right and pulling to the left should roughly balance
         */
        if(bin+1 == bins){
            /* the only time we push to the left */
            balance_push_left(bin);
            return;
        }
        if(bin_list[bin].contents.size() > 2*(size/bins)){
            if(bin_list[bin].contents.size() > bin_list[bin+1].contents.size()){
                if(!bin_list[bin].reversed && !bin_list[bin+1].reversed){
#define BALANCE_HELPER_FBFB(FRONT1, BACK1, FRONT2, BACK2) \
                do{\
                    /*index_type bin_sz = bin_list[bin].contents.size()*/;\
                    for(index_type i=0; i < size/bins; i += 2){\
                        bin_list[bin+1].contents.emplace_ ## FRONT2(bin_list[bin].contents.BACK1());\
                        bin_list[bin].contents.pop_ ## BACK1();\
                    }\
                } while(false)
                    BALANCE_HELPER_FBFB(front, back, front, back);
                }
                else if(!bin_list[bin].reversed && bin_list[bin+1].reversed){
                    BALANCE_HELPER_FBFB(front, back, back, front);
                }
                else if(bin_list[bin].reversed && !bin_list[bin+1].reversed){
                    BALANCE_HELPER_FBFB(back, front, front, back);
                }
                else{
                    BALANCE_HELPER_FBFB(back, front, back, front);
                }
            }
        }
        else if(bin_list[bin].contents.size() < (size/bins)/2){
            if(bin_list[bin].contents.size() < bin_list[bin+1].contents.size()){
                if(!bin_list[bin].reversed && !bin_list[bin+1].reversed){
#define BALANCE_HELPER_FBFB2(FRONT1, BACK1, FRONT2, BACK2) \
                do{\
                    index_type bin_sz = (index_type)bin_list[bin].contents.size();\
                    if(bin_list[bin+1].contents.size()/2 > size/bins){\
                        bin_sz = size/bins;\
                    }\
                    for(index_type i=0; i < bin_sz; i++){\
                        bin_list[bin].contents.emplace_ ## BACK1(bin_list[bin+1].contents.FRONT2());\
                        bin_list[bin+1].contents.pop_ ## FRONT2();\
                    }\
                } while(false)
                    BALANCE_HELPER_FBFB2(front, back, front, back);
                }
                else if(!bin_list[bin].reversed && bin_list[bin+1].reversed){
                    BALANCE_HELPER_FBFB2(front, back, back, front);
                }
                else if(bin_list[bin].reversed && !bin_list[bin+1].reversed){
                    BALANCE_HELPER_FBFB2(back, front, front, back);
                }
                else{
                    BALANCE_HELPER_FBFB2(back, front, back, front);
                }
            }
        }
        else{
            // do nothing
        }
    }
    void reverse_bin_list(index_type bin1, index_type bin2){
        if(bin2 == 0){
            return;
        }
        bin2--;
        for(; bin1 < bin2; bin1++, bin2--){
            bin_list[bin1].contents.swap(bin_list[bin2].contents);
            bool tmp = bin_list[bin1].reversed;
            bin_list[bin1].reversed = bin_list[bin2].reversed;
            bin_list[bin2].reversed = tmp;
        }
    }
    private:
    std::vector<bin> bin_list;
    index_type size;
    index_type bins;
};

#endif /* REVDEQUE_H */
