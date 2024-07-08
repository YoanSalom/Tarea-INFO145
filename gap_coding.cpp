#include <iostream>
#include <cstdlib>
#include "huffman.h"

using namespace std;


//Crea el arreglo con los gap
int* generarArregloGap(int n, int* A){
    int* Gap = new int[n];
    Gap[0] = A[0];
    for(int i = 1; i < n; i++){
        Gap[i] = A[i] - A[i-1];
    }
    return Gap;
}

//Crea el arreglo de los samples
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


//Imprime los valores dentro del array
void printArray(int* A, int n){
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
}

//Genera los valores que estan dentro del arreglo lineal 
int* arregloLinealGen(int n, int e){
    int* A = new int[n];
    A[0] = rand() % e;
    for (int i = 1; i < n; i++) {
        A[i] = A[i-1] + 1 + (rand() % e);
    }
    return A;
}

int main(){
    int n, e, m, b, seed;

    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    cout << "Ingrese la Seed para generar numeros aleatorios: ";
    cin >> seed;
    srand(seed);

    cout << "Ingrese Epsilon para generar numeros aleatorios: ";
    cin >> e;

    do{
        cout << "Ingrese Valor para m (n tiene que ser divisible por m): ";
        cin >> m;
    }while ( n%m != 0 && m >= n);

    b = n/m;


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
    huff.print(huff.rootC);
    unsigned short int* codesArr = new unsigned short int[(huff.huffmanCodes).size()];
    for (int i = 0; i < (huff.huffmanCodes).size(); i++)
    {
        codesArr[i] = get<1>(huff.huffmanCodes[i]);
    }


    for (int i = 0; i < (huff.huffmanCodes).size(); i++)
    {
        cout << huff.decodeHuffman(codesArr[i], huff.huffmanCodes, huff.c, huff.f) << "\n";
    }

    huff.~huffman();
    delete[] arregloSample;
    delete[] arregloGap;
    delete[] arregloLineal;
    delete[] codesArr;
    return 0;
}