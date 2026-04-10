#ifndef ESTRUTURA_H
#define ESTRUTURA_H

/* ============================================================
 * estrutura.h
 * Contrato do TAD Fila (Queue) para gerenciamento de
 * requisicoes de atendimento — logica FIFO.
 *
 * Estrategia de implementacao:
 *   Lista encadeada com ponteiros para o INICIO (head) e
 *   para o FIM (tail) da fila.
 *
 *   - Insercao no tail  → O(1)  sem percorrer a lista
 *   - Remocao no head   → O(1)  sem percorrer a lista
 *   - Consulta de tamanho → O(1) campo mantido atualizado
 * ============================================================ */

#include "requisicao.h"

/* ---- No interno da lista encadeada ---- */
typedef struct No {
    Requisicao    dado;   /* Copia da requisicao armazenada neste no  */
    struct No    *prox;   /* Ponteiro para o proximo no da fila        */
} No;

/* ---- TAD Fila ---- */
typedef struct {
    No  *head;    /* Ponteiro para o inicio da fila (proximo a sair)  */
    No  *tail;    /* Ponteiro para o fim da fila   (ultimo inserido)  */
    int  tamanho; /* Numero de requisicoes atualmente na fila         */
} Fila;

/* ================================================================
 * Assinaturas das funcoes publicas do TAD
 * ================================================================ */

/**
 * Inicializa uma fila vazia.
 * Deve ser chamada antes de qualquer outra operacao.
 * Complexidade: O(1)
 */
void fila_inicializar(Fila *f);

/**
 * Insere uma requisicao no fim da fila (enqueue).
 * Retorna 1 em sucesso, 0 em caso de falha de alocacao.
 * Complexidade: O(1)
 */
int fila_inserir(Fila *f, Requisicao req);

/**
 * Remove a requisicao do inicio da fila (dequeue).
 * Armazena os dados removidos em *removida (se nao NULL).
 * Retorna 1 em sucesso, 0 se a fila estiver vazia.
 * Complexidade: O(1)
 */
int fila_remover(Fila *f, Requisicao *removida);

/**
 * Retorna o numero de requisicoes na fila.
 * Complexidade: O(1)
 */
int fila_tamanho(const Fila *f);

/**
 * Verifica se a fila esta vazia.
 * Retorna 1 se vazia, 0 caso contrario.
 * Complexidade: O(1)
 */
int fila_vazia(const Fila *f);

/**
 * Libera toda a memoria alocada pelos nos da fila.
 * Apos a chamada, a fila fica no estado inicializado (vazia).
 * Complexidade: O(n)
 */
void fila_destruir(Fila *f);

/**
 * Exibe todos os elementos da fila sem remove-los (para debug).
 * Complexidade: O(n)
 */
void fila_exibir(const Fila *f);

#endif /* ESTRUTURA_H */
