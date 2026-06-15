#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include "atendimento.h"

// ============================================================
//  TAD Lista Encadeada — histórico de atendimentos
//  Cada nó guarda um Atendimento e um ponteiro para o próximo.
// ============================================================

typedef struct NoLista {
    Atendimento dado;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *cabeca;
    int tamanho;
} Lista;

// Inicializa a lista.
void lista_inicializar(Lista *l);

// Retorna 1 se vazia, 0 caso contrário.
int lista_vazia(const Lista *l);

// Insere um atendimento no final da lista.
void lista_inserir(Lista *l, Atendimento a);

// Atualiza o status de um atendimento pelo id.
// Retorna 1 se encontrou e atualizou, 0 caso contrário.
int lista_atualizar_status(Lista *l, int id, const char *novo_status);

// Lista todos os atendimentos do histórico.
void lista_listar(const Lista *l);

// Busca sequencial por nome do cliente (parcial ou total).
// Imprime todos os resultados encontrados.
void lista_buscar_por_cliente(const Lista *l, const char *nome);

// Busca sequencial por prioridade.
void lista_buscar_por_prioridade(const Lista *l, int prioridade);

// Libera toda a memória da lista.
void lista_destruir(Lista *l);

#endif // LISTA_H
