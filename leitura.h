#ifndef LEITURA_H
#define LEITURA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "vetorPontos.h"
#include "grafo.h"

char* defineBuffer (FILE* file, size_t bufsize);
FILE* inicializaArquivo(FILE* file, char* nomeArq);
void leArquivo(FILE* file, char* buffer, size_t bufsize, VetorPontos* vet, Grafo* grafo);

#endif // LEITURA_H