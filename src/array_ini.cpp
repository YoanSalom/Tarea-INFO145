#include "array_ini.h"

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
void printArray(int* A, int n, int limit){
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
