#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leitura.h"
#include "ponto.h"
#include "vetorPontos.h"
#include "grafo.h"
#include "genetics.h"

int main(int argc, char** argv) {
    if (argc != 2){
        printf("Sintaxe: ./main A-n32-k5.vrp\n");
        exit(1);
    }
    time_t t;
    srand((unsigned)time(&t));
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    FILE * file = NULL;
    file = inicializaArquivo(file, argv[1]);

    // Declaração do buffer
    size_t bufsize = 1;
    char* buffer = defineBuffer(file, bufsize);

    // Inicializa lista que guarda todos os pontos
    VetorPontos* entrada = inicializaVetorPonto();

    // Inicializa grafo que conterá informações lidas 
    Grafo* grafo = criaGrafo();

    // Lê o arquivo e preenche a lista de pontos com todos os pontos(cidades), suas coordenadas e demandas 
    leArquivo(file, buffer, bufsize, entrada, grafo);

    // Geração da matriz que guarda distancia entre cidades 
    geraMatrizDistancias(grafo, entrada);
//----------------------------------------------------------------------



    // EXECUTAR ALGORITMO: void runGeneticAlgorithm(timeToExec,probMutate, entrada, grafo)
    runGeneticAlgorithm(10, 0.05, entrada, grafo);



//----------------------------------------------------------------------



    destroiGrafo(grafo);
    destroiVetPtsEntrada(entrada);
    return 0;
}
