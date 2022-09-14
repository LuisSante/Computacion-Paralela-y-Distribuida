#ifndef GENERADOR_HPP
#define GENERADOR_HPP

void llenar(int **A , int n_filas, int n_columnas){
    int max = n_filas; 
    srand(time(0));
    for (int i=0; i<n_filas; i++){
        for(int j=0; j<n_columnas; j++){
            *(*(A+i)+j) = rand()% (2*max+1)-max;
        }
    }
}

void llenar_c(int **C , int n_filas, int n_columnas){
    for (int i=0; i<n_filas; i++){
        for(int j=0; j<n_columnas; j++){
            *(*(C+i)+j) = 0;
        }
    }
}

#endif