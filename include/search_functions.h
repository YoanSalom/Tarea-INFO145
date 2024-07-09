#ifndef SEARCH_FUNCTIONS_H
#define SEARCH_FUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>
#include "huffman.h"
#include <iomanip>

using namespace std;


void imprimeTiempoBusqueda(int *A, int l, int r, int elem, string type);

int binarySearchGapWithSample(int* gap, int* sample, int n, int m, int elem, int b);

int binarySearchHuffmanGapSample(unsigned short int* codes, int* sample, int n, int m, int elem, int b, huffman h, int* gap);

void imprimeTiempoBusquedaHuffman(int* sample, int* gap, int n, int m, int elem, int b, huffman h, unsigned short int* codes);

void imprimeTiempoBusquedaSample(int* gap, int* sample, int n, int m, int elem, int b, string type);


#endif