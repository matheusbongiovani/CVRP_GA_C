#ifndef VNS_LISTAPONTOS_H
#define VNS_LISTAPONTOS_H
#include <stdio.h>
#include "ponto.h"

typedef struct listaPonto ListaPonto;
typedef struct aresta Aresta;
ListaPonto* inicializaListaPonto();
void inserePonto(Ponto* p, ListaPonto* lista);
Ponto * procurandoPonto(int id, ListaPonto * lista);
void distanciaPontos(ListaPonto* lista, double ** matriz, int numCidades);
void destroiLista(ListaPonto* lista);


#endif //VNS_LISTAPONTOS_H
