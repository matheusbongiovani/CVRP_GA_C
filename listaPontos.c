#include "listaPontos.h"

typedef struct celula Celula;

struct celula{
    Ponto* ponto;
    Celula* prox;
};

struct listaPonto{
    Celula* prim;
    Celula* ult;
};

ListaPonto* inicializaListaPonto(){
    // Aloca a lista de pontos 
    ListaPonto* lista = (ListaPonto*)malloc(sizeof (ListaPonto));
    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

int tamanhoLista(ListaPonto* lista){
    int i = 0;
    Celula* p = lista->prim;
    while(p!=NULL){
        p = p->prox;
        i++;
    }
    return i;
}


void appendPonto(Ponto* p, ListaPonto* lista){
    // Insere ponto no fim da lista
    Celula* nova = (Celula*)malloc(sizeof (Celula));

    nova->ponto = p;
    nova->prox = NULL;

    // Inserção em caso de lista vazia
    if(lista->ult == NULL){
        lista->prim = lista->ult = nova;
    }
    else{ // Caso regular de inserção
        lista->ult->prox = nova;
        lista->ult = nova;
    }
}

Ponto* extractDepot(ListaPonto* lista){
    Celula* celDepot = lista->prim;
    Ponto* depot = celDepot->ponto;

    lista->prim = celDepot->prox;

    free(celDepot);

    return depot;
}

Ponto* procurandoPonto(int id, ListaPonto* lista){
    Celula* p = lista->prim;
    for(p = lista->prim; p!=NULL; p=p->prox){
        if(retornId(p->ponto) == id){
            return p->ponto;
        }
    }
    printf("Ponto %d nao encontrado\n", id);
}

Ponto* retornaPontoPosicaoNaLista(int i, ListaPonto* lista){
    Celula* p = lista->prim;
    int j;
    for(j = 0; p!=NULL; p=p->prox){
        if(j == i){
            return p->ponto;
        }
        j++;
    }
    printf("Sem Ponto na posicao %d\n", i);
}



void distanciaPontos(ListaPonto* lista, double** matriz, int numCidades){
    int i, j;
    double dist = 0;
    // Matrix quadrada contendo distância entre todas as cidades
    for(i = 0; i < numCidades ; i++){
        for(j = 0; j < numCidades; j++){
            // Calcula a distância entre os pontos 
            dist = distanciaEntrePontos(procurandoPonto(i, lista), procurandoPonto(j, lista));
            matriz[i][j] = dist;
            // printf("%.1f ", dist);
        }
        // printf("\n");
    }
}


void destroiLista(ListaPonto* lista){
    Celula* p;
    Celula* t;
    p = lista->prim;

    while(p!=NULL){
        t = p->prox;
        destroiPonto(p->ponto);
        free(p);
        p = t;
    }
    free(lista);
}
