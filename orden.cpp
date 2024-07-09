#include <iostream>
#include "huffman.h"
#include "array_ini.h"
#include "search_functions.h"

using namespace std;


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
    cout << "Tamaño: " << n*sizeof(arregloLineal[0]) << endl;

    //BINARY SEARCH PARA ARREGLO LINEAL
    imprimeTiempoBusqueda(arregloLineal, 0, n-1, buscar_lineal, "Arreglo Lineal");

    cout << "Arreglo Lineal Gap-Coded: ";
    printArray(arregloGapLineal, n);
    cout << "Tamaño: " << n*sizeof(arregloGapLineal[0]) << endl;
    
    cout << "Arreglo Lineal Sample: ";
    printArray(arregloSampleLineal, m);
    cout << "Tamaño: " << n*sizeof(arregloSampleLineal[0]) << endl;

    imprimeTiempoBusquedaSample(arregloGapLineal,arregloSampleLineal, n, m, buscar_lineal, b, "Arreglo Lineal");

    cout << endl;

    cout << "Arreglo Normal: ";
    printArray(arregloNormal, n);
    cout << "Tamaño: " << n*sizeof(arregloNormal[0]) << endl;

    //BINARY SEARCH PARA ARREGLO NORMAL
    imprimeTiempoBusqueda(arregloNormal, 0, n-1, buscar_normal, "Arreglo Normal");

    cout << "Arreglo Normal Gap-Coded: ";
    printArray(arregloGapNormal, n);
    cout << "Tamaño: " << n*sizeof(arregloGapLineal[0]) << endl;
    
    cout << "Arreglo Normal Sample: ";
    printArray(arregloSampleNormal, m);
    cout << "Tamaño: " << n*sizeof(arregloSampleLineal[0]) << endl;


    imprimeTiempoBusquedaSample(arregloGapNormal,arregloSampleNormal, n, m, buscar_normal, b, "Arreglo Normal");

    cout<<endl;

    //como se crea el arreglo para los codigos canonicos para gapLineal
    //se crea el vector con sin outliers
    vector<int> out, nOut;
    filtrarArray(arregloGapLineal, nOut, out, n);
    // generamos un array con los elementos que no son outliers
    int* nOutA = &nOut[0];
    //generamos el arreglo con los codigos
    unsigned short int* arrCodes = new unsigned short int[n]; 
    huffman huff(nOutA, nOut.size());
    asignarCodigos(arregloGapLineal, n, huff.huffmanCodes, arrCodes);

    imprimeTiempoBusquedaHuffman(arregloSampleLineal, arregloGapLineal,n,m,buscar_lineal,b, huff,arrCodes);

    delete[] arregloSampleLineal;
    delete[] arregloSampleNormal;
    delete[] arregloGapLineal;
    delete[] arregloGapNormal;
    delete[] arregloLineal;
    delete[] arregloNormal;
    delete[] arrCodes;

    return 0;
}
