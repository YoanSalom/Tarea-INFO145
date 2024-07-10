#ifndef ARRAY_INI_H
#define ARRAY_INI_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>
#include "huffman.h"

using namespace std;

unsigned short int codeSearchL(const vector<tuple<int, unsigned short int>>& huffmanCodes, int value);

void asignarCodigos(int* A, int n, vector<tuple<int, unsigned short int>> huffmanCodes, unsigned short int* Arr);

void filtrarArray(int* Arr, vector<int>& nOut, vector<int>& out, int n);

int* generarArregloGap(int n, int* A);

int* generarArregloSample(int n, int* A, int m, int b);

void printArray(int* A, int n, int limit = 10);

int* arregloLinealGen(int n, int e);

int* arregloNormalGen(int n, int media, int ds);


#endif