#include <iostream>
#include <cstdlib>
#include <iomanip> //Necesario para fixed y setprecision
#include <ctime>
#include <random>
#include <algorithm>
#include "huffman.h"

using namespace std;

//Cambié la función para trabajar con punteros
int binarySearch(int* A, int l, int r, int num){
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
//Esta función imprime el tiempo de búsqueda, llamando a la funcion que busca, es pura estética, para que esté
//más ordenado y no hayan tantas cosas en el main
void imprimeTiempoBusqueda(int *A, int l, int r, int elem, string type){
    double t0L = clock();
    int posL= binarySearch(A, l, r, elem);
    double t1L = clock();
    double tL = (t1L-t0L)/CLOCKS_PER_SEC;

    cout<<endl;
    if (posL == -1){
        cout <<"El elemento: "<< elem  << " no se encuentra en el " <<type<< endl;
    }
    else{
        cout <<"El elemento: "<< elem << " está en el "<<type<<", en la posición: " << posL << endl;
    }
    // Esto lo modifique un poco para que el resultado no se exprese con notación científica
    cout << fixed << setprecision(6) << "Se demoró " << tL << " segundos en hacer la búsqueda" << endl<<endl;
}

//Se implementa el binary search para el sample con el gap
int binarySearchGapWithSample(int* gap, int* sample, int n, int m, int elem, int b) {
    //Primero, verificamos que esté en el sample
    int sample_index = binarySearch(sample, 0, m - 1, elem);
    if (sample_index != -1) {
        return sample_index * b;
    }

    //Encontramos el rango correcto en el sample
    int l = 0, r = m - 1, mid;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (sample[mid] < elem) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    //Buscamos en el rango del gap array
    int start = r * b;
    int end;
    if (l < m) {
        end = l * b;
    } else {
        end = n - 1;
    }
    int current_value = gap[0];

    for (int i = 1; i <= start; ++i) {
        current_value += gap[i];
    }

    for (int i = start + 1; i <= end; ++i) {
        current_value += gap[i];
        if (current_value == elem) {
            return i;
        }
        if (current_value > elem) {
            break;
        }
    }

    return -1; // No se encontró el elemento
}

//Esta función imprime el tiempo de búsqueda, llamando a la funcion que busca, es pura estética, para que esté
//más ordenado y no hayan tantas cosas en el main
void imprimeTiempoBusquedaSample(int* gap, int* sample, int n, int m, int elem, int b, string type){
    double t0L = clock();
    int posL= binarySearchGapWithSample(gap, sample, n, m, elem, b);
    double t1L = clock();
    double tL = (t1L-t0L)/CLOCKS_PER_SEC;

    cout<<endl;
    if (posL == -1){
        cout <<"El elemento: "<< elem  << " no se encuentra con las estructuras Sample y Gap" <<type<< endl;
    }
    else{
        cout <<"El elemento: "<< elem << " se encuentra con las estructuras Sample y Gap "<<type<<", en la posición: " << posL << endl;
    }
    // Esto lo modifique un poco para que el resultado no se exprese con notación científica
    cout << fixed << setprecision(6) << "Se demoró " << tL << " segundos en hacer la búsqueda" << endl<<endl;

}

int main(){
    
    // Se definieron variables más grandes
    int media = 5000, ds = 1000;
    int n = 1000000, e = 5, m = 100, b = n/m, seed;//También modifiqué el b, que se supone que debe ser n/m.

    //Este bloque pide el ingreso de los valores que se usaran para funcionamiento de los algoritmos
    cout << "Ingrese la cantidad de elementos (ej: 1000000): ";
    cin >> n;

    cout << "\nIngrese la Seed para generar los elementos: ";
    cin >> seed;
    srand(seed);

    cout << "\nIngrese Epsilon para generar los elementos del arreglo lineal: ";
    cin >> e;

    do{
        cout << "\nIngrese Valor para gap (n tiene que ser divisible por el gap): ";
        cin >> m;
    }while ( n%m != 0 && m >= n);

    b = n/m;

    cout << "\nIngrese la Media para generar los elementos del arreglo normal(ej: 5000): ";
    cin >> media;

    cout << "\nIngrese la Desviacion estandar para generar los elementos del arreglo normal(ej: 1000): ";
    cin >> ds;

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
    imprimeTiempoBusqueda(arregloLineal, 0, n-1, buscar_lineal, "Arreglo Lineal");

    cout << "Arreglo Lineal Gap-Coded: ";
    printArray(arregloGapLineal, n);
    
    cout << "Arreglo Lineal Sample: ";
    printArray(arregloSampleLineal, m);

    imprimeTiempoBusquedaSample(arregloGapLineal,arregloSampleLineal, n, m, buscar_lineal, b, "Arreglo Lineal");

    cout << endl;

    cout << "Arreglo Normal: ";
    printArray(arregloNormal, n);

    //BINARY SEARCH PARA ARREGLO NORMAL
    imprimeTiempoBusqueda(arregloNormal, 0, n-1, buscar_normal, "Arreglo Normal");

    cout << "Arreglo Normal Gap-Coded: ";
    printArray(arregloGapNormal, n);
    
    cout << "Arreglo Normal Sample: ";
    printArray(arregloSampleNormal, m);

    imprimeTiempoBusquedaSample(arregloGapNormal,arregloSampleNormal, n, m, buscar_normal, b, "Arreglo Normal");

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
