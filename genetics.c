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

int idEstaContidoNaSolu(int id, int* solucao){
    int contido = 0;
    for(int i = 0; solucao[i]!= -1; i++){
        int blub;
        if(solucao[i]==id){
            contido = 1;
            break;
        }
    }
    return contido;
}

int* removeZerosNaSolu(int* solucao, Grafo* grafo){
    int i, j;
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*3)-1;
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
                // i--;
            }
        }
    }
    return solucao;
}

int* removeIdNaPos(int pos, int* solucao){
    int i, j;
    if(pos == 0){
        solucao = &solucao[1];
            for(j = -1; solucao[j] != -1 ; j++){
                solucao[j] = solucao[j+1];
            }
        return solucao;
    }
    for(i = 0; solucao[i]!= -1; i++){
        if (i = pos){
            for(j = i; solucao[j] != -1 ; j++){
                solucao[j] = solucao[j+1];
            }
        break;
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

void insereZeroAntesPos(int pos, int* solucao, Grafo* grafo){
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*3)-2;
    int j;

    for(j = vetTamMax; j >= pos; j--){
        solucao[j+1] = solucao[j];
    }
    solucao[pos] = 0;
}

int tamanhoSolucao(int* solucao){
    int j = 0;
    for(j = 0; solucao[j]!= -1; j++);

    return j;
}

int* distribuirZerosNaSoluInicial(int* solucao, Grafo* grafo, VetorPontos* entrada){
    int i = 0;
    double cargaAtual = 0;
    double reachedTotalDemand = 0;
    double capacidadeVeiculo = retornaCapacidadeMaxVeiculo(grafo);
    double totalDemand = retornaDemandaTotal(grafo);
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*3)-1;
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

void distribuirZerosRecorrente(int* solucao, Grafo* grafo, VetorPontos* entrada){
    double total = 0;
    double demandaCidadeI = 0;
    int i = 0;
    double kCapMax = retornaCapacidadeMaxVeiculo(grafo);

    while(i < tamanhoSolucao(solucao)){
        demandaCidadeI = retornaDemanda(procuraPontoPeloId(solucao[i], entrada));
        total += demandaCidadeI;
        if(total > kCapMax && total!= 0){
            insereZeroAntesPos(i, solucao, grafo);
            total = 0;
        }
        i++;
    }    
}



double fitness(int* solucao, Grafo* grafo, VetorPontos* entrada){
    removeZerosDoLado(solucao);
    double cost = 0;
    int i = 0;
    // Distância do Depot até a 1ª cidade da 1ª rota
    cost += retornaDistancia(grafo, 0, solucao[0]); 
    // Distância entre as cidades no vetor da solução.
    for(i =0; solucao[i] != -1; i++){
        cost += retornaDistancia(grafo, solucao[i], solucao[i+1]);
        if(solucao[i+2] == -1){
            i++;
            break;
        }
    }
    // Distância da última cidade da última rota até o Depot
    cost += retornaDistancia(grafo, solucao[i], 0); //

    // Checar nº de rotas, e aplicar penalidade caso exceda capacidade máxima
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
                    penalty += (weight - capMaxVeic)*50;
                    cost += penalty;
                    weight = 0;
                }
            }
        }
    }
    return cost;
}

int* tornarFactivel(int* solucao, Grafo* grafo, VetorPontos* entrada){
    removeZerosNaSolu(solucao, grafo);

    int nCidades = retornaNCidades(grafo);
    // boleanos para fazer ajuste de cidades repetidas e que faltam na solução
    int nextDup = 0;
    int i1 = 0;
    int i2 = 0;
    int cidadeId = 1; // começa pela cidade1 (desconsidera depot)
    int ajustar = 1;
    while(ajustar){
        for(i1 = 0; i1< (nCidades-1); i1++){
            nextDup = 0;
            for(i2 = 0; i2 < i1; i2++){
                if(solucao[i1]==solucao[i2]){
                    for(cidadeId=1; cidadeId < nCidades; cidadeId++){
                        if(idEstaContidoNaSolu(cidadeId, solucao) == 0){
                            solucao[i1] = cidadeId;
                            break;
                        }
                    }
                    nextDup = 1;
                }
                if(nextDup)
                    break;
            }
        }
        ajustar = 0;
    }
    distribuirZerosRecorrente(solucao, grafo, entrada);

    return solucao;
}


int* criarSolucaoInt(VetorPontos* entrada, Grafo* grafo){
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*3);
    int* solucao = (int*)malloc(sizeof(int)*vetTamMax);
    for(int i =0; i < (vetPtsTamInicial(entrada)-1); i++){
        solucao[i] = i+1;
    }
    return solucao;
}

