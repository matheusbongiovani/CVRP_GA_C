#include "genetics.h"



int* shuffleVetInt(int* solucao, Grafo* grafo){
    int N = retornaNCidades(grafo)-1 ;
    int i = 0;
    
    for(i = 0; i < N-1; i++){
        int j = rand() % N;
        int temp = solucao[i];
        solucao[i] = solucao[j];
        solucao[j] = temp;    
    }
    return solucao;
}

int* removeZerosNaSolu(int* solucao, Grafo* grafo){
    int i, j;
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*2)-1;
    for(i = 0; solucao[i]!= -1; i++){
        if (solucao[i] == 0){
            for(j = i; solucao[j] != -1 ; j++){
                solucao[j] = solucao[j+1];
            }
        }
    }
    return solucao;
}

int* removeZerosDoLado(int* solucao){
    int i, j;
    for(i = 0; solucao[i]!= -1; i++){
        if (solucao[i] == 0 && solucao[i+1]== 0){
            for(j = i; solucao[j] != -1 ; j++){
                solucao[j] = solucao[j+1];
                i--;
            }
        }
    }
    return solucao;
}

int contarDepositosNaSolu(int* solucao){
    int count = 0;
    for(int i = 0; solucao[i]!= -1; i++){
        if (solucao[i] == 0)
            count++;
    }
    return count;   
}


double fitness(int* solucao, Grafo* grafo, VetorPontos* entrada){
    removeZerosDoLado(solucao);
    double cost = 0;
    int i = 0;

    cost += retornaDistancia(grafo, 0, solucao[0]); //1º nó da 1ª rota

    for(i =0; solucao[i] != -1; i++){
        cost += retornaDistancia(grafo, solucao[i], solucao[i+1]);
        if(solucao[i+2] == -1){
            i++;
            break;
        }
    }
    cost += retornaDistancia(grafo, solucao[i], 0);

    int numDepot = contarDepositosNaSolu(solucao);

    if (numDepot+1 != retornaNVeiculos(grafo)){
        int j = 0;
        double capMaxVeic = retornaCapacidadeMaxVeiculo(grafo);
        double weight = 0;
        double penalty = 0;
        for(j = 0; solucao[j] != -1; j++){
            weight += retornaDemanda(procuraPontoPeloId(solucao[j], entrada));
            if(solucao[j]==0){
                if (weight > capMaxVeic){
                    // penalty*50 performed better
                    penalty += (weight - capMaxVeic)*50;
                    cost += penalty;
                    weight = 0;
                }
            }
        }
    }

    return cost;
}



int* distribuirZerosNaSolu(int* solucao, Grafo* grafo, VetorPontos* entrada){
    int i = 0;
    double cargaAtual = 0;
    double reachedTotalDemand = 0;
    double capacidadeVeiculo = retornaCapacidadeMaxVeiculo(grafo);
    double totalDemand = retornaDemandaTotal(grafo);
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*2)-1;
    int j = 0;
    while(reachedTotalDemand < totalDemand){
        Ponto* cidadeAtual = procuraPontoPeloId(solucao[i], entrada);
        int demandaAtual = retornaDemanda(cidadeAtual);
        cargaAtual += demandaAtual;

        reachedTotalDemand += demandaAtual;
        if(cargaAtual > capacidadeVeiculo){
            //trecho para inserir o Depot antes de sobrecarregar
            for(j = vetTamMax-1; j >= i-1 ; j--){
                solucao[j+1] = solucao[j];
            }
            solucao[i] = 0;
            reachedTotalDemand -= demandaAtual;
            cargaAtual = 0;
        }
        if(j != vetTamMax-1)
            i++;
    }
    solucao[i] = -1;   // delimitador de fim da solucao
    return solucao;
}


// double fitness(int* solucao, Grafo* grafo){
//     double cost = 0;
//     int i = 0;
//     int tamlist = tamSolucaoInt(solucao);

//     //1º nó da 1ª rota. Id do Depot == 1!!
//     cost += retornaDistancia(grafo, 0, solucao[i]);
    
//     for(i = 0; i < tamlist-1; i++)
//         cost += retornaDistancia(grafo,solucao[i],solucao[i+1]);

//     //último nó da última rota
//     cost += retornaDistancia(grafo, solucao[i], 0);

// }

int* criarSolucaoInt(VetorPontos* vet, Grafo* grafo){
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*2);
    int* solucao = (int*)malloc(sizeof(int)*vetTamMax);
    for(int i =0; i < (vetPtsTamInicial(vet)-1); i++){
        solucao[i] = i+1;
    }
    return solucao;
}



int** criarPopulacaoInicial(VetorPontos* entrada, Grafo* grafo){
    int tamPop = retornaNCidades(grafo)*2;

    int** populacao = (int**)malloc(sizeof(int*)*tamPop);

    for(int i = 0; i < tamPop; i++){
        int* novoElem = criarSolucaoInt(entrada, grafo);
        shuffleVetInt(novoElem, grafo);
        distribuirZerosNaSolu(novoElem, grafo, entrada);
        populacao[i] = novoElem;
    }

    return populacao;
}



void imprimirSolInt(int* solucao){
    for(int j = 0; solucao[j]!= -1; j++){
        printf("%d, ",solucao[j]);
    }    
}


void imprimirElemsPopulacao(int** populacao, Grafo* grafo){
    int tamPop = retornaNCidades(grafo)*2;
    for(int i =0 ; i < tamPop; i++){
        for(int j = 0; populacao[i][j]!= -1; j++){
            printf("%d, ",populacao[i][j]);
        }
        printf("\n");
    }
}

































void destroiPopulacao(int** populacao, Grafo* grafo){
    int tamPop = retornaNCidades(grafo)*2;
    for(int i =0 ; i < tamPop; i++){
        free(populacao[i]);
    }
    free(populacao);

}
