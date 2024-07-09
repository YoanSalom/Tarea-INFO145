#include <iostream>
#include <cstdlib>
#include <iomanip> //Necesario para fixed y setprecision
#include <ctime>
#include <random>
#include <algorithm>
#include "huffman.h"

using namespace std;

//Busqueda binaria recursiva
int binarySearch(int* A, int l, int r, int m ,int num){
    if(l > r) return -1;
    else if (A[m] == num) return m;
    else if (A[m] < num) return binarySearch(A,m+1,r,((m+1) + r)/2, num);
    else return binarySearch(A,l,m-1,(l+(m-1))/2, num);
}

//Crea el arreglo con los gaps
int* generarArregloGap(int n, int* A){
    int* Gap = new int[n];
    Gap[0] = A[0];
    for(int i = 1; i < n; i++){
        Gap[i] = A[i] - A[i-1];
    }
    return Gap;
}

//Crea los valores del arreglo sample
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


//Genera los valores del arreglo lineal
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
    int posL= binarySearch(A, l, r, l + (r - l) / 2, elem);
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
    int sample_index = binarySearch(sample, 0, m - 1, (m-1)/2 , elem);
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
    
    // Se definen las variables
    int media , ds; // media = media aritmetica, ds = desviacion estandar
    int n , e , m , b, seed; // n = numero de elementos en los array, e = Epsilon para generar los elementos del array lineal, m = es el valor de gap, seed = para calcular los numeros aleatorios
    

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
    }while ( n%m != 0 || m >= n);

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

    int buscar_lineal = rand() % arregloLineal[n-1];
    cout << "Se buscara el valor " << buscar_lineal << " en el arreglo lineal" << endl;

    int buscar_normal = rand() % arregloNormal[n-1];
    cout << "Se buscara el valor " << buscar_normal << " en el arreglo normal" << endl;

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
