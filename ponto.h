#ifndef PONTO_H
#define PONTO_H
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ponto Ponto;

void recebeCoordenadas (double coord1, double coord2, Ponto * ponto);
Ponto* criaPonto(int id, double x, double y);
double retornId(Ponto * p);
void insereDemanda(Ponto * ponto, double demand);

double retornaDemanda(Ponto * ponto);
double distanciaEntrePontos(Ponto* ponto1, Ponto* ponto2);

void destroiPonto (Ponto * p);

#endif // PONTO_H
