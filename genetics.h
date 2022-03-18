#ifndef GENETICS_H
#define GENETICS_H
#include "grafo.h"
#include "listaPontos.h"
#include <stdlib.h>
#include <time.h>


typedef struct listaPopulacao ListaPopulacao;
ListaPopulacao* AlocarPoplist();
int tamanhoListaPopulacao(ListaPopulacao* pop);
ListaPopulacao* duplicarPopulacao(ListaPopulacao* oldPop);
void appendSolucaoNaPopulacao(ListaPonto* solucao, ListaPopulacao* populacao);
ListaPonto* retornaSolucaoNoIndexDaPopulacao(int i, ListaPopulacao* poplist);


double fitness(ListaPonto* lista, Grafo* grafo);
ListaPonto* tornarFactivel(ListaPonto* solucao, Grafo* grafo, ListaPonto* entradaInicial);
ListaPonto* aplicarMutacao(ListaPonto* solucao, double probMutate, ListaPonto* entrada);



ListaPopulacao* criarPopulacaoInicial(ListaPonto* listaEntrada, Grafo* grafo, int tamPop);
ListaPopulacao* SelectApplyCrossoverMutateAndAppendToNewPop(ListaPonto* entrada,  double probMutate, Grafo* grafo, ListaPopulacao* oldPop);

ListaPonto* runGeneticAlgorithm(double timeToExec, ListaPonto* entrada,  double probMutate, Grafo* grafo);


void imprimePopulation(ListaPopulacao* pop);
void destroiPopulacao(ListaPopulacao* popList);

#endif // GENETICS_H