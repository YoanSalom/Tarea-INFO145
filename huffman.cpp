#include "huffman.h"


huffman::huffman(int* Arr, int n) : root(nullptr), huffmanCodes(){
    // Encontrar el máximo valor en el arreglo para determinar el tamaño del arreglo auxiliar
    int maximo = 0;
    for (int i = 0; i < n; ++i) {
        if (Arr[i] > maximo) {
            maximo = Arr[i];
        }
    }
    // Crear un arreglo auxiliar para contar frecuencias
    int tamanoAuxiliar = maximo + 1;
    vector<int> frecuencias(tamanoAuxiliar, 0);
    // Contar la frecuencia de cada número en el arreglo
    for (int i = 0; i < n; ++i) {
        frecuencias[Arr[i]]++;
    }
    // Crear un vector de tuplas a partir del arreglo de frecuencias
    for (int num = 0; num < tamanoAuxiliar; ++num) {
        if (frecuencias[num] > 0) {
            double probabilidad = static_cast<double>(frecuencias[num]) / n;
            Prob.push_back(make_tuple(num, probabilidad, nullptr));
        }
    }
    generateCode(Arr);
    unsigned short int code = 0;
    generateHuffmanCodes(root, 0, 0);
    cout << "Codigos de Huffman:"<< "\n"; 
    printHuffmanCodes();
    insertionSort(huffmanCodes);
    cout << "Codigos de Huffman despues de ordenarse:"<< "\n";
    printHuffmanCodes();
    generateCanonicalHuffman(huffmanCodes);
    huffmanCodes.clear();
    cout << "Codigos de Huffman:"<< "\n";
    generateHuffmanCodes(rootC, 0, 0);

}


huffman::~huffman() {
    // Liberar la memoria del árbol de Huffman
    liberarNodos(root);
    liberarNodos(rootC);
}

void huffman::liberarNodos(node* n) {
    if (n == nullptr) return;
    liberarNodos(n->left);
    liberarNodos(n->right);
    delete n;
}

void huffman::generateHuffmanCodes(node* root, unsigned short int code,unsigned short int length){
        if (!root) return;
        // Si es una hoja, almacenar el código
        if (root->value != -1) {
            // Verificar que la longitud no supere 12 bits
            if (length <= 12) {
                // Almacenar la longitud en los 4 bits más significativos
                unsigned short int storedCode = (length << 12) | code;
                huffmanCodes.push_back({root->value, storedCode});
                cout << "Almacenando valor: " << root->value << ", codigo: " << bitset<16>(storedCode) << "\n";
            } else {
                cerr << "Error: la longitud del código supera los 12 bits para el valor " << root->value << "\n";
                throw HuffmanCodeLengthException(); // Lanzar excepción
            }
    }
        // Desplazar el código y aumentar la longitud
        generateHuffmanCodes(root->left, code << 1, length + 1);
        generateHuffmanCodes(root->right, (code << 1) | 1, length + 1);
    }

void huffman::printHuffmanCodes(){
        unsigned short int length, numero;
        for (const auto& code : huffmanCodes){
        int value = get<0>(code);
        unsigned short int binCode = get<1>(code);
        extractCodeAndLength(binCode, length, numero);
        // Imprimir el valor y el código en formato binario
        cout << "Value: " << value << ", Code: " << numero <<" "<< "longitud: " << length <<" - ";
    }
    cout << "\n";
}

void huffman::huffmanDecode() {
    // Implementar la decodificación de Huffman
}

