#ifndef PRODUCT_HPP
#define PRODUCT_HPP

void product(int ** A, int **B,  int **C, int size_){
    for (int i = 0; i < size_; i++){
        for(int j = 0; j < size_; j++){
            for(int k = 0; k < size_; k++){
                *(*(C+i)+j) += *(*(A+i)+k) *  *(*(B+k)+j);
            }
        }
    }
    
}

#endif