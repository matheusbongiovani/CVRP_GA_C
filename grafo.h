#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>
#include "vetorPontos.h"

typedef struct grafo Grafo;
Grafo* criaGrafo();
void inicializaGrafo(Grafo* grafo, int nVeiculos, int nCidades, double capacidadeV, double demandaTotal);
int retornaNCidades(Grafo* grafo);
int retornaNVeiculos(Grafo* grafo);
double retornaCapacidadeMaxVeiculo(Grafo* grafo);
double retornaDemandaTotal(Grafo * grafo);
void insereMatrizDistancias(Grafo* grafo, double** matriz);
void geraMatrizDistancias(Grafo* grafo, VetorPontos* vet);
double retornaDistancia(Grafo* grafo, int cidade1, int cidade2);
void destroiGrafo(Grafo* grafo);

#endif // GRAFO_H
