#include <iostream>
#include <cstdlib>
#include "huffman.h"

using namespace std;

//ya que el vector de codigos esta desordenado con respecto al valor entero no queda otra que hacer una busqueda secuencial
unsigned short int codeSearchL(const vector<tuple<int, unsigned short int>>& huffmanCodes, int value) {
    for (int i = 0; i < huffmanCodes.size(); i++) {
        if (get<0>(huffmanCodes[i]) == value) {
            return get<1>(huffmanCodes[i]);
        }
    }
    return 0;
}
//Funcion para asignar los codigos al arreglo, si no encuentra el valor, los casos outliers se marcaran como 0 y se obtendrea el valor desde el arreglogap.
void asignarCodigos(int* A, int n, vector<tuple<int, unsigned short int>> huffmanCodes, unsigned short int* Arr) {
    for (int i = 0; i < n; i++) {
        unsigned short int num = codeSearchL(huffmanCodes, A[i]); // Corregido: usar A[i] en lugar de Arr[i]
        if (num == 0) {
            Arr[i] = 0;
        } else {
            Arr[i] = num;
        }
    }
}

void filtrarArray(int* Arr, vector<int>& nOut, vector<int>& out,int n){
    // encontrar el máximo valor en el arreglo para determinar el tamaño del arreglo auxiliar
    int maximo = 0;
    for (int i = 0; i < n; ++i) {
        if (Arr[i] > maximo) {
            maximo = Arr[i];
        }
    }
    // crear un arreglo auxiliar para contar frecuencias
    int tamanoAuxiliar = maximo + 1;
    vector<int> frecuencias(tamanoAuxiliar, 0);
    // contar la frecuencia de cada número en el arreglo
    for (int i = 0; i < n; ++i) {
        frecuencias[Arr[i]]++;
    }
    // Calcular la media y desviación estándar de las frecuencias
    double suma = 0.0;
    int count = 0;
    for (int i = 0; i < tamanoAuxiliar; ++i) {
        if (frecuencias[i] > 0) {
            suma += frecuencias[i];
            count++;
        }
    }
    double media = suma / count;
    double sumaDesviaciones = 0.0;
    
    for (int i = 0; i < tamanoAuxiliar; ++i) {
        if (frecuencias[i] > 0) {
            sumaDesviaciones += pow(frecuencias[i] - media, 2);
        }
    }
    double desviacionEstandar = sqrt(sumaDesviaciones / count);
    
    // Filtrar los elementos que son outliers y los que no
    for (int i = 0; i < n; ++i) {
        if (frecuencias[Arr[i]] > 0){
            if (frecuencias[Arr[i]] > media + 2 * desviacionEstandar || frecuencias[Arr[i]] < media - 2 * desviacionEstandar) {
                out.push_back(Arr[i]);  // Elemento outlier
            } else {
                nOut.push_back(Arr[i]);  // Elemento no outlier
            }
        }
    }
}

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
    vector<int> out, nOut;
    
    cout << "Arreglo Lineal: ";
    printArray(arregloLineal, n);
    
    cout << "Arreglo Gap-Coded: ";
    printArray(arregloGap, n);
    
    cout << "Arreglo Sample: ";
    printArray(arregloSample, m);

    filtrarArray(arregloGap, nOut, out, n);

    int* nOutA = &nOut[0];
    unsigned short int* arrCodes = new unsigned short int[n]; 
    huffman huff(nOutA, nOut.size());
    asignarCodigos(arregloGap, n, huff.huffmanCodes, arrCodes);
    for(int i = 0; i < n; i++){
        if(arrCodes[i] == 0){
            cout << "outlier:"<< arregloGap[i] << "\n";
        }
        else{
        cout << "codigo: " << i << ": " << bitset<16>(arrCodes[i]) << " decodificado: " << huff.decodeHuffman(arrCodes[i], huff.huffmanCodes, huff.c, huff.f) << " valor en el gap: " << arregloGap[i] << "\n";
        }
    }
  
    huff.~huffman();
    
    delete[] arregloSample;
    delete[] arregloGap;
    delete[] arregloLineal;
    return 0;
}
