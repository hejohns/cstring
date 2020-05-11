//grid2d.h
#ifndef GRID_2D_H
#define GRID_2D_H

#include <cstddef>

template <typename T>
struct grid2d{
    public:
        grid2d(const size_t M, const size_t N)
        : M(M), N(N), array(new T*[M]){
            for(size_t i=0; i<M; i++){
                array[i] = new T[N];
            }
        }
        ~grid2d(){
            for(size_t i=0; i<M; i++){
                delete[] array[i];
            }
            delete[] array;
        }
        inline T& at(const size_t M, const size_t N){
            return array[M][N];
        }
        inline T* operator[](size_t M){
            return array[M];
        }
        const size_t M;
        const size_t N;
    private:
        T** const array;
};

#endif /* GRID_2D_H */
