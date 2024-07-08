#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>
#include <cmath>
using namespace std;

struct node
{
    short int value;
    node* left;
    node* right;

    node(short int val, node* l = nullptr, node* r = nullptr)
        : value(val), left(l), right(r) {}
};

class HuffmanCodeLengthException : public std::exception {
public:
    const char* what() const noexcept override {
        return "La longitud del código supera los 12 bits";
    }
};

class huffman{
    public:
        huffman(int* Arr, int n);
        ~huffman();
        void generateCode();

        node* root; // Puntero a la raiz del arbol
        node* rootC; // Puntero a la raiz del arbol canonico

        node* rootOut; // Puntero a la raiz del arbol
        node* rootCOut; // Puntero a la raiz del arbol canonico

        void print(node* n); //Funcion imprimir un arbol
        void printHuffmanCodes(); //Funcion para imprimir los codigos de huffman y sus valores que representan
        void generateHuffmanCodes(node* root, unsigned short int code = 0,
        unsigned short int length = 0); //Funcion para generar los codigos a partir de un arbol
        int decodeHuffman(unsigned short int code, vector<tuple<int, unsigned short int>> codes,
        vector<short int> c, vector<short int> f); //Funcion para generar los codigos a partir de un arbol

        //vectores auxiliares
        vector<tuple<int, unsigned short int>> huffmanCodes;
        vector<short int> c;
        vector<short int> f;

        vector<tuple<int, double, node*>> Prob; //vector que contendra las probabilidades de cada elemento valido

    private:
        //las funciones minheap y extractMinheap son funciones basicas para tratar los heaps
        void minHeapify(vector<tuple<int, double, node*>>& heap, int l, int i); 
        void extractMinHeap(vector<tuple<int, double, node*>>& heap, int& l);
        void anadirNodo(tuple<int, double, node*> u, tuple<int, double, node*> v, int& len); //funcion para añadir un nodo a un arbol
        void liberarNodos(node* n); //funcion auxiliar para el destructor
        void arbolCan(int v, unsigned short int l, int bit, node* rootT, unsigned short int code); //funcion para crear el arbol canonico de huffman
        void extractCodeAndLength(unsigned short int storedCode, 
        unsigned short int& length, unsigned short int& code); //funcion para extraer la longitud del codigo junto con este
        int getLength(unsigned short int code);  //funcion para extraer solo la longitud del codigo
        void insertionSort(vector<tuple<int, unsigned short int>>& huffmanCodes); //funcion para ordenar el los vectores con 
        //los codigos usando insertion sort
        void generateCanonicalHuffman(vector<tuple<int, unsigned short int>>& huffmanCodes); //funcion que inicia la creacion del arbol canonico
        void fillArrays(vector<short int> &c, vector<short int> &f, vector<tuple<int, unsigned short int>> codes);//rellena los arrays f y c para la decodificacion
        void findOutliers(const vector<int>& frecuencias, vector<pair<int, int>>& outliers, vector<pair<int, int>>& nonOutliers, int & t_out, int & t_nOut);
        };

