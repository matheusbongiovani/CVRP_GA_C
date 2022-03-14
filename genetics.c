#include "genetics.h"

typedef struct celula Celula;

struct celula{
    ListaPonto* listap;
    Celula* prox;
};

struct listaPopulacao{
    Celula* prim;
    Celula* ult;
};

int tamanhoListaPopulacao(ListaPopulacao* pop){
    int i = 0;
    Celula* p = pop->prim;
    while(p!=NULL){
        p = p->prox;
        i++;
    }
    return i;
}

ListaPopulacao* AlocarPoplist(){
    ListaPopulacao* vetorPopulacao = (ListaPopulacao*)malloc(sizeof(ListaPopulacao));
    vetorPopulacao->prim = NULL;
    vetorPopulacao->ult = NULL;

    return vetorPopulacao;
}

void appendSolucaoNaPopulacao(ListaPonto* solucao, ListaPopulacao* populacao){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->listap = solucao;
    nova->prox = NULL;

    if(populacao->ult == NULL){
        populacao->prim = populacao->ult = nova;
    }else{
        populacao->ult->prox = nova;
        populacao->ult = nova;
    }
}

void destroiPopulacao(ListaPopulacao* popList){
    Celula* p;
    Celula* t;
    p = popList->prim;

    while(p!=NULL){
        t = p->prox;
        destroiListaDuplicada(p->listap);
        free(p);
        p = t;
    }
    free(popList);
}






double fitness(ListaPonto* solucao, Grafo* grafo){
    double cost = 0;
    int i = 0;
    int tamlist = tamanhoLista(solucao);

    //1º nó da 1ª rota
    cost += retornaDistancia(grafo, 0, retornId(retornaPontoPosicaoNaLista(0,solucao)));
    
    for(i = 0; i < tamlist-1; i++)
        cost += retornaDistancia(grafo,retornId(retornaPontoPosicaoNaLista(i,solucao)), retornId(retornaPontoPosicaoNaLista(i+1,solucao)));

    //último nó da última rota
    cost += retornaDistancia(grafo, retornId(retornaPontoPosicaoNaLista(i,solucao)), 0);

    // Checar nº de rotas, e aplicar penalidade caso exceda capacidade máxima
    i = 0;
    int num_of_depots = 1;
    while (i < tamlist){
        if (retornId(retornaPontoPosicaoNaLista(i,solucao)) == 0)
            num_of_depots++;
        i++;
    }

    i = 0;
    double weight = 0;
    double penalty = 0;
    double demandAtual = 0;
    int IdDemandaAtual = 0;
    double capMaxVeiculo = retornaCapacidadeMaxVeiculo(grafo);

    if (num_of_depots != retornaNVeiculos(grafo)){
        for(i = 0;i < tamlist; i++){
            demandAtual = retornaDemanda(retornaPontoPosicaoNaLista(i,solucao));
            weight += demandAtual;
            IdDemandaAtual = (demandAtual + 0.1); // demanda do depot = 0;
            if (IdDemandaAtual == 0){
                if (weight > capMaxVeiculo){
                    // penalty*50 performed better
                    penalty += (weight - capMaxVeiculo)*50;
                    cost += penalty;
                    weight = 0;
                }
            }
        }
    } 

    return cost;
}

