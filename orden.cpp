#include <iostream>
#include <cstdlib>
#include <iomanip> //Necesario para fixed y setprecision
#include <ctime>
#include <random>
#include <algorithm>
#include "huffman.h"

using namespace std;

//Cambié la función para trabajar con punteros
int binarysearch(int* A, int l, int r, int num){
    int m;
    while (l <= r){
        m = l + (r - l) / 2;

        if(A[m] == num){
            return m;
        }
        if(A[m] < num){
            l = m + 1;
        }
        else{
            r = m - 1;
        }
    }

    return -1;
}

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
        else 
            return Sample;
    }
    return Sample;
}

//Limité la funcion de impresién del arreglo, para que se impriman solo los primeros y ultimos valores, y asi sea mas legible con
//los arreglos muy grandes.
void printArray(int* A, int n, int limit = 10){
    for (int i = 0; i < min(n, limit); i++) {
        cout << A[i] << " ";
    }
    if (n > limit) {
        cout << "... ";
        for (int i = max(n - limit, limit); i < n; i++) {
            cout << A[i] << " ";
        }
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

//Se añadió la función para crear el arreglo normal
int* arregloNormalGen(int n, int media, int ds){
    random_device rd{};
    mt19937 gen{rd()};

    int* A = new int[n];
    normal_distribution<> distribucion(media, ds);
    for (int i = 0; i < n; i++){
        A[i] = round(distribucion(gen));
    }

    sort(A, A + n);

    return A;
}

int main(){
    srand(time(NULL));

    // Se definieron variables más grandes (hay que cambiarlas para ingresarlas como usuario)
    int media = 5000, ds = 1000;
    int n = 1000000, e = 3, m = 100, b = n/m;//También modifiqué el b, que se supone que debe ser n/m.

    //Creación de los arreglos lineal y normal, implementando la búsqueda binaria y el sample y gap coded.
    //Solo falta el Binary Search de los arreglos con los gap y sample.
    int* arregloLineal = arregloLinealGen(n, e);
    int* arregloGapLineal = generarArregloGap(n, arregloLineal);
    int* arregloSampleLineal = generarArregloSample(n, arregloLineal, m, b);

    int* arregloNormal = arregloNormalGen(n, media, ds);
    int* arregloGapNormal = generarArregloGap(n, arregloNormal);
    int* arregloSampleNormal = generarArregloSample(n, arregloNormal, m, b);

    int buscar_lineal = arregloLineal[300000];
    int buscar_normal = arregloNormal[300000];

    cout <<endl<< "Arreglo Lineal: ";
    printArray(arregloLineal, n);

    //BINARY SEARCH PARA ARREGLO LINEAL

    double t0L = clock();
    int posL= binarysearch(arregloLineal, 0, n-1, buscar_lineal);
    double t1L = clock();
    double tL = (t1L-t0L)/CLOCKS_PER_SEC;

    if (posL == -1){
        cout << buscar_lineal  << " no se encuentra en el arreglo lineal" << endl;
    }
    else{
        cout << buscar_lineal << " está en el arreglo lineal, en la posición: " << posL << endl;
    }
    // Esto lo modifique un poco para que el resultado no se exprese con notación científica
    cout << fixed << setprecision(6) << "Se demoró " << tL << " segundos en hacer la búsqueda" << endl<<endl;
    
    cout << "Arreglo Lineal Gap-Coded: ";
    printArray(arregloGapLineal, n);
    
    cout << "Arreglo Lineal Sample: ";
    printArray(arregloSampleLineal, m);

    cout << endl;

    cout << "Arreglo Normal: ";
    printArray(arregloNormal, n);

    //BINARY SEARCH PARA ARREGLO NORMAL
    double t0N = clock();
    int posN = binarysearch(arregloNormal, 0, n-1, buscar_normal);
    double t1N = clock();
    double tN = (t1N-t0N)/CLOCKS_PER_SEC;

    if (posN == -1){
        cout << buscar_normal  << " no se encuentra en el arreglo normal" << endl;
    }
    else{
        cout << buscar_normal << " está en el arreglo normal, en la posición: " << posN << endl;
    }
    cout << fixed << setprecision(6) << "Se demoró " << tN << " segundos en hacer la búsqueda" << endl<<endl;

    cout << "Arreglo Normal Gap-Coded: ";
    printArray(arregloGapNormal, n);
    
    cout << "Arreglo Normal Sample: ";
    printArray(arregloSampleNormal, m);

    cout<<endl;
    huffman huff(arregloGapLineal, n);
    cout<<endl<< "Arbol de Huffman:"<< "\n";
    huff.print(huff.root);


    delete[] arregloSampleLineal;
    delete[] arregloSampleNormal;
    delete[] arregloGapLineal;
    delete[] arregloGapNormal;
    delete[] arregloLineal;
    delete[] arregloNormal;

    return 0;
}
