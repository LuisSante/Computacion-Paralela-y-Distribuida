#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<algorithm>
#include "generador.hpp"
#include "block.hpp"

using namespace std;

int main(){

    int _size = 5000;
    int **A = new int*[_size];
    for (int i = 0; i < _size; i++) {
        A[i] = new int[_size];
    }

    int **B = new int*[_size];
    for (int i = 0; i < _size; i++) {
        B[i] = new int[_size];
    }

    int **C = new int*[_size];
    for (int i = 0; i < _size; i++) {
        C[i] = new int[_size];
    }
  
    const int razon = _size/5;
    const int block = 10;
    double time;

    ofstream salida{"block.txt", ios::out};

    for(size_t lenght = razon; lenght <= _size; lenght+=razon){

        llenar(A, lenght, lenght);
        llenar(B, lenght, lenght);
        llenar_c(C, lenght, lenght);

        auto begin = chrono::steady_clock::now();
        product(A,B,C,lenght, block);
        auto end = chrono::steady_clock::now();
        time = double(chrono::duration_cast <chrono::microseconds> (end - begin).count());

        
        salida << lenght << "\t" << time << " \t" << endl;       
    }
    for(int i=0; i<_size; i++){
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}