ListaPonto* tornarFactivel(ListaPonto* solucao, Grafo* grafo, ListaPonto* entradaInicial){
    int nCidades = retornaNCidades(grafo);
    removeDepositosDaLista(solucao);

    // boleanos para fazer ajuste de cidades repetidas e que faltam
    int ajustar = 1;
    int noDuplicates = 0;
    int i1 = 0;
    int i2 = 0;
    int idpos1 = 0;
    int idpos2 = 0;
    int cidadeId = 1; // começa pela cidade1 (desconsidera depot)
    int tamlist = tamanhoLista(solucao);

    imprimeListaPonto(solucao);


    // esta funfandoo!!!

    while(ajustar){
        ajustar = 0;
        for(i1 = 0; i1 < tamanhoLista(solucao);i1++){
            for(i2 = 0; i2 < i1; i2++){
                idpos1 = retornId(retornaPontoPosicaoNaLista(i1,solucao));
                idpos2 = retornId(retornaPontoPosicaoNaLista(i2,solucao));
                if(idpos1==idpos2){
                    noDuplicates = 1;
                    for(cidadeId = 1; cidadeId < nCidades; cidadeId++){
                        if(procuraPontoPeloId(cidadeId,solucao)==NULL){
                            Ponto* Pfaltando = procuraPontoPeloId(cidadeId,entradaInicial);
                            atualizarPontoAtPos(i1,Pfaltando,solucao);
                            noDuplicates = 0;
                            break;
                        }
                    if (noDuplicates)
                        removePontoNaPos(i1,solucao);
                    }
                    ajustar = 1;
                }
                if (ajustar)
                    break;
            }
            if (ajustar)
                break;
        }
    }

    imprimeListaPonto(solucao);


    double total = 0;
    double demandaCidadeI = 0;
    int i = 0;
    double kCapMax = retornaCapacidadeMaxVeiculo(grafo);
    Ponto* depot = procuraPontoPeloId(0,entradaInicial);

    while(i < tamanhoLista(solucao)){
        demandaCidadeI = retornaDemanda(retornaPontoPosicaoNaLista(i,solucao));
        total += demandaCidadeI;
        if(total > kCapMax){
            insereDepotAantesPos(i, depot, solucao);
            total = 0;
        }
        i++;
    }

    int tam = tamanhoLista(solucao);

    imprimeListaPonto(solucao);
    return solucao;
}

ListaPopulacao* criarPopulacaoInicial(ListaPonto* listaEntrada, Grafo* grafo, int tamPop){
    ListaPopulacao* initialPop = AlocarPoplist();
    int tam = 0;
    while(tam < tamPop){
        ListaPonto* solucao = shuffleListaPonto(listaEntrada);
        solucao = tornarFactivel(solucao, grafo, listaEntrada);
        appendSolucaoNaPopulacao(solucao,initialPop);        
        tam++;
    }
    return initialPop;
}

ListaPonto* aplicarMutacao(ListaPonto* solucao, double probMutate, ListaPonto* entrada){
    int prob0a100 = rand() % 100;
    double rprob = (double)prob0a100/100;
    if (rprob < probMutate){
        int tamL = (tamanhoLista(solucao)-1); // -1 porque começa de 0.
        int index1 = rand() % tamL;
        int index2 = rand() % (tamL-index1);
        index2 += index1 +1;
        reverseEntreCuts(solucao, index1,index2, entrada);
    }
    return solucao;
}


ListaPonto* retornaSolucaoNoIndexDaPopulacao(int i, ListaPopulacao* poplist){
    Celula* p = poplist->prim;
    int j;
    for(j = 0; p!=NULL; p=p->prox){
        if(i==j){
            return p->listap;
        }
        j++;
    }
    return NULL;
}

ListaPonto* tournamentSelect(ListaPopulacao* popList, Grafo* grafo){
    int tamPopList = retornaNCidades(grafo)*2;
    int numSelects = round(tamPopList/10 -0.5);
    double best = 999999;
    double fitSelected;
    int i, irand, iSelecionado;

    for(i = 0; i < numSelects; i++){
        irand = rand() % tamPopList;
        ListaPonto* selecionado = retornaSolucaoNoIndexDaPopulacao(irand,popList);
        fitSelected = fitness(selecionado,grafo);
        if (fitSelected < best){
            best = fitSelected;
            iSelecionado = irand;
        }
    }
   return retornaSolucaoNoIndexDaPopulacao(iSelecionado, popList);
}

ListaPopulacao* duplicarPopulacao(ListaPopulacao* oldPop){
    ListaPopulacao* newPop = AlocarPoplist();
    Celula* p;
    Celula* t;
    p = oldPop->prim;

    int i = 0;
    while(p!=NULL){
        appendSolucaoNaPopulacao(p->listap, newPop);
        t = p->prox;
        p = t;
        i++;
    }

    return newPop;
}

