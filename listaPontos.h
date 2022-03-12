#ifndef LISTAPONTOS_H
#define LISTAPONTOS_H
#include <stdio.h>
#include "ponto.h"

typedef struct listaPonto ListaPonto;
typedef struct celula Celula;
ListaPonto* inicializaListaPonto();
int tamanhoLista(ListaPonto* lista);
void appendPonto(Ponto* p, ListaPonto* lista);
Ponto* tirar1elemDaLista(ListaPonto* lista);
void insereDepotAantesPos(int i, Ponto* novoP, ListaPonto* lista);
Ponto* procuraPontoPeloId(int id, ListaPonto* lista);
Ponto* retornaPontoPosicaoNaLista(int i,ListaPonto* lista);
void atualizarPontoAtPos(int i, Ponto* novo ,ListaPonto* lista);
void removePontoNaPos(int i, ListaPonto* lista);
void removePontoPeloId(int id, ListaPonto* lista);
void removeDepositosDaLista(ListaPonto* lista);
ListaPonto* duplicarLista(ListaPonto* entrada);
void distanciaPontos(ListaPonto* lista, double** matriz, int numCidades);
void destroiListaDuplicada(ListaPonto* lista);
void destroiLista(ListaPonto* lista);

#endif // LISTAPONTOS_H