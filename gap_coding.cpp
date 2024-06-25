#include <iostream>
#include <cstdlib>
#include <time.h>
#include <omp.h>

using namespace std;

int binarysearch(int arreglo[], int l, int r, int num){
    int m;
    while (l <= r){
        m = l+(r-l)/2;

        if(arreglo[m] == num){
            return m;
        }
        if(arreglo[m] < num){
            l = m + 1;
        }
        else{
            r = m - 1;
        }
    }

    return -1;
}

int main(){
    
    int n;
    int search;
    int pos;
    double t1, t2 , tfin;
    
    //genera arreglos

    cout << "Ingrese el numero de elementos: ";
    cin >> n;

    srand(time(NULL));

    int num_array[n] = {};
    int normal_array[n] = {};

    for (int i = 0; i <= n-1; i++){
        if (i == 0){
            num_array[0] = rand() % 10 + 1;
        }
        else{
            num_array[i] = num_array[i-1] + rand() % 10 + 1;
        }
        cout << num_array[i];
        cout << " ";
    }

    cout << "\n\nIngrese numero a buscar: ";
    cin >> search;

    
    //Busqueda binaria para arreglo lineal
    t1 = omp_get_wtime();
    pos = binarysearch(num_array,0,n-1,search);
    t2 = omp_get_wtime();

    if (pos == -1){
        cout << search  << " no se encuentra en el arreglo lineal" << endl;
    }
    else{
        cout << search << " esta en el arreglo lineal, en la posicion: " << pos << endl;
    }

    tfin = t2 - t1;

    cout << "Se demoro: " << tfin<< " s" << endl;

    return 0;
}