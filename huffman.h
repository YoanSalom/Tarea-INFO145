#include <iostream>
#include <vector>
#include <tuple>

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
        void print(node* n);
        void printHuffmanCodes();
        void generateHuffmanCodes(node* root, const string& code);

    private:
        vector<tuple<int, double, node*>> Prob;
         vector<pair<int, string>> huffmanCodes;
        void minHeapify(vector<tuple<int, double, node*>>& heap, int l, int i);
        void extractMinHeap(vector<tuple<int, double, node*>>& heap, int& l);
        void anadirNodo(tuple<int, double, node*> u, tuple<int, double, node*> v, int& len);
        void liberarNodos(node* n);
    };

