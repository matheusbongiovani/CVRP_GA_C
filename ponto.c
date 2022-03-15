#include "ponto.h"

struct ponto{
    int id;
    double x;
    double y;
    double demand;
};

Ponto* criaPonto(int id, double x, double y){
    // Aloca novo ponto
    Ponto* novo = (Ponto*) malloc(sizeof(Ponto));
    novo->id = id;
    novo->x = x;
    novo->y = y;

    return novo;
}

void insereDemanda(Ponto * ponto, double demand){
    ponto->demand = demand;
};

int retornId(Ponto * p){
    if (p!= NULL)
        return p->id;
    return 9999;
}

double retornaDemanda(Ponto * ponto){
    return ponto->demand;
}

void recebeCoordenadas (double coord1, double coord2, Ponto * ponto){
    ponto->x = coord1;
    ponto->y = coord2;
}

double distanciaEntrePontos(Ponto* ponto1, Ponto* ponto2){
    double Totalsoma = 0, soma = 0;

    // Realiza o cálculo da distância euclidiana entre dois pontos
        soma = ponto1->x - ponto2->x;
        soma = soma * soma;
        Totalsoma += soma;

        soma = 0;
        soma = ponto1->y - ponto2->y;
        soma = soma * soma;
        Totalsoma += soma;

    Totalsoma = sqrt(Totalsoma);

    return Totalsoma;
}

void destroiPonto(Ponto * p){
    free(p);
}
