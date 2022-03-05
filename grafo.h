#ifndef VNS_GRAFO_H
#define VNS_GRAFO_H

#include <stdlib.h>
#include "listaPontos.h"

typedef struct grafo Grafo;
Grafo * criaGrafo();
void inicializaGrafo(Grafo * grafo, int nVeiculos, int nCidades, int capacidadeV, double demandaTotal);
int retornaNCidades(Grafo * grafo);
int retornaNVeiculos(Grafo * grafo);
double retornaCapacidade(Grafo * grafo);
void insereMatrizDistancias(Grafo * grafo, double ** matriz);
void geraMatrizDistancias(Grafo * grafo, ListaPonto * lista);
double retornaDistancia(Grafo * grafo, int cidade1, int cidade2);
void destroiGrafo(Grafo * grafo);

#endif //VNS_GRAFO_H
