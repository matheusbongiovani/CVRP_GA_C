#include "genetics.h"

double fitness(ListaPonto* lista, Grafo* grafo){
    double cost = 0;
    int i = 0;
    int tamlist = tamanhoLista(lista);

    //1º nó da 1ª rota
    cost += retornaDistancia(grafo, 0, retornId(retornaPontoPosicaoNaLista(0,lista)));
    
    for(i = 0; i < tamlist-1; i++)
        cost += retornaDistancia(grafo,retornId(retornaPontoPosicaoNaLista(i,lista)), retornId(retornaPontoPosicaoNaLista(i+1,lista)));

    //último nó da última rota
    cost += retornaDistancia(grafo, retornId(retornaPontoPosicaoNaLista(i,lista)), 0);

    return cost;

}




































int calculaTamanhoVetorRotas(Grafo* grafo){
    /* O vetor irá conter cada rota e cada rota será delimitada por um depósito no início e no fim
     *
     * Exemplo de vetor com 2 rotas:
     * 0 5 10 3 14 0 2 4 1 6 7 8 9 11 12 13 0
     * */
    return retornaNCidades(grafo) + retornaNVeiculos(grafo);
}

int* alocaVetor(int tamVetor){
    int* vetorRotas = (int*) malloc (sizeof (int)* (tamVetor));
    return vetorRotas;
}

void imprimeVetor(int* vetorRotas, int k){
    for(int i = 0; i < k; i++){
        printf("%d ", vetorRotas[i]);
    }
}

void imprimeResultado(int* vetorRotas, int k, double custo){

    int y = 1; /* conta os zeros encontrados nas rotas para dar inicio e fim a rota */
    printf("Route #1: ");

    for (int i = 1; i < k-1; i++){
        if(vetorRotas[i] != 0){
            printf("%d ", vetorRotas[i]);
        }else{
            y++;
            printf("\nRoute #%d: ", y);
        }
    }
    printf("\ncusto: %.2lf", custo);
}

void geraSolucaoInicialRandom(Grafo * grafo, int * vetorRotaAleatorio, ListaPonto * listaPontos, int numAleatorio){
    /* Declarando vetor que conterá cidades excluindo o depósito */
    int nCidades = retornaNCidades(grafo);

    int cidades[nCidades]; /* Vetor de cidades de 0 a 31 (para o primeiro exemplo, sendo 0 o depósito) */
    for(int i = 0; i < nCidades ; i++){
        cidades[i] = i; /* De 1 a nCidades-1 são as cidades */
    }

    vetorRotaAleatorio[0] = 0; /* A primeira posição do vetor se refere ao depósito, de onde os carros partem */
    cidades[1] = numAleatorio;
    cidades[numAleatorio] = 1;
    int contador = 0, cidadeAtual = 0 /* <=Começa sendo o depósito */,
            proximaCidade, deposito = 0, aux, k=1;
    double proximoCusto, custoAtual, demandaAtual, novaDemanda = 0;
    double demandaTotal = 0;
    double capacidade = retornaCapacidade(grafo); /* Se refere a capacidade de cada veículo */

    while(nCidades-1 != contador){
        proximoCusto = 0;
        custoAtual = 0;
        demandaAtual = 0;
        aux = 0;
        for(int i = 0; i < nCidades; i++){
            proximaCidade = cidades[i];
            novaDemanda = retornaDemanda(procurandoPonto(cidades[i], listaPontos));
            /* A próxima cidade deve ser a mais próxima da cidade atual e sua demanda não deve utrapassar a capacidade do carro,
             * portanto, é feita uma verificação entre a cidade atual e todas as outras */
            if(proximaCidade != deposito && demandaTotal+novaDemanda < capacidade){
                /* A matriz de distancia não possui distâncias repetidas, portanto, é sempre retorna a
                 * distancia da cidade de maior rótulo para a
                 * cidade de menor rotulo, portanto o if else serve para ordenar essa ordem de pesquisa */
                if(cidadeAtual > proximaCidade){
                    proximoCusto = retornaDistancia(grafo, cidadeAtual, proximaCidade);
                }else{
                    proximoCusto = retornaDistancia(grafo, proximaCidade, cidadeAtual);
                }

                /* Verificando se o custo da proxima cidade
                 * é menor que o custo da cidade atual */
                if ((proximoCusto != 0) && (proximoCusto < custoAtual)){
                    custoAtual = proximoCusto;
                    aux = i;
                    demandaAtual = novaDemanda;
                }else if (custoAtual == 0 && proximoCusto != 0){ /* Na primeira iteração, o custo atual é zero, portanto, qualquer primeiro custo
                                                                * diferente de zero será o próximo */
                    custoAtual = proximoCusto;
                    aux = i;
                    demandaAtual = novaDemanda;
                }else if((proximoCusto == custoAtual) && (demandaAtual < novaDemanda)){ /* Buscando a demanda que
                                                                                        * vai ocupar a rota mais rapidamente */
                    custoAtual = proximoCusto;
                    aux = i;
                    demandaAtual = novaDemanda;
                }
                if(k==1){
                    aux = 1;
                }
            }
        }
        /* k começa sendo 1 na primeira iteração */
        /* No vetorRotas, as cidades ficam na posição vetorRotas[1] em diante, e quando usamos k=1, queremos
        * pular a primeira posição vetorRotas[0] que se refere ao deposito
        * Depois, k servirá para percorrer  o vetor e em cada posição que ele referenciar, será
        * colocada uma cidade, ou um deposito caso uma  rota termine */

        if (demandaTotal+demandaAtual < capacidade && demandaAtual != 0){
            /*
             * Somando a nova demanda a demandaTotal da rota.
             * Adicionando uma nova cidade a rota.
             */
            demandaTotal += demandaAtual; /* Demanda é acrescida da demanda da cidade escolhida para manter o controle de que a capacidade do veículo não será ultrapassada */
            vetorRotaAleatorio[k] = cidades[aux]; /* Vetor de rotas recebe a cidade que foi a melhor opção para ir a partir da que estávamos avaliando */
            k++; /* Fica na próxima posição do vetor de rotas */
            cidadeAtual = cidades[aux]; /* Para que a próxima avaliação parta da cidade que acabou de ser inserida */
            cidades[aux] = deposito; /* A cidade inserida no vetor de rotas é mudada para zero para que não seja mais avaliada */
            contador++; /* Contador do while */
        }else{
            /*
             * Terminando a rota e iniciando uma nova rota.
             */
            vetorRotaAleatorio[k] = 0; /* Zero se refere ao deposito */
            k++;
            demandaTotal = 0;
            cidadeAtual = 0;
        }
    }
    vetorRotaAleatorio[k] = deposito; /* Dando fim na rota */
}

