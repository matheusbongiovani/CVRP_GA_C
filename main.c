#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "ponto.h"
#include "listaPontos.h"
#include "grafo.h"
#include "genetics.h"
#include <time.h>

char* defineBuffer (FILE* file, size_t bufsize){
    // Lê a primeira linha do arquivo e guarda no buffer 

    char* buffer = NULL;
    buffer = (char*)malloc(bufsize* sizeof(char));
    getline(&buffer, &bufsize, file);

    return buffer;
}



int main(int argc, char** argv) {
    if (argc != 2){
        printf("Sintaxe: ./main A-n32-k5.vrp\n");
        exit(1);
    }
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    FILE * file = NULL;
    file = inicializaArquivo(file, argv[1]);

    // Declaração do buffer
    size_t bufsize = 1;
    char* buffer = defineBuffer(file, bufsize);

    // Inicializa lista que guarda todos os pontos 
    ListaPonto* lista = inicializaListaPonto();

    // Inicializa grafo que conterá informações lidas 
    Grafo* grafo = criaGrafo();

    // Lê o arquivo e preenche a lista de pontos com todos os pontos(cidades), suas coordenadas e demandas 
    leArquivo(file, buffer, bufsize, lista, grafo);

    // Geração da matriz que guarda distancia entre cidades 
    geraMatrizDistancias(grafo, lista);


    int tamLista = tamanhoLista(lista);

// tamanho do vetor com folga pra 2 veiculos a mais que o mín de veículos da melhor solução
    int tamMaxlist = calculaTamanhoVetorRotas(grafo) + 2;

    int* solutionVector = (int*) malloc (sizeof(int)* tamMaxlist);

    // Ponto* pontoAtPos = retornaPontoPosicaoNaLista(4, lista); // retorna ponto at pos i in lista


    // Ponto* depot = extractDepot(lista);  //remove depot da lista, posteriormente tem q: free(depot)

    double fitvalue = fitness(lista, grafo);




















    free(solutionVector);
    // destroiPonto(depot);
    destroiLista(lista);
    destroiGrafo(grafo);


    // //////////////// FUNCTION LOOP TIME
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

    return 0;
}


