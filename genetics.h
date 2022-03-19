#ifndef GENETICS_H
#define GENETICS_H
#include "grafo.h"
#include "vetorPontos.h"
#include <stdlib.h>
#include <time.h>



int* shuffleVetInt(int* solucao, Grafo* grafo);
int* removeZerosNaSolu(int* solucao, Grafo* grafo);
int* removeZerosDoLado(int* solucao);

// double fitness(int* solucao, Grafo* grafo);

int* criarSolucaoInt(VetorPontos* vet, Grafo* grafo);
int** criarPopulacaoInicial(VetorPontos* vet, Grafo* grafo);





int* distribuirZerosNaSolu(int* solucao, Grafo* grafo, VetorPontos* entrada);



void imprimirSolInt(int* solucao);
void imprimirElemsPopulacao(int** populacao, Grafo* grafo);

void destroiPopulacao(int** populacao, Grafo* grafo);
#endif // GENETICS_H