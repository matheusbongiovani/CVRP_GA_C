#ifndef LISTAPONTOS_H
#define LISTAPONTOS_H
#include <stdio.h>
#include "ponto.h"

typedef struct listaPonto ListaPonto;
typedef struct celula Celula;
ListaPonto* inicializaListaPonto();
int tamanhoLista(ListaPonto* lista);
void appendPonto(Ponto* p, ListaPonto* lista);
Ponto* extractDepot(ListaPonto* lista);
Ponto* procurandoPonto(int id, ListaPonto* lista);
Ponto* retornaPontoPosicaoNaLista(int i,ListaPonto* lista);


ListaPonto* duplicarLista(ListaPonto* entrada);
void distanciaPontos(ListaPonto* lista, double** matriz, int numCidades);
void destroiLista(ListaPonto* lista);

#endif // LISTAPONTOS_H