int* duplicarSolucaoInt(int* pai, Grafo* grafo){
    int vetTamMax = retornaNCidades(grafo)+(retornaNVeiculos(grafo)*3);
    int* filho = (int*)malloc(sizeof(int)*vetTamMax);
    int i;
    for(i = 0; pai[i] != -1; i++)
        filho[i] = pai[i];

    filho[i] = -1;

    return filho;    
}

int* reverseEntreCuts(int* solucao, int cut1, int cut2){
    int N = tamanhoSolucao(solucao);
    int elem[N];
    int toReverse[(cut2-cut1)+1];
    int i = 0;
    int j = 0;

    for(i = cut2, j = 0; i >= cut1; i--, j++){
        toReverse[j] = solucao[i];
    }
    for(i = cut1, j = 0; i <=cut2; i++, j++){
        solucao[i] = toReverse[j];
    }
    return solucao;
}

int* selecaoPorTorneio(int** populacao, Grafo* grafo, VetorPontos* entrada){
    int tamPop = retornaNCidades(grafo)*2;
    int numSelects = round(tamPop/10 -0.5);
    double best = 999999999999;
    double fitSelected;
    int i, irand, iSelecionado;

    for(i = 0; i < numSelects; i++){
        irand = rand() % tamPop;
        int* selecionado = populacao[irand];
        fitSelected = fitness(selecionado, grafo, entrada);
        if(fitSelected < best){
            best = fitSelected;
            iSelecionado = irand;
        }
    }
    return populacao[iSelecionado];
}

int* mutacao(int* solucao, double probMutate){
    int prob0a100 = rand() % 100;
    double rprob = (double)prob0a100/100;
    if(rprob < probMutate){
        int tam = tamanhoSolucao(solucao)-1;
        int cut1 = rand() % tam;
        int cut2 = rand() % (tam - cut1);
        cut2 += cut1 +1;
        reverseEntreCuts(solucao, cut1, cut2);
    }
    return solucao;
}

int** crossover(int* p1, int* p2, Grafo* grafo, VetorPontos* entrada){
    // Gera gera filhos por trecho dos pais. Cortes representados por '/'
    // f1 =  p1/p2/p1 ; f2 = p2/p1/p2
    removeZerosNaSolu(p1, grafo);
    removeZerosNaSolu(p2, grafo);
    int* f1 = duplicarSolucaoInt(p1, grafo);
    int* f2 = duplicarSolucaoInt(p2, grafo);

    int N = retornaNCidades(grafo)-1;

    int cut1 = rand() % N;      // index de cortes
    int cut2 = rand() % (N-cut1);
    cut2 += cut1 +1;
    int tamCut = (cut2-cut1)+1;

    int entreCuts1[tamCut];
    int entreCuts2[tamCut];

    int i, j;
    for(i=cut1, j=0 ; i<=cut2 ; i++, j++){
        entreCuts1[j] = f1[i];
        entreCuts2[j] = f2[i];
    }
    for(i=cut1, j=0 ; i<=cut2 ; i++, j++){
        f1[i] = entreCuts2[j];
        f2[i] = entreCuts1[j];
    }

    distribuirZerosRecorrente(p1, grafo, entrada);
    distribuirZerosRecorrente(p2, grafo, entrada);

    int** childs = (int**)malloc(2*sizeof(int*));
    distribuirZerosRecorrente(f1, grafo, entrada);
    distribuirZerosRecorrente(f2, grafo, entrada);
    childs[0] = f1;
    childs[1] = f2;

    return childs;
}


int** criarPopulacaoInicial(VetorPontos* entrada, Grafo* grafo){
    int tamPop = retornaNCidades(grafo)*2;
    int** populacao = (int**)malloc(tamPop*sizeof(int*));

    for(int i = 0; i < tamPop; i++){
        int* novoElem = criarSolucaoInt(entrada, grafo);
        shuffleVetInt(novoElem, grafo);
        distribuirZerosNaSoluInicial(novoElem, grafo, entrada);
        populacao[i] = novoElem;
    }

    return populacao;
}

int** criarNOVApopulacao(int** oldPop, double prob_mutate, Grafo* grafo, VetorPontos* entrada){
    int tamPop = retornaNCidades(grafo)*2;
    int** newPop = (int**)malloc(tamPop*sizeof(int*));

    for(int i = 0; i < tamPop;){
        int* p1 = selecaoPorTorneio(oldPop, grafo, entrada);
        int* p2 = selecaoPorTorneio(oldPop, grafo, entrada);
        int** filhos = crossover(p1, p2, grafo, entrada);
        int* f1 = filhos[0];
        int* f2 = filhos[1];
        mutacao(f1, prob_mutate);
        mutacao(f2, prob_mutate);
        tornarFactivel(f1, grafo, entrada);
        tornarFactivel(f2, grafo, entrada);
        newPop[i] = f1;
        newPop[i+1] = f2;
        i = i+2;
        free(filhos);
    }

    destroiPopulacao(oldPop, grafo);    
    return newPop;
}