ListaPopulacao* SelectApplyCrossoverMutateAndAppendToNewPop(ListaPonto* entrada,  double probMutate, Grafo* grafo, ListaPopulacao* oldPop){
    ListaPopulacao* newPop = AlocarPoplist();

    // Para termos a população constante, iteramos o tamanho da população divido por 2
    // já que em cada iteração são gerado 2 membros da nova geração
    int tamPop = retornaNCidades(grafo)*2;
    int half_pop = (tamPop/2);
    for(int i = 0; i < half_pop; i++){
        ListaPonto* lp1 = tournamentSelect(oldPop, grafo);
        ListaPonto* lp2 = tournamentSelect(oldPop, grafo);

        int tamL1 = (tamanhoLista(lp1)-1);
        int tamL2 = (tamanhoLista(lp2)-1);
        int tamLMin = (tamL1<tamL2) ? tamL1 : tamL2 ; // -1 porque começa de 0.
        int index1 = rand() % tamLMin;      // index de cortes
        int index2 = rand() % (tamLMin-index1);
        index2 += index1 +1;
        // faz com que as listas lp1 e lp2 se tornem os decendentes da prox geracao
        // novaListaEntreCuts == Crossover()
        aplicarCrossover(lp1, lp2, index1, index2, entrada);
    
        lp1 = aplicarMutacao(lp1, probMutate, entrada);
        lp2 = aplicarMutacao(lp2, probMutate, entrada);

        lp1 = tornarFactivel(lp1, grafo, entrada);
        lp2 = tornarFactivel(lp2, grafo, entrada);

        appendSolucaoNaPopulacao(lp1, newPop);
        appendSolucaoNaPopulacao(lp2, newPop);
    }
    // destroiPopulacao(oldPop);
    return newPop;
}

ListaPonto* runGeneticAlgorithm(double timeToExec, ListaPonto* entrada,  double probMutate, Grafo* grafo){
    int tamPop = retornaNCidades(grafo)*2;
    ListaPopulacao* poplist = criarPopulacaoInicial(entrada, grafo, tamPop);
    clock_t start_t, end_t;
    start_t = clock();
    double total_t;
    double currentMutatProb = probMutate;
    ListaPonto* solutionAtIndex = NULL;
    ListaPonto* bestSolutionAtual = NULL;
    ListaPonto* bestSolutionGlobal = NULL;  
    double bestFitAtual = 999999;
    double bestFitGlobal = 999999;
    double fitAtIndex = 0;
    double time_to_best_solution = 0;

    int index_geracao_atual = 0;
    int iteracoes_sem_melhora = 0;
    int num_iteracoes_melhor_solucao = 0;

    
    while(1){
        index_geracao_atual++;

        poplist = SelectApplyCrossoverMutateAndAppendToNewPop(entrada, currentMutatProb, grafo, poplist);

        for(int i = 0; i< tamPop; i++){
            solutionAtIndex = retornaSolucaoNoIndexDaPopulacao(i, poplist);
            fitAtIndex = fitness(solutionAtIndex, grafo);
            if(fitAtIndex < bestFitAtual){
                bestFitAtual = fitAtIndex;
                bestSolutionAtual = solutionAtIndex;
            }
        }
        if(bestFitAtual >= bestFitGlobal){
            iteracoes_sem_melhora++;
            currentMutatProb += 0.01;
        }else{
            bestSolutionGlobal = bestSolutionAtual;
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
            printf("Total time taken by CPU: %lf\n", total_t ); //Em microsegundos (10^-6)
            break;            
        }

    }
    printf("-----------------------------------------------------------------------------\n");
    printf("fitness melhor entre todas gerações: %lf -- melhor fitness atual: %lf \n",bestFitGlobal, bestFitAtual);
    printf("num de iterações: %d, iterações sem melhora: %d, iterações pra melhor solução: %d, tempo de exc da melhor solução: %lf \n", index_geracao_atual, iteracoes_sem_melhora, num_iteracoes_melhor_solucao, time_to_best_solution);
    printf("-----------------------------------------------------------------------------\n");
    imprimeListaPonto(bestSolutionGlobal);


    return bestSolutionGlobal;

}