void huffman::generateCode(int* Arr) {
    int l = Prob.size();
    
    // Crear el minHeap asociado a las hojas en función de las probabilidades
    for (int i = l / 2 - 1; i >= 0; i--) {
        minHeapify(Prob, l, i);
    }
    // Imprimir el heap para verificar
    cout << "Min-Heap creado: ";
    for (const auto& elem : Prob) {
        cout << get<0>(elem) << "(" << get<1>(elem) << ") ";
    }
    cout << endl;

    // Extraer los elementos del Min-Heap
    while (l >= 2) {
        // Extraer el primer mínimo
        auto min1 = Prob[0];
        extractMinHeap(Prob, l);
        
        // Extraer el segundo mínimo
        auto min2 = Prob[0];
        extractMinHeap(Prob, l);
        cout << "Min-Heap al extraer los dos primeros elementos: ";
        // Añadir un nodo utilizando los dos elementos extraídos
        for (const auto& elem : Prob) {
            cout << get<0>(elem) << "(" << get<1>(elem) << ")";
        }
        cout << endl << l<< endl;

        anadirNodo(min1, min2, l);
        cout << "Min-Heap nuevo: ";
        for (const auto& elem : Prob) {
            cout << get<0>(elem) << "(" << get<1>(elem) << ") ";
        }
        cout << endl;
    }
    root = get<2>(Prob[0]);
}

void huffman::minHeapify(vector<tuple<int, double, node*>>& heap, int l, int i) {
    int smallest = i; // Inicializar el nodo actual como el más pequeño
    int left = 2 * i + 1; // Índice del hijo izquierdo
    int right = 2 * i + 2; // Índice del hijo derecho

    // Si el hijo izquierdo es más pequeño en probabilidad que el nodo actual, actualizar el índice del más pequeño
    if (left < l && get<1>(heap[left]) < get<1>(heap[smallest])) {
        smallest = left;
    }

    // Si el hijo derecho es más pequeño en probabilidad que el nodo actual o el hijo izquierdo, actualizar el índice del más pequeño
    if (right < l && get<1>(heap[right]) < get<1>(heap[smallest])) {
        smallest = right;
    }

    // Si el nodo más pequeño no es el nodo actual, intercambiarlos y continuar heapificando hacia abajo
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, l, smallest);
    }
}

void huffman::extractMinHeap(vector<tuple<int, double, node*>>& heap, int& l) {
    if (l <= 0) {
        return; // o alguna otra señal de que el heap está vacío
    }
    if (l == 1) {
        l--;
        return;
    }
    // Mover el último elemento a la raíz y reducir el tamaño del heap
    swap(heap[0], heap[l-1]);
    l--;
    // Llamar a minHeapify en la raíz
    minHeapify(heap, l, 0);
}

void huffman::anadirNodo(tuple<int, double, node*> u, tuple<int, double, node*> v,int& len) {
    node* leftNode;
    node* rightNode;
    // Crear nuevos nodos para u y v si no son nodos internos (-1)
    if (get<0>(u) == -1) {
        leftNode = get<2>(u);
    } else {
        leftNode = new node(get<0>(u));
    }
    if (get<0>(v) == -1) {
        rightNode = get<2>(v);
    } else {
        rightNode = new node(get<0>(v));
    }
    // Crear un nuevo nodo que será el padre de u y v
    double combinedProbability = get<1>(u) + get<1>(v);
    node* parentNode = new node(-1, leftNode, rightNode); // -1 indica que no es una hoja
    // Insertar el nuevo nodo en el vector Prob
    Prob.push_back(make_tuple(-1, combinedProbability, parentNode));
    len++;
    swap(Prob[len-1], Prob[Prob.size()-1]);
    // Actualizar la raíz del árbol de Huffman
    root = parentNode;
    cout <<  "valor:" <<root -> value << "\n";
    // Reordenar el minHeap
    for (int i = len / 2 - 1; i >= 0; i--) {
        minHeapify(Prob, len, i);
    }
}

void huffman::print(node* root) {
    if (root == nullptr)
        return;
    // Imprimir el valor del nodo actual
    cout <<  "valor:" <<root -> value << "\n";

    // Recorrer el subárbol izquierdo
    print(root->left);

    // Recorrer el subárbol derecho
    print(root->right);
}

