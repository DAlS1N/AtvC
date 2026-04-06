#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

//TAD Geométrico (.c): Implemente o arquivo ponto.c realizando as alocações e cálculos necessários para o TAD anterior.

struct ponto {
    float x;
    float y;
};

Ponto* ponto_criar(float x, float y) {
    Ponto* p = (Ponto*) malloc(sizeof(Ponto));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

float ponto_distancia(Ponto* p1, Ponto* p2) {
    if (p1 == NULL || p2 == NULL) return -1.0; 

    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    return sqrt(dx * dx + dy * dy);
}


void ponto_destruir(Ponto* p) {
    if (p != NULL) {
        free(p);
    }
}