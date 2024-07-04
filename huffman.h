#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>
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
        void huffmanDecode();
        void generateCode(int* Arr);
        node* root; // Puntero al nodo raíz
        node* rootC;
        void print(node* n);
        void printHuffmanCodes();
        void generateHuffmanCodes(node* root, unsigned short int code = 0, unsigned short int length = 0);
        int searchT(node* root, unsigned short int code, int bit);
        vector<tuple<int, unsigned short int>> huffmanCodes;

    private:
        vector<tuple<int, double, node*>> Prob;
        void minHeapify(vector<tuple<int, double, node*>>& heap, int l, int i);
        void extractMinHeap(vector<tuple<int, double, node*>>& heap, int& l);
        void anadirNodo(tuple<int, double, node*> u, tuple<int, double, node*> v, int& len);
        void liberarNodos(node* n);
        void arbolCan(int v, unsigned short int l, int bit, node* rootT, unsigned short int code);
        void extractCodeAndLength(unsigned short int storedCode, unsigned short int& length, unsigned short int& code);
        int getLength(unsigned short int code);
        void insertionSort(vector<tuple<int, unsigned short int>>& huffmanCodes);
        void generateCanonicalHuffman(vector<tuple<int, unsigned short int>>& huffmanCodes);
        };