void huffman::extractCodeAndLength(unsigned short int storedCode, unsigned short int& length, unsigned short int& code) {
    length = (storedCode >> 12) & 0xF; // Extraer los 4 bits más significativos
    code = storedCode & 0xFFF;         // Extraer los 12 bits menos significativos
}

int huffman::getLength(unsigned short int code){
    return code >> 12; //Retorna solo la longitud del codigo
}

void huffman::insertionSort(vector<tuple<int, unsigned short int>>& huffmanCodes) {
    int n = huffmanCodes.size();
    for (int i = 1; i < n; ++i) {
        auto key = huffmanCodes[i];
        int keyLength = getLength(get<1>(key));
        int j = i - 1;

        // Mover los elementos de huffmanCodes[0..i-1], que son mayores que el
        // largo del código clave, una posición adelante de su posición actual
        while (j >= 0 && getLength(get<1>(huffmanCodes[j])) > keyLength) {
            huffmanCodes[j + 1] = huffmanCodes[j];
            --j;
        }
        huffmanCodes[j + 1] = key;
    }
}

void huffman::arbolCan(int v, unsigned short int l, int bit, node* rootT, unsigned short int code){
    //añade los nodos para el codigo, si los bits faltantes llegan a 0 se crea el ultimo nodo
   if (0 == bit) {
        unsigned short int mask = 1 << bit; 
        bool bitValue = (code & mask) != 0;
        node* q = new node(v);
        if (bitValue) {
            rootT->right = q;
        } else {
            rootT->left = q;
        }
    } 
    //en caso de que falten nodos se crean los nodos faltantes(para el primer codigo de 0 de largo l), recorre el arbol hasta encontrar donde inserta el nodo
    else {
        unsigned short int mask = 1 << bit; 
        bool bitValue = (code & mask) != 0;
        if (bitValue) {
            if (rootT->right == nullptr) {
                rootT->right = new node(-1);
            }
            arbolCan(v, l, bit - 1, rootT->right, code);
        } else {
            if (rootT->left == nullptr) {
                rootT->left = new node(-1);
            }
            arbolCan(v, l, bit - 1, rootT->left, code);
        }
    }
}

void huffman::generateCanonicalHuffman(vector<tuple<int, unsigned short int>>& huffmanCodes){
    //funcion para crear los codigos canonicos e insertarlos en el arbol.
    unsigned short int l, l_c, code_c;
    l = getLength(get<1>(huffmanCodes[0]));
    rootC = new node(-1);
    code_c = 0;
    arbolCan(get<0>(huffmanCodes[0]), l, l-1, rootC, code_c);
    for(int i = 1; i < huffmanCodes.size(); i++){
        l_c = getLength(get<1>(huffmanCodes[i]));
        if(l == l_c){
            if(code_c + 1 > 4095){
                cerr << "Error: la longitud del código supera los 12 bits para el valor " << root->value << "\n";
                throw HuffmanCodeLengthException(); // Lanzar excepción
            }
            code_c = code_c + 1;
            arbolCan(get<0>(huffmanCodes[i]), l, l-1, rootC, code_c);
        }
        else if (l + 1 == l_c)
        {
            code_c = 2*(code_c + 1);
            l++;
            if(code_c> 4095){
                cerr << "Error: la longitud del código supera los 12 bits para el valor " << root->value << "\n";
                throw HuffmanCodeLengthException(); // Lanzar excepción
            }
            arbolCan(get<0>(huffmanCodes[i]), l, l-1, rootC, code_c);
            }
        else if (l + 1 < l_c)
        {
            while (l + 1< l_c){
                if (l > 12){
                    cerr << "Error: la longitud del código supera los 12 bits para el valor " << get<0>(huffmanCodes[i]) << "\n";
                    throw HuffmanCodeLengthException(); // Lanzar excepción
                }
                l++;
                code_c = code_c << 1;
                arbolCan(-1, l, l-1, rootC, code_c);
        }
        }
    }
}
