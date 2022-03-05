#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "grafo.h"
#include "listaPontos.h"
#include "ponto.h"
#include <time.h>

char * defineBuffer (FILE * file, size_t bufsize){
    /* Lê a primeira linha do arquivo e guarda no buffer */

    char * buffer = NULL;
    buffer = (char *)malloc(bufsize * sizeof(char));
    getline(&buffer, &bufsize, file);

    return buffer;
}



int main(int argc, char ** argv) {
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

    FILE * file = NULL;
    file = inicializaArquivo(file, argv[1]);

    /* Declaração do buffer */
    size_t bufsize = 1;
    char * buffer = defineBuffer(file, bufsize);

    /* Inicializa lista que guarda todos os pontos */
    ListaPonto * lista = inicializaListaPonto();

    /* Inicializa grafo que conterá informações lidas */
    Grafo * grafo = criaGrafo();

    /* Lê o arquivo e preenche a lista de pontos com todos os pontos(cidades), suas coordenadas e demandas */
    leArquivo(file, buffer, bufsize, lista, grafo);

    /* Geração da matriz que guarda distancia entre cidades */
    geraMatrizDistancias(grafo, lista);

    return 0;
}


