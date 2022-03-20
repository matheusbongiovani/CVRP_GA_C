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

    // imprimeVetPtsInicial(entrada);


    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*2); // TAM DA POPULAÇÃO



        // int* sol1 = criarSolucaoInt(entrada, grafo);
        // distribuirZerosNaSoluInicial(sol1, grafo, entrada);
        // imprimirSolInt(sol1);
        // printf("\nantes ^^^... dps: \n");
        // // removeIdNaPos(0, sol1);
        // // insereZeroAntesPos(0, sol1, grafo);
        // // removeZerosDoLado(sol1);
        // imprimirSolInt(sol1);
        // int tsmdfsa = tamanhoSolucao(sol1);
        // double fitva = fitness(sol1, grafo, entrada);
        // // printf("%d \n", idEstaContidoNaSolu(2,sol1));

        // free(sol1);



    int** oldPop = criarPopulacaoInicial(entrada, grafo);

    // imprimirElemsPopulacao(oldPop, grafo);
    // destroiPopulacao(oldPop, grafo);


    int** newPop = criarNOVApopulacao(oldPop, 0.05, grafo, entrada);
    imprimirElemsPopulacao(newPop, grafo);
    destroiPopulacao(newPop, grafo);





    destroiGrafo(grafo);
    destroiVetPtsEntrada(entrada);
    return 0;
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