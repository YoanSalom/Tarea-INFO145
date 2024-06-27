#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <algorithm>
#include <array>

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
    
    int n; //Elementos en el array
    int searchLineal, searchNormal; //Elemento que se esta buscando
    int pos; //Posicion en la que se encontro el elemento
    int media = 50;
    int des_std = 10; //Desviacion estandar

    double t0, t1, t; //Variables para medir tiempo de ejecucion
    

    cout << "Ingrese el numero de elementos: ";
    cin >> n;

    //Semillas
    srand(time(NULL));
    random_device rd{};
    mt19937 gen{rd()};


    int num_array[n] = {}; //Arreglo lineal
    int normal_array[n] = {}; //Arreglo normal

    //Agrega n elementos al arreglo lineal
    for (int i = 0; i <= n-1; i++){
        if (i == 0){
            num_array[0] = rand() % 10 + 1;
        }
        else{
            num_array[i] = num_array[i-1] + rand() % 10 + 1;
        }
    }
  
    //Busqueda binaria para arreglo lineal

    cout << "\n\nIngrese numero a buscar en el arreglo lineal: ";
    cin >> searchLineal;

    t0 = clock();
    pos = binarysearch(num_array,0,n-1,searchLineal);
    t1 = clock();

    t = (t1-t0)/CLOCKS_PER_SEC;

    if (pos == -1){
        cout << searchLineal  << " no se encuentra en el arreglo lineal" << endl;
    }
    else{
        cout << searchLineal << " esta en el arreglo lineal, en la posicion: " << pos << endl;
    }

    cout << "Se demoro " << t << " s en hacer la busqueda" << endl;


    //Agrega n elementos al arreglo normal
    normal_distribution<> distribucion(media, des_std);
    for (int i = 0; i < n;i++){
        normal_array[i] = round(distribucion(gen));
    }
    sort(normal_array,normal_array + n);

    //Busqueda binaria para el arreglo normal
    cout << "\n\nIngrese numero a buscar en el arreglo normal: ";
    cin >> searchNormal;

    t0 = clock();
    pos = binarysearch(num_array,0,n-1,searchNormal);
    t1 = clock();

    t = (t1 - t0)/CLOCKS_PER_SEC;

    if (pos == -1){
        cout << searchNormal  << " no se encuentra en el arreglo normal" << endl;
    }
    else{
        cout << searchNormal << " esta en el arreglo normal, en la posicion: " << pos << endl;
    }

    cout << "Se demoro " << t << " s en hacer la busqueda" << endl;

    return 0;
}
