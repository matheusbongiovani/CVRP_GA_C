#include "vetorPontos.h"

struct vetorPontos{
    Ponto* ponto;
    int tam;
};

vetorPontos* inicializaVetorPonto(){
    // Aloca a lista de pontos 
    vetorPontos* pontosEntrada = (vetorPontos*)malloc(sizeof(vetorPontos));
    

    return pontosEntrada;
}

int tamanhoLista(vetorPontos* vet){
    return vet->tam;
}


void appendPonto(Ponto* p, vetorPontos* vet){

    vet->tam++;

}


// parar de usar ess função 'insereDepotAantesPos' ...
void insereDepotAantesPos(int i, Ponto* novoP, ListaPonto* lista){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->ponto = novoP;
    nova->prox = NULL;
    Celula* p = lista->prim;


    lista->tam++;    
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
    lista->tam--;
    Celula* celDepot = lista->prim;
    Ponto* depot = celDepot->ponto;

    lista->prim = celDepot->prox;

    free(celDepot);

    return depot;
}

void removePontoNaPos(int i, ListaPonto* lista){
    Celula* ant = NULL;
    Celula* p = lista->prim;
    lista->tam--;

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
    lista->tam--;

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
            lista->tam--;
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
        }
    }
}

ListaPonto* duplicarLista(ListaPonto* entrada){
    ListaPonto* duplicada = inicializaListaPonto();
    Celula* p;
    Celula* t;
    p = entrada->prim;

    while(p!=NULL){
        t = p->prox;
        appendPonto(p->ponto,duplicada);
        p = t;
    }

    return duplicada;
}

void imprimeListaPonto(ListaPonto* lista){
    Celula* p;
    Celula* t;
    p = lista->prim;
    int len = 0;
    printf("[ ");
    while(p!=NULL){
        t = p->prox;
        printf("%d, ",retornId(p->ponto));
        p = t;
        
        len++;
    }
    // printf("]\n");
    printf("] len:%d \n",len);
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
    removeDepositosDaLista(solucao);
    int N = solucao->tam;
    // int* cidades = (int*)malloc(sizeof(int)*N);
    int cidades[N]; // Vetor de cidades de 0 a 31 (para o primeiro exemplo, sendo 0 o depot)
    int i;
    for(i = 0; i < N ; i++){
        cidades[i] = i+1; // De 1 a nCidades-1(==31)
    }

    for (i = 0; i < N-1; ++i){
        int j = rand() % N;
        int temp = cidades[i];
        cidades[i] = cidades[j];
        cidades[j] = temp;
    }

    Celula* p = solucao->prim;
    solucao->ult->ponto = procuraPontoPeloId(cidades[N-1],entrada);
    Celula* t;
    for (i = 0; i < N; ++i){
        t = p->prox;
        Ponto* ponto = procuraPontoPeloId(cidades[i],entrada);
        p->ponto = ponto;
        p = t;
    }

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
    for(i=cut1; i<=cut2; i++){
        Ponto* ponto = procuraPontoPeloId(toReverse[j],entrada);
        p->ponto = ponto;
        p = p->prox;
        j++;
    }

}

void aplicarCrossover(ListaPonto* lp1, ListaPonto* lp2,  int cut1, int cut2, ListaPonto* entrada){
    // Gera gera filhos por trecho dos pais. Cortes representados por '/'
    // f1 =  p1/p2/p1 ; f2 = p2/p1/p2 
    int N1 = lp1->tam;
    int N2 = lp2->tam;

    
    int elem1[N1];
    int elem2[N2];
    int entreCuts1[(cut2-cut1)+1];
    int entreCuts2[(cut2-cut1)+1];
    int i, j;
    for(i = 0; i < N1 ; i++){
        elem1[i] = retornId(retornaPontoPosicaoNaLista(i,lp1)); // De 1 a nCidades-1(==31)
    }
    for(i = 0; i < N2 ; i++){
        elem2[i] = retornId(retornaPontoPosicaoNaLista(i,lp2)); // De 1 a nCidades-1(==31)
    }

    j = 0;
    for(i=cut1; i<=cut2;i++){
        entreCuts1[j] = elem1[i];
        j++;
    }
    j = 0;
    for(i=cut1; i<=cut2;i++){
        entreCuts2[j] = elem2[i];
        j++;
    }

    Celula* cp1 = lp1->prim;
    j = 0;
    // pular elementos da lista até chegar no trecho para cortar()
    for(i = 0; i < cut1; cp1 = cp1->prox){
        i++;
    }
    for(i=cut1; i<=cut2; i++){
        Ponto* ponto = procuraPontoPeloId(entreCuts2[j],entrada);
        if(cp1->ponto == NULL){
            appendPonto(ponto,lp1);
        }else{
            cp1->ponto = ponto;
            cp1 = cp1->prox;
            j++;
        }
    }


    Celula* cp2 = lp2->prim;
    j = 0;
    for(i = 0; i < cut1; cp2 = cp2->prox){
        i++;
    }
    for(i=cut1; i<=cut2; i++){
        Ponto* ponto = procuraPontoPeloId(entreCuts1[j],entrada);
        if(cp2->ponto == NULL){
            appendPonto(ponto,lp2);
        }else{
            cp2->ponto = ponto;
            cp2 = cp2->prox;
            j++;
        }
    }
}

void removerZerosDoLado(ListaPonto* solucao){
    Celula* p = solucao->prim;
    Celula* next;

    while(p!=NULL){
        next = p->prox;
        if(next!=NULL && retornId(p->ponto) == 0 && retornId(next->ponto)== 0){
            solucao->tam--;
            p->prox = next->prox;
            free(next);
            continue;
        }
        p = p->prox;
    }
}