#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// ============================================================
//  Ordenação do histórico (Lista Encadeada)
//  Algoritmo: Insertion Sort — eficiente para listas pequenas
//  e adequado para listas encadeadas (sem acesso aleatório).
// ============================================================

// Ordena o histórico por prioridade (maior prioridade primeiro).
void ordenar_por_prioridade(Lista *l);

// Ordena o histórico por tempo estimado (menor tempo primeiro).
void ordenar_por_tempo(Lista *l);

#endif // ORDENACAO_H
