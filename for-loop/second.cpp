#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<algorithm>
#include "generador.hpp"
#include "second_block.hpp"

using namespace std;

int main(){

    int _size = 10000;
    int **arr = new int*[_size];
    for (int i = 0; i < _size; i++) {
        arr[i] = new int[_size];
    }

    int *y = new int[_size];
    int *x = new int[_size];
  
    int razon = _size/10;
    double time;

    ofstream salida{"second.txt", ios::out};

    //salida << "tamanho" << "\t" << "time\t" << endl;   

    for(size_t lenght = razon; lenght <= _size; lenght+=razon){

        llenar_matrix(arr, lenght, lenght);
        llenar_X(x, lenght);
        llenar_Y(y, lenght);
        auto begin = chrono::steady_clock::now();
        block(arr, y , x , lenght);
        auto end = chrono::steady_clock::now();
        time = double(chrono::duration_cast <chrono::microseconds> (end - begin).count());

        
        salida << lenght << "\t" << time << " \t" << endl;
        //cout << lenght << "\t" << time << " \t" << endl;       
    }

    return 0;
}