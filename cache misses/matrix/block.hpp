#ifndef BLOCKED_HPP
#define BLOCKED_HPP

void product(int **A, int **B, int **C, int size_, const int block)
{
    for (int ii = 0; ii < size_; ii += block){
        for (int jj = 0; jj < size_; jj += block){
            for (int kk = 0; kk < size_; kk += block){
                for (int i = ii; i < ii + block; i++){
                    for (int j = jj; j < jj + block; j++){
                        for (int k = kk; k < kk + block; k++){
                            *(*(C+i)+j) += *(*(A+i)+k) *  *(*(B+k)+j);
                        }
                    }
                }
            }
        }
    }
}

#endif