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
    ListaPonto* lista = (ListaPonto*)malloc(sizeof(ListaPonto));
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
    Celula* nova = (Celula*)malloc(sizeof(Celula));

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

void insereDepotAantesPos(int i, Ponto* novoP, ListaPonto* lista){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->ponto = novoP;
    nova->prox = NULL;
    Celula* p = lista->prim;

    int j; // j=1 para p->prox apontar para nova, e nova estar na pos(i)
    for(j=1; p!=NULL; p=p->prox){
        if(j==i){
            nova->prox = p->prox;
            p->prox = nova;
            break;
        }
        j++;
    }

}

Ponto* extractDepotDaLista(ListaPonto* lista){
    Celula* celDepot = lista->prim;
    Ponto* depot = celDepot->ponto;

    lista->prim = celDepot->prox;

    free(celDepot);

    return depot;
}

void removePontoNaPos(int i, ListaPonto* lista){
    Celula* ant = NULL;
    Celula* p = lista->prim;
    int j = 0;

    while(p!=NULL && j!=i){   
        ant = p;
        p = p->prox;
    }
    if(p==NULL)
        return;
    if(p==lista->prim && p==lista->ult){
        lista->prim = lista->ult = NULL;
        free(p);
        return;
    }
    if(p==lista->ult){
        lista->ult = ant;
        ant->prox = NULL;
        free(p);
        return;
    }
    if(p==lista->prim)
        lista->prim = p->prox;
    else
        ant->prox = p->prox;
    
    free(p);

}

void removePontoPeloId(int id, ListaPonto* lista){
    Celula* ant = NULL;
    Celula* p = lista->prim;

    while(p!=NULL && retornId(p->ponto) != id){   
        ant = p;
        p = p->prox;
    }
    if(p==NULL)
        return;
    if(p==lista->prim && p==lista->ult){
        lista->prim = lista->ult = NULL;
        free(p);
        return;
    }
    if(p==lista->ult){
        lista->ult = ant;
        ant->prox = NULL;
        free(p);
        return;
    }
    if(p==lista->prim)
        lista->prim = p->prox;
    else
        ant->prox = p->prox;
    
    free(p);

}

void removeDepositosDaLista(ListaPonto* lista){
    Celula* next = NULL;
    Celula* p = lista->prim;

    while(p!=NULL){
        next = p->prox;
        if(retornId(p->ponto) == 0){
            removePontoPeloId(0,lista);
            p = next;
        }else
            p = p->prox;
    }
}

Ponto* procuraPontoPeloId(int id, ListaPonto* lista){
    Celula* p = lista->prim;
    for(p = lista->prim; p!=NULL; p=p->prox){
        if(retornId(p->ponto) == id){
            return p->ponto;
        }
    }
    return NULL;
}


Ponto* retornaPontoPosicaoNaLista(int i, ListaPonto* lista){
    Celula* p = lista->prim;
    int j;
    for(j = 0; p!=NULL; p=p->prox){
        if(i==j){
            return p->ponto;
        }
        j++;
    }
    return NULL;
}

void atualizarPontoAtPos(int i, Ponto* novo ,ListaPonto* lista){
    Celula* p = lista->prim;
    int j;
    for(j = 0; p!=NULL; p=p->prox){
        if(i==j){
            p->ponto = novo;
        }
        j++;
    }
}


void distanciaPontos(ListaPonto* lista, double** matriz, int numCidades){
    int i, j;
    double dist = 0;
    // Matrix quadrada contendo distância entre todas as cidades
    for(i = 0; i < numCidades ; i++){
        for(j = 0; j < numCidades; j++){
            // Calcula a distância entre os pontos 
            dist = distanciaEntrePontos(procuraPontoPeloId(i, lista), procuraPontoPeloId(j, lista));
            matriz[i][j] = dist;
            // printf("%.1f ", dist);
        }
        // printf("\n");
    }
}

ListaPonto* duplicarLista(ListaPonto* entrada){
    ListaPonto* duplicada = inicializaListaPonto();
    Celula* p;
    Celula* t;
    p = entrada->prim;

    int i = 0;
    while(p!=NULL){
        t = p->prox;
        appendPonto(p->ponto,duplicada);
        p = t;
        i++;
    }

    return duplicada;
}

void imprimeListaPonto(ListaPonto* lista){
    Celula* p;
    Celula* t;
    p = lista->prim;
    

    while(p!=NULL){
        t = p->prox;
        printf("%d ",retornId(p->ponto));
        p = t;
    }
    printf("\n");
}


void destroiListaDuplicada(ListaPonto* lista){
    Celula* p;
    Celula* t;
    p = lista->prim;

    while(p!=NULL){
        t = p->prox;
        free(p);
        p = t;
    }
    free(lista);
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


// shuffleListaPonto() recebe a lista com o depot incluso da entrada, e retorna as cidades randomizadas (sem depot).
ListaPonto* shuffleListaPonto(ListaPonto* entrada){
    ListaPonto* solucao = duplicarLista(entrada);
    extractDepotDaLista(solucao);
    int N = tamanhoLista(entrada)-1;
    int cidades[N]; // Vetor de cidades de 0 a 31 (para o primeiro exemplo, sendo 0 o depot)
    int i;
    for(i = 0; i < N ; i++){
        cidades[i] = i+1; // De 1 a nCidades-1(==31)
    }

    // ----------- r random beteween 1 ~ N
    // int r= rand()% N;
    // r++;
    // printf("%d ",r);
    for (i = 0; i < N-1; ++i){
        int j = rand() % (N-i) + i;
        int temp = cidades[i];
        cidades[i] = cidades[j];
        cidades[j] = temp;
    }
    // for (i = 0; i < N; i++)
    //     printf("%d ", cidades[i]);
    // printf("\n");

    Celula* p = solucao->prim;
    solucao->ult->ponto = procuraPontoPeloId(cidades[N-1],entrada);
    Celula* t;
    for (i = 0; i < N; ++i){
        t = p->prox;
        Ponto* ponto = procuraPontoPeloId(cidades[i],entrada);
        p->ponto = ponto;
        p = t;
    }
    // imprimeListaPonto(solucao);

    return solucao;
}

void reverseEntreCuts(ListaPonto* solucao, int cut1, int cut2, ListaPonto* entrada){
    int N = tamanhoLista(solucao);
    int elem[N];
    int toReverse[(cut2-cut1)+1];
    int i;
    for(i = 0; i < N ; i++){
        elem[i] = retornId(retornaPontoPosicaoNaLista(i,solucao)); // De 1 a nCidades-1(==31)
    }

    int j = 0;
    for(i=cut2; i>=cut1;i--){
        toReverse[j] = elem[i];
        // printf("%d ", toReverse[j]);
        j++;
    }
    Celula* p = solucao->prim;
    // pular elementos da lista até chegar no trecho para reverse()
    for(i = 0; i < cut1;p = p->prox){
        i++;
    }
    j = 0;
    // imprimeListaPonto(solucao);
    for(i=cut1; i<=cut2; i++){
        Ponto* ponto = procuraPontoPeloId(toReverse[j],entrada);
        p->ponto = ponto;
        p = p->prox;
        j++;
    }

    // imprimeListaPonto(solucao);
}
