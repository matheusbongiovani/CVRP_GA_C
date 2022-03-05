#include "leitura.h"


FILE* inicializaArquivo(FILE* file, char * nomeArq){
    file = fopen(nomeArq, "r");
    if (file == NULL){
        printf("Invalid instance file.\n");
        exit(1);
    }
    return file;
}


void leArquivo(FILE* file, char* buffer, size_t bufsize, ListaPonto * lista, Grafo * grafo){
    char *token; /* Recebe dados separados pelo strtok */

    token = strtok(buffer, "-k"); /* Tira o inicio da linha */
    token = strtok(NULL, "-k"); /* Pega a quantidade de veiculos que restou */
    int k_rotas = atoi(token);

    // trecho para pular linhas da entrada que não será utilizado
    int i = 0;
    while(i < 3){
        getline(&buffer, &bufsize, file);
        i++;
    }

    /* A linha será separada em 3 e queremos a terceira parte, que tem o numero de cidades */
        token = strtok(buffer, " ");  /* Separa os dados da string */
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        /* Recebe NULL para continuar de onde parou */


    int n_genes = atoi(token);

    //trecho para pular linhas da entrada que não será utilizado
    i = 0;
    while(i < 2){
        getline(&buffer, &bufsize, file);
        i++;
    }
    /* Lendo a capacidade de veiculos */
    /* Mudando o separador do token */

        /* A linha será separada em 3 e queremos a terceira parte, que tem a capacidade */
        token = strtok(buffer, " ");  /* Separa os dados da string */
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        /* Recebe NULL para continuar de onde parou */

    int capacidade = atoi(token);

    /* Pulando mais 2 linhas para chegar ate as coordenadas das cidades */
    i = 0;
    while(i < 2){
        getline(&buffer, &bufsize, file);
        i++;
    }

    i = 0;
    /* Leitura das coordenadas de cada cidade */
    while(i < n_genes) { /* Leitura das coordenadas do ponto que foi lido */
        token = strtok(buffer, r);  /* Separa os dados da string */
        double nomePonto = converteNumero(token);
        token = strtok(NULL, r);  /* Separa os dados da string */
        double coord1 = converteNumero(token);
        token = strtok(NULL, r);  /* Separa os dados da string */
        double coord2 = converteNumero(token);
        /* Recebe NULL para continuar de onde parou */

        /* Registrando coordenadas lidas no ponto */
        Ponto * ponto = criaPonto(nomePonto-1, coord1, coord2); /* nomePonto-1 porque a resposta será de 0 até nCidades-1 */
        /* Insere ponto lido na lista de pontos */
        inserePonto(ponto, lista);

        i++;
        getline(&buffer, &bufsize, file); /* Pulando pra proxima linha */
    }

    double totalDeDemandas = 0;
    i = 0;
    while(i < n_genes) { /* Leitura das demandas de cada cidade */
        getline(&buffer, &bufsize, file); /* Pulando pra proxima linha */

        token = strtok(buffer, r);  /* Separa os dados da string */
        double nomePonto = converteNumero(token);

        token = strtok(NULL, r);  /* Separa os dados da string. Recebe NULL para continuar de onde parou */
        double demandaCidade = converteNumero(token);

        /* Insere demanda no ponto correspondente */
        insereDemanda(procurandoPonto(nomePonto-1, lista), demandaCidade);
        totalDeDemandas+= demandaCidade;
        i++;
    }

    /* Verifica se a soma de todas as demandas ultrapassa a capacidade de cada veídulo * num de veículos */
    verificaTotalDeDemanda(totalDeDemandas, k_rotas, capacidade);

    /* Lendo até o final */
    while(getline(&buffer, &bufsize, file) != -1){

    }

    /* Colocando no grafo as informação recolhidas */
    inicializaGrafo(grafo, k_rotas, n_genes, capacidade, totalDeDemandas);

    /* Dando um fim no buffer */
    free(buffer);

    /* Dando um fim na leitura do arquivo */
    fclose(file);
}

double converteNumero (char * token){
    /* Converte número de char * para double */
    double numero = atof(token);
    return numero;
}

void verificaTotalDeDemanda(double totalDeDemandas, int quantVeiculos, double capacidadeVeiculos){
    if(totalDeDemandas > quantVeiculos * capacidadeVeiculos){
        printf("Não existe conjunto de rotas possível que atenda à dedmanda de todas as cidades\n");
        exit(1);
    }
}