#ifndef GENERADOR_H
#define GENERADOR_H
#include<iostream>
#include<ctime>
#include<stdlib.h>

using namespace std;

void llenar_matrix(int **A , int n_filas, int n_columnas){
    int max = n_filas; 
    srand(time(0));
    for (int i=0; i<n_filas; i++){
        for(int j=0; j<n_columnas; j++){
            *(*(A+i)+j) = rand()% (2*max+1)-max;
        }
    }
}

void llenar_X(int *x, int size_){
    for (int i=0; i<size_; i++){
        x[i] = rand()% (2*size_+1)-size_;
    }
}

void llenar_Y(int y[], int size_){
    for (int i=0; i<size_; i++){
        y[i] = 0;
    }
}

#endif