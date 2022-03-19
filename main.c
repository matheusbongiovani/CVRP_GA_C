#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leitura.h"
#include "ponto.h"
#include "vetorPontos.h"
#include "grafo.h"
#include "genetics.h"

char* defineBuffer (FILE* file, size_t bufsize);

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
    VetorPontos* vetorPontosEntrada = inicializaVetorPonto();

    // Inicializa grafo que conterá informações lidas 
    Grafo* grafo = criaGrafo();

    // Lê o arquivo e preenche a lista de pontos com todos os pontos(cidades), suas coordenadas e demandas 
    leArquivo(file, buffer, bufsize, vetorPontosEntrada, grafo);

    // Geração da matriz que guarda distancia entre cidades 
    geraMatrizDistancias(grafo, vetorPontosEntrada);
//----------------------------------------------------------------------

    // imprimeVetPtsInicial(vetorPontosEntrada);


    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*2); // TAM DA POPULAÇÃO



    int** populacaoInicial = criarPopulacaoInicial(vetorPontosEntrada, grafo);


    removeZerosNaSolu(populacaoInicial[0], grafo);

    imprimirElemsPopulacao(populacaoInicial, grafo);

    int zeroos[] = {0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 5, 4, 8, 7, 6, 0, 0, 10, 12, 11, 0, 0, 0, -1};


    removeZerosDoLado(zeroos);

    imprimirSolInt(zeroos);




    destroiPopulacao(populacaoInicial, grafo);
    destroiGrafo(grafo);
    destroiVetPtsEntrada(vetorPontosEntrada);



    return 0;
}

char* defineBuffer (FILE* file, size_t bufsize){
    // Lê a primeira linha do arquivo e guarda no buffer 

    char* buffer = NULL;
    buffer = (char*)malloc(bufsize* sizeof(char));
    getline(&buffer, &bufsize, file);

    return buffer;
}


    // // //////////////// FUNCTION LOOP TIME
    // end_t = clock();
    // while(1){
    //     end_t = clock();
    //     total_t = (double)end_t - (double)start_t;
    //     total_t =  (total_t/ CLOCKS_PER_SEC); // Sem funções printf(), o tempo dá certo
    //     // printf("current elapseed: %lf\n", total_t );
    //     if (total_t > 0.5){
    //         // printf("Total time taken by CPU: %lf\n", total_t ); //Em microsegundos (10^-6)
    //         // printf("Exiting of the program...\n");
    //         break;
    //     }
    // }