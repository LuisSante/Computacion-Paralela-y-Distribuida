#ifndef _FIRST_BLOCK
#define _FIRST_BLOCK
 
void block(int **A, int *y, int *x, int size_){
    for(int i = 0; i < size_; i++){
        for(int j = 0; j < size_; j++){
            *(y+i) += *(*(A+i)+j) * *(x+j);
        }
    }
}

#endif