double calculaCustoRota(Grafo * grafo, int * vetorRotas, int tamVetor){
    double custo = 0;
    for(int i = 0; i < tamVetor-1; i++){
        /* A distancia sempre é calculada da cidade de maior rótulo para a cidade de menor rótulo,
         * por isso a necessidade do if else */
        if(vetorRotas[i] > vetorRotas[i+1]){
            custo += retornaDistancia(grafo, vetorRotas[i], vetorRotas[i+1]);
        }else{
            custo += retornaDistancia(grafo, vetorRotas[i+1], vetorRotas[i]);
        }
    }
    return custo;
}

int * buscaLocal(int * rotaVizinha, int * vetorRotas, int  tamVetor, Grafo * grafo, double custo){
    int deposito = 0;
    for (int i = 0; i < tamVetor; i++){
        rotaVizinha[i] = vetorRotas[i];
    }

    int aux;
    for (int x = 0; x < tamVetor-1; x++){
        if(vetorRotas[x] == deposito){
            for (int y = x+1; vetorRotas[y] != deposito; y++){
                for (int z = y+1; vetorRotas[z] != deposito; z++){
                    /* Troca de cidades 2-opt para gerar nova vizinhança x' */
                    /* As cidades são trocadas 2 a 2: a primeira com a segunda, depois
                     * a primeira com a quarta e a segunda com a terceira e por aí vai */
                    for (int i = y, w = z; i < w; i++, w--){
                        aux = rotaVizinha[i];
                        rotaVizinha[i] = rotaVizinha[w];
                        rotaVizinha[w] = aux;
                    }
                    if (custo <= calculaCustoRota(grafo, rotaVizinha, tamVetor)){
                        /* Caso o custo da rota inicial seja menor que o da rota que acabou de ser definida, a troca
                         * é desfeita porque não terá valido a pena */
                        for (int i = y, w = z; i < w; i++, w--){
                            aux = rotaVizinha[i];
                            rotaVizinha[i] = rotaVizinha[w];
                            rotaVizinha[w] = aux;
                        }
                    }
                }
            }
        }
    }
    return rotaVizinha;
}

int * geraXisLinha(int * xLinha, int * vetorRotas, int tamVetor, double custo, ListaPonto * listaPontos, Grafo * grafo){
    /* Realiza a troca de cidades duas a duas, exemplo, 1 com 2, 1 com 3 ... Depois 2 com 3, 2 com 4 */
    /* O x' não precisa ter um custo melhor que o de x, porém precisamos garantir que a capacidade
     * dos veículos não seja ultrapassada */

    double capacidadeVeiculos = retornaCapacidade(grafo);

    /* O custo se refere ao custo do vetorRotas que é passado como parâmetro */
    for (int i = 0; i < tamVetor; ++i){
        xLinha[i] = vetorRotas[i];
    }

    int aux = 0, deposito = 0;
    double demanda, capacidadeDaRota;
    for (int a = 1; a < tamVetor-1; a++){
        for (int b = a+1; b < tamVetor-1; b++){
            /* Troca de posição de duas cidades em um vetor de rotas */
            aux = xLinha[a];
            xLinha[a] = xLinha[b];
            xLinha[b] = aux;

            if (calculaCustoRota(grafo, xLinha, tamVetor) < custo) {
                capacidadeDaRota = 0; /* A uma rota vai de um zero ao outro num vetor. Caso uma das rotas de um conjunto de rotas
                                    * ultrapasse a capacidade de um veículo, o conjunto para de ser avaliado e a
                                    * troca que foi feita é desfeita */

                for (int i = 0; i < tamVetor; i++) {
                    if (xLinha[i] != deposito) {
                        /* Retornando a demanda de uma cidade a partir de seu rótulo */
                        demanda = retornaDemanda(procurandoPonto(xLinha[i], listaPontos));
                        capacidadeDaRota += demanda;
                    } else {
                        capacidadeDaRota = 0;
                    }
                    /* Caso a capacidade de um veículo seja ultrapassada */
                    if (capacidadeDaRota >= capacidadeVeiculos) {
                        capacidadeDaRota = -1; /* Flag que indica que um veiculo teve sua capacidade ultrapassada */
                        break;
                    }
                }
                if (capacidadeDaRota == -1) {
                    /* Desfazendo trocas caso a capacidade de algum veículo seja ultrapassada */
                    aux = xLinha[b];
                    xLinha[b] = xLinha[a];
                    xLinha[a] = aux;
                }else{
                    custo = calculaCustoRota(grafo, xLinha, tamVetor);
                }
            }else{
                /* Desfazendo trocas caso a capacidade de algum veículo seja ultrapassada */
                aux = xLinha[b];
                xLinha[b] = xLinha[a];
                xLinha[a] = aux;
            }
        }
    }
    return xLinha;
}

void vns(int* vetorRotas, int tamVetor, Grafo * grafo, ListaPonto * listaPontos){

    /* Alocando o vetor que conterá as rotas atualizadas de todos os veículos de acordo com a necessidade */
    int * vetorRotasNovas;
    int * rotaVizinha = alocaVetor(tamVetor);

    time_t t;
    srand((unsigned)time(&t));
    int r= rand()%(retornaNCidades(grafo));
    /* Geração gulosa de uma solução inicial x */
    geraSolucaoInicialRandom(grafo, vetorRotas, listaPontos, r);

    double custo = calculaCustoRota(grafo, vetorRotas, tamVetor);

    vetorRotas = buscaLocal(rotaVizinha, vetorRotas, tamVetor, grafo, custo);

    /* Atualização do custo */
    custo = calculaCustoRota(grafo, vetorRotas, tamVetor);


    double custoAnterior = 0;
    int kmax = 80,
        k = 1;
    while(custo != custoAnterior && k < kmax){
        /* vetorRotas se refere a solução inicial x
         * vetorRotasNovas se refere a x' e x'' */

        /* Para atualização do while */
        custoAnterior = custo;

        /* A partir da solução inicial que é x, gera-se um x' */
        vetorRotasNovas = geraXisLinha(rotaVizinha, vetorRotas, tamVetor, custo, listaPontos, grafo);

        /* Aplica-se uma busca local para chegar em x'' */
        vetorRotasNovas = buscaLocal(rotaVizinha, vetorRotasNovas, tamVetor, grafo, custo);

        if (calculaCustoRota(grafo, vetorRotas, tamVetor) < calculaCustoRota(grafo, vetorRotasNovas, tamVetor)){
            /* Então f(x'') é melhor que f(x) */
            /* x <- x'' */
            custo = calculaCustoRota(grafo, vetorRotas, tamVetor);
        }else{
            for(int i = 0; i< tamVetor; i++){
                vetorRotas[i] = vetorRotasNovas[i];
            }
            custo = calculaCustoRota(grafo, vetorRotas, tamVetor);
        }
        k++;
    }
    printf("\nTotal de iterações do while: %d\n",k);

    imprimeResultado(vetorRotas, tamVetor, custo);
    printf("\nnumero aleatorio: %d\n", r);
    free(rotaVizinha);
}