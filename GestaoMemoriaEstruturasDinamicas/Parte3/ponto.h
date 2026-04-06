#ifndef PONTO_H
#define PONTO_H

//TAD Geométrico (.h): Crie o arquivo ponto.h definindo a estrutura opaca e as assinaturas para criar, distancia e destruir

typedef struct ponto Ponto;

Ponto* ponto_criar(float x, float y);

float ponto_distancia(Ponto* p1, Ponto* p2);

void ponto_destruir(Ponto* p);

#endif 