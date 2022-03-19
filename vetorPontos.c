#include "vetorPontos.h"

struct vetorPontos{
    Ponto** ponto;
    int tam;
};

VetorPontos* inicializaVetorPonto(){
    // Aloca vetor inicial de pontos 
    VetorPontos* pontosEntrada = (VetorPontos*)malloc(sizeof(VetorPontos));
    pontosEntrada->tam = 0;
    pontosEntrada->ponto = NULL;
    return pontosEntrada;
}

int vetPtsTamInicial(VetorPontos* vet){
    return vet->tam;
}

void atualizaTamVet(int n_genes, VetorPontos* vet){
    vet->tam = 0;
    vet->ponto = criaVetPontoTam(n_genes);

}


void appendPonto(Ponto* p, VetorPontos* vet){
    int posicao = vet->tam;
    vet->ponto[posicao] = p;
    vet->tam++;
}

Ponto* procuraPontoPeloId(int id, VetorPontos* vet){
    return vet->ponto[id];
}

void imprimeVetPtsInicial(VetorPontos* vet){
    for(int i = 0; i< vet->tam;i++){
        printf("%d ", retornId(vet->ponto[i]));
    }
    printf("\n");
}



void destroiVetPtsEntrada(VetorPontos* vet){
    int tamVet = vetPtsTamInicial(vet);
    int i = 0;
    for(int i = 0; i < tamVet; i++){
        destroiPonto(vet->ponto[i]);
    }
    free(vet->ponto);
    free(vet);
} 











void distanciaPontos(VetorPontos* vet, double** matriz, int numCidades){
    int i, j;
    double dist = 0;
    // Matrix quadrada contendo distância entre todas as cidades
    for(i = 0; i < numCidades ; i++){
        for(j = 0; j < numCidades; j++){
            // Calcula a distância entre os pontos 
            dist = distanciaEntrePontos(procuraPontoPeloId(i, vet), procuraPontoPeloId(j, vet));
            matriz[i][j] = dist;
        }
    }
}
