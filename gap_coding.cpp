#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    
    int n;

    cout << "Ingrese el numero de elementos: ";
    cin >> n;

    srand(time(NULL));

    int num_array[n] = {};

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

    cout << endl;

    
    return 0;
}