void runGeneticAlgorithm(double timeToExec, double probMutate, VetorPontos* entrada, Grafo* grafo){
    int tamPop = retornaNCidades(grafo)*2;
    int** populacao = criarPopulacaoInicial(entrada, grafo);
    clock_t start_t, end_t;
    start_t = clock();
    double total_t;
    double currentMutatProb = probMutate;
    int* solutionAtIndex = NULL;
    int* bestSolutionAtual = NULL;
    int* bestSolutionGlobal = NULL;  
    double bestFitAtual = 999999999999;
    double bestFitGlobal = 999999999999;
    double fitAtIndex = 0;
    double time_to_best_solution = 0;
    int index_geracao_atual = 0;
    int iteracoes_sem_melhora = 0;
    int num_iteracoes_melhor_solucao = 0;

    while(1){
        index_geracao_atual++;
        populacao = criarNOVApopulacao(populacao, probMutate, grafo, entrada); 
        for(int i = 0; i< tamPop; i++){
            solutionAtIndex = populacao[i];
            fitAtIndex = fitness(solutionAtIndex, grafo, entrada);
            if(fitAtIndex < bestFitAtual){
                bestFitAtual = fitAtIndex;
                bestSolutionAtual = solutionAtIndex;
            }
        }
        if(bestFitAtual >= bestFitGlobal){
            iteracoes_sem_melhora++;
            currentMutatProb += 0.001;
            if(currentMutatProb > 1)
                currentMutatProb = 0.05;
        }else{
            free(bestSolutionGlobal);
            bestSolutionGlobal = duplicarSolucaoInt(bestSolutionAtual, grafo);
            bestFitGlobal = bestFitAtual;
            iteracoes_sem_melhora = 0;
            num_iteracoes_melhor_solucao = index_geracao_atual;
            currentMutatProb = probMutate;
            end_t = clock();
            total_t = (double)end_t - (double)start_t;
            total_t = (total_t/ CLOCKS_PER_SEC);
            time_to_best_solution = total_t;
        }
        end_t = clock();
        total_t = (double)end_t - (double)start_t;
        total_t = (total_t/ CLOCKS_PER_SEC);
        if (total_t >= timeToExec){
            printf("Tempo de Execução do Algoritmo: %.2fs\n", total_t ); 
            break;            
        }
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Melhor fitness entre todas gerações: %.2f -- Melhor fitness da geração atual: %.2f \n",bestFitGlobal, bestFitAtual);
    printf("Nº de iterações: %d -- Iterações sem melhora: %d -- Iterações pra melhor solução: %d -- Tempo de exc da melhor solução: %.2f \n", index_geracao_atual, iteracoes_sem_melhora, num_iteracoes_melhor_solucao, time_to_best_solution);
    printf("------------------------------------------------------------------------------------------------------------------------------------\nCUSTO: %lf, SOLUÇÃO:\n", bestFitGlobal);

    imprimirSolInt(bestSolutionGlobal);
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    imprimeDemandaRotas(bestSolutionGlobal, entrada, grafo);

    free(bestSolutionGlobal);
    destroiPopulacao(populacao, grafo);

}


void imprimeDemandaRotas(int* solucao, VetorPontos* entrada, Grafo* grafo){
    printf("Capacidade máxima dos veículos: %.1f -- Carga em cada rota: [", retornaCapacidadeMaxVeiculo(grafo));
    double cargaRota = 0;
    int numVeiculosMin = 0;
    for(int j = 0; solucao[j]!= -1; j++){
        cargaRota += retornaDemanda(procuraPontoPeloId(solucao[j], entrada));
        if(solucao[j] == 0){
            printf("%.1f, ",cargaRota);
            numVeiculosMin++;
            cargaRota = 0;
        }
    }
    printf(" %.1f]\n",cargaRota);
    numVeiculosMin++;
    if(numVeiculosMin != retornaNVeiculos(grafo)){
        printf("NÃO FOI POSSÍVEL ACHAR UMA SOLUÇÃO FACTÍVEL UTILIZANDO O Nº MÍNIMO DE VEÍCULOS DISPONÍVEIS\n");
        printf("Nº MÍNIMO DE VEÍCULOS DISPONÍVEIS: %d \n", retornaNVeiculos(grafo));
        printf("VEÍCULOS UTILIZADOS NESTA SOLUÇÃO: %d \n", numVeiculosMin);
    }
}

void imprimirSolInt(int* solucao){
    printf("[0,");
    for(int j = 0; solucao[j]!= -1; j++){
        printf(" %d,",solucao[j]);
    }
    printf(" 0]\n");   
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
