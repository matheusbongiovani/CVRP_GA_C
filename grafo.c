#include "grafo.h"

struct grafo{
    int nVeiculos;
    int nCidades;
    double capacidadeV;
    double demandaTotal;
    double ** matrizDistancias;
};

Grafo * criaGrafo(){
    // Aloca estrutura grafo 
    Grafo * grafo = (Grafo*) malloc(sizeof(Grafo));
    return grafo;
}

void inicializaGrafo(Grafo * grafo, int nVeiculos, int nCidades, double capacidadeV, double demandaTotal){
    grafo->nVeiculos = nVeiculos;
    grafo->nCidades = nCidades; // Inclui uma unidade referente ao depósito 
    grafo->capacidadeV  = capacidadeV;
    grafo->demandaTotal = demandaTotal;
    grafo->matrizDistancias = NULL;
}

int retornaNCidades(Grafo * grafo){
    return grafo->nCidades;
}

int retornaNVeiculos(Grafo * grafo){
    return grafo->nVeiculos;
}

double retornaDemandaTotal(Grafo * grafo){
    return grafo->demandaTotal;
}

double retornaCapacidadeMaxVeiculo(Grafo * grafo){
    return grafo->capacidadeV;
}

double ** retornaMatrizDistancias(Grafo * grafo){
    return grafo->matrizDistancias;
}

void insereMatrizDistancias(Grafo * grafo, double ** matriz){
    grafo->matrizDistancias = matriz;
}

// SUBSTITUIR A LISTA POR VET[];
void geraMatrizDistancias(Grafo * grafo, ListaPonto * lista){
    double ** matrizDistancias = (double **) malloc(sizeof(double*)*(grafo->nCidades));
    for(int i = 0; i < grafo->nCidades; i++){
        matrizDistancias[i] = (double *) malloc(sizeof(double)*(grafo->nCidades));
    }
    // Terminada a alocação da matriz 

    // Preenchendo matriz com distâncias entre cidades 
    distanciaPontos(lista, matrizDistancias, grafo->nCidades);

    // Inserção da matriz no grafo 
    insereMatrizDistancias(grafo, matrizDistancias);
}

void destroiMatriz(Grafo* grafo){
    for(int i = 0; i < grafo->nCidades; i++){
        free(grafo->matrizDistancias[i]);
    }
    free(grafo->matrizDistancias);
}

double retornaDistancia(Grafo * grafo, int cidade1, int cidade2){
    return grafo->matrizDistancias[cidade1][cidade2];
}

void destroiGrafo(Grafo * grafo){
    destroiMatriz(grafo);
    free(grafo);
}
