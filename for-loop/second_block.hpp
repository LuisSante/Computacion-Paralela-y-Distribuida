#ifndef SECOND_BLOCK_HPP
#define SECOND_BLOCK_HPP

void block(int **A, int *y, int *x, int size_){
    for(int j = 0; j < size_; j++){
        for(int i = 0; i < size_; i++){
            *(y+i) += *(*(A+i)+j) * *(x+j);
        }
    } 
}

#endif