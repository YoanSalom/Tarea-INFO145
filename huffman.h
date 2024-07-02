#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>
using namespace std;

struct node
{
    short int value;
    double p;
    node* left;
    node* right;

    node(short int val, double prob, node* l = nullptr, node* r = nullptr)
        : value(val), p(prob), left(l), right(r) {}
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

    private:
        vector<tuple<int, double, node*>> Prob;
        vector<pair<int, unsigned short int>> huffmanCodes;
        void minHeapify(vector<tuple<int, double, node*>>& heap, int l, int i);
        void extractMinHeap(vector<tuple<int, double, node*>>& heap, int& l);
        void anadirNodo(tuple<int, double, node*> u, tuple<int, double, node*> v, int& len);
        void liberarNodos(node* n);
        void arbolCan();
        void extractCodeAndLength(unsigned short int storedCode, unsigned short int& length, unsigned short int& code);
        int getLength(unsigned short int code);
        void insertionSort(vector<pair<int, unsigned short int>>& huffmanCodes);
        };

