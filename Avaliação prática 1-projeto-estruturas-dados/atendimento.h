#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include <stdio.h>
#include <stdlib.h>

// ============================================================
//  TAD Atendimento — definição da estrutura principal
// ============================================================

typedef struct {
    int id;
    char cliente[50];
    char categoria[30];
    int prioridade;       // 1 = baixa, 2 = média, 3 = alta
    int tempo_estimado;   // em minutos
    char status[20];      // "aberto", "atendido" ou "cancelado"
} Atendimento;

// Cria e retorna um novo Atendimento com os dados fornecidos.
// O status é definido automaticamente como "aberto".
Atendimento atendimento_criar(int id, const char *cliente, const char *categoria,
                               int prioridade, int tempo_estimado);

// Imprime os dados de um atendimento no terminal.
void atendimento_imprimir(const Atendimento *a);

// Converte inteiro de prioridade para string legível.
const char *atendimento_prioridade_str(int prioridade);

#endif // ATENDIMENTO_H
