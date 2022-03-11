#ifndef GENETICS_H
#define GENETICS_H
#include "grafo.h"
#include "listaPontos.h"
#include <stdlib.h>
#include <time.h>


double fitness(ListaPonto* lista, Grafo* grafo);
ListaPonto* tornarFactivel(ListaPonto* solucao, Grafo* grafo);









void vns(int* vetorRotas, int tamVetor, Grafo * grafo, ListaPonto * listaPontos);
int * buscaLocal(int* rotaVizinha, int * vetorRotas, int  tamVetor, Grafo * grafo, double custo);
int calculaTamanhoVetorRotas(Grafo * grafo);
int * criaVetorDeIntDe1ateNcidades(int tamVetor);
void geraSolucaoInicialRandom(Grafo * grafo, int * vetorRotaAleatorio, ListaPonto * listaPontos, int numAleatorio);
int * geraXisLinha(int * xLinha, int * vetorRotas, int tamVetor, double custo, ListaPonto * listaPontos, Grafo * grafo);
void imprimeResultado(int * vetorRotas, int k, double custo);

#endif // GENETICS_H