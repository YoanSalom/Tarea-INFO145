#include "huffman.h"
#include <bitset>



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
    generateHuffmanCodes(root, "");
    cout << "Codigos de Huffman:"<< "\n";
    printHuffmanCodes();
}


huffman::~huffman() {
    // Liberar la memoria del árbol de Huffman
    liberarNodos(root);
}

void huffman::liberarNodos(node* n) {
    if (n == nullptr) return;
    liberarNodos(n->left);
    liberarNodos(n->right);
    delete n;
}

void huffman::generateHuffmanCodes(node* root, const string& code){
    if (!root) return;
    // Si es una hoja, almacenar el código
    if (root->value != -1) {
        huffmanCodes.push_back({root->value, code});
    }
    generateHuffmanCodes(root->left, code + "0");
    generateHuffmanCodes(root->right, code + "1");
}

void huffman::printHuffmanCodes(){
    string aux;
    for (const auto& code : huffmanCodes) {
        cout << "Value: " << code.first << ", Code: " << code.second << endl;
        /*if(size(code.second) < 8){ //Agrega los ceros necesarios para poder transformalos a un valor ASCII
            aux = code.second;
            for (int i = 0; i< 8 - size(code.second); i++){
                aux = "0" + aux;
            }
            bitset<8> temp(aux);//Toma el string y lo guarda como bitset
            cout << "ASCII Code: " << aux << ", ASCII char: " << temp.to_ulong() << endl; //.to_ulong() no hace lo que queria :( 
        }
        else if (size(code.second) == 8){
            bitset<8> temp(code.second);
            cout << "ASCII Code: " << code.second << ", ASCII char: " << temp.to_ulong() << endl;
        }
        else{
            cout << "No se puede representar como ASCII" << endl;
        }*/
    }
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
        cout << "Min-Heap al extraer: ";
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
        leftNode = new node(get<0>(u), get<1>(u));
    }

    if (get<0>(v) == -1) {
        rightNode = get<2>(v);
    } else {
        rightNode = new node(get<0>(v), get<1>(v));
    }
    

    // Crear un nuevo nodo que será el padre de u y v
    double combinedProbability = get<1>(u) + get<1>(v);
    node* parentNode = new node(-1, combinedProbability, leftNode, rightNode); // -1 indica que no es una hoja
    
    // Insertar el nuevo nodo en el vector Prob
    Prob.push_back(make_tuple(-1, combinedProbability, parentNode));
    len++;
    swap(Prob[len-1], Prob[Prob.size()-1]);
    // Actualizar la raíz del árbol de Huffman
    root = parentNode;

    cout <<  "valor:" <<root -> value << " probabilidad:" << root -> p << "\n";
    // Reordenar el minHeap
    for (int i = len / 2 - 1; i >= 0; i--) {
        minHeapify(Prob, len, i);
    }

}
void huffman::print(node* root) {
    if (root == nullptr)
        return;
    // Imprimir el valor del nodo actual
    cout <<  "valor:" <<root -> value << " probabilidad:" << root -> p << "\n";

    // Recorrer el subárbol izquierdo
    print(root->left);

    // Recorrer el subárbol derecho
    print(root->right);
}