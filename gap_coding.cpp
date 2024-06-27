#include <iostream>
#include <cstdlib>
#include "huffman.h"

using namespace std;


int* generarArregloGap(int n, int* A){
    int* Gap = new int[n];
    Gap[0] = A[0];
    for(int i = 1; i < n; i++){
        Gap[i] = A[i] - A[i-1];
    }
    return Gap;
}

int* generarArregloSample(int n, int* A, int m, int b){
    int* Sample = new int[m];
    int index = 0;
    for(int i = 0; i < n; i += b){
        if (index < m) {
            Sample[index++] = A[i];
        }
    }
    return Sample;
}

void printArray(int* A, int n){
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
}

int* arregloLinealGen(int n, int e){
    int* A = new int[n];
    A[0] = rand() % e;
    for (int i = 1; i < n; i++) {
        A[i] = A[i-1] + 1 + (rand() % e);
    }
    return A;
}

int main(){
    int n = 10, e = 3, m = 10, b = 8;
    int* arregloLineal = arregloLinealGen(n, e);
    int* arregloGap = generarArregloGap(n, arregloLineal);
    int* arregloSample = generarArregloSample(n, arregloLineal, m, b);
    
    cout << "Arreglo Lineal: ";
    printArray(arregloLineal, n);
    
    cout << "Arreglo Gap-Coded: ";
    printArray(arregloGap, n);
    
    cout << "Arreglo Sample: ";
    printArray(arregloSample, m);
    
    huffman huff(arregloGap, n);
    cout << "Arbol de Huffman:"<< "\n";
    huff.print(huff.root);
    

    delete[] arregloSample;
    delete[] arregloGap;
    delete[] arregloLineal;
    return 0;
}