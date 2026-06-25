#ifndef FILA_H
#define FILA_H

#include "atendimento.h"

// ============================================================
//  TAD Fila Dinâmica — controla a ordem de atendimento
//  Implementação: lista encadeada simples com ponteiros
//  de início (frente) e fim (cauda).
// ============================================================

typedef struct NoFila {
    Atendimento dado;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *frente;
    NoFila *cauda;
    int tamanho;
} Fila;

// Inicializa a fila (deve ser chamada antes de qualquer uso).
void fila_inicializar(Fila *f);

// Retorna 1 se a fila estiver vazia, 0 caso contrário.
int fila_vazia(const Fila *f);

// Insere um atendimento no final da fila.
void fila_enqueue(Fila *f, Atendimento a);

// Remove e retorna o atendimento da frente da fila.
// ATENÇÃO: verificar fila_vazia() antes de chamar.
Atendimento fila_dequeue(Fila *f);

// Consulta o atendimento da frente sem remover.
Atendimento fila_frente(const Fila *f);

// Lista todos os atendimentos da fila sem removê-los.
void fila_listar(const Fila *f);

// Libera toda a memória alocada pela fila.
void fila_destruir(Fila *f);

#endif // FILA_H
