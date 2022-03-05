#ifndef VNS_LEITURA_H
#define VNS_LEITURA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "listaPontos.h"
#include "grafo.h"

FILE* inicializaArquivo(FILE* file, char * nomeArq);
void leArquivo(FILE* file, char* buffer, size_t bufsize, ListaPonto * lista, Grafo * grafo);
double converteNumero (char * token);
void verificaTotalDeDemanda(double totalDeDemandas, int quantVeiculos, double capacidadeVeiculos);
#endif //VNS_LEITURA_H
