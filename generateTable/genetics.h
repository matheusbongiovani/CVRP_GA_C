#ifndef GENETICS_H
#define GENETICS_H
#include "grafo.h"
#include "vetorPontos.h"
#include <stdlib.h>
#include <time.h>



int* shuffleVetInt(int* solucao, Grafo* grafo);
int* removeZerosNaSolu(int* solucao, Grafo* grafo);
int* removeZerosDoLado(int* solucao);
int* distribuirZerosNaSoluInicial(int* solucao, Grafo* grafo, VetorPontos* entrada);
void distribuirZerosRecorrente(int* solucao, Grafo* grafo, VetorPontos* entrada);
int* removeIdNaPos(int pos, int* solucao);
void insereZeroAntesPos(int pos, int* solucao, Grafo* grafo);
int idEstaContidoNaSolu(int id, int* solucao);

int tamanhoSolucao(int* solucao);
int* reverseEntreCuts(int* solucao, int cut1, int cut2);
int* mutacao(int* solucao, double probMutate);
int** crossover(int* p1, int* p2, Grafo* grafo, VetorPontos* entrada);




double fitness(int* solucao, Grafo* grafo, VetorPontos* entrada);
int* tornarFactivel(int* solucao, Grafo* grafo, VetorPontos* entrada);


int* criarSolucaoInt(VetorPontos* entrada, Grafo* grafo);
int** criarPopulacaoInicial(VetorPontos* entrada, Grafo* grafo);
int** criarNOVApopulacao(int** oldPop, double prob_mutate, Grafo* grafo, VetorPontos* entrada);
void runGeneticAlgorithm(double timeToExec, double probMutate, VetorPontos* entrada, Grafo* grafo);





void imprimeDemandaRotas(int* solucao, VetorPontos* entrada, Grafo* grafo);
void imprimirSolInt(int* solucao);
void imprimirElemsPopulacao(int** populacao, Grafo* grafo);

void destroiPopulacao(int** populacao, Grafo* grafo);
#endif // GENETICS_H