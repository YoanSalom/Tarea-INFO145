#include "search_functions.h"



//Busqueda binaria recursiva
int binarySearch(int* A, int l, int r, int m ,int num){
    if(l > r) return -1;
    else if (A[m] == num) return m;
    else if (A[m] < num) return binarySearch(A,m+1,r,((m+1) + r)/2, num);
    else return binarySearch(A,l,m-1,(l+(m-1))/2, num);
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

//Se implementa el binary search para el sample con el gap de codigos canonicos de huffman
int binarySearchHuffmanGapSample(unsigned short int* codes, int* sample, int n, int m, int elem, int b, huffman h, int* gap) {
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
    int current_value;
    if (codes[0] == 0) current_value = gap[0];
    else current_value = h.decodeHuffman(codes[0], h.huffmanCodes, h.c, h.f);

    for (int i = 1; i <= start; ++i) {
        if (codes[i] == 0) current_value += gap[i];
        else current_value += h.decodeHuffman(codes[i], h.huffmanCodes, h.c, h.f);
    }
    
    for (int i = start + 1; i <= end; ++i) {
        if (codes[i] == 0) current_value += gap[i];
        else current_value += h.decodeHuffman(codes[i], h.huffmanCodes, h.c, h.f);
        if (current_value == elem) {
            return i;
        }
        if (current_value > elem) {
            break;
        }
    }
    return -1; // No se encontró el elemento
}

void imprimeTiempoBusquedaHuffman(int* sample, int* gap, int n, int m, int elem, int b, huffman h, unsigned short int* codes){
    double t0H = clock();
    int posH = binarySearchHuffmanGapSample(codes, sample, n, m, elem, b, h, gap);
    double t1H = clock();
    double tH = (t1H - t0H)/CLOCKS_PER_SEC;

    cout << endl;

    if (posH = -1){
        cout <<"El elemento: "<< elem << " no se encuentra con codificacion de huffman" << endl;
    }
    else{
        cout <<"El elemento: "<< elem << "se encuentra con codificacion de huffman, en la posicion: " << posH << endl;
    }

    cout << fixed << setprecision(6) << "Se demoro " << tH << "segundos en la busqueda" << endl << endl;



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

