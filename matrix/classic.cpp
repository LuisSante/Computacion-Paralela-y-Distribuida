#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<algorithm>
#include "generador.hpp"
#include "product.hpp"

using namespace std;

int main(){

    int _size = 10000;
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
  
    int razon = _size/10;
    double time;

    ofstream salida{"classic.txt", ios::out};

    salida << "tamanho" << "\t" << "time\t" << endl;   

    for(size_t lenght = razon; lenght <= _size; lenght+=razon){

        llenar(A, lenght, lenght);
        llenar(B, lenght, lenght);
        llenar_c(C, lenght, lenght);

        auto begin = chrono::steady_clock::now();
        product(A,B,C,lenght);
        auto end = chrono::steady_clock::now();
        time = double(chrono::duration_cast <chrono::microseconds> (end - begin).count());

        
        salida << lenght << "\t" << time << " ms\t" << endl;       
    }

    return 0;
}