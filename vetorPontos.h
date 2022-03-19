#ifndef VETORPONTOS_H
#define VETORPONTOS_H
#include <stdio.h>
#include "ponto.h"
#include <time.h>


typedef struct vetorPontos VetorPontos;
VetorPontos* inicializaVetorPonto();
int vetPtsTamInicial(VetorPontos* vet);
void atualizaTamVet(int n_genes, VetorPontos* vet);
void appendPonto(Ponto* p, VetorPontos* vet);

Ponto* procuraPontoPeloId(int id, VetorPontos* vet);
void distanciaPontos(VetorPontos* vet, double** matriz, int numCidades);

void imprimeVetPtsInicial(VetorPontos* vet);





void destroiVetPtsEntrada(VetorPontos* vet);





#endif // VETORPONTOS_H