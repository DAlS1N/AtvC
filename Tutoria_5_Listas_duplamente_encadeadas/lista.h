#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

/* -------------------------------------------------------
   Exercicio 2 — Estrutura base da lista
   ------------------------------------------------------- */
typedef struct {
    Nodo *inicio;
    Nodo *fim;
    int   tamanho;
} Lista;

Lista* criar_lista(void);
int    esta_vazia(Lista *lista);
int    tamanho_lista(Lista *lista);   /* 'tamanho' seria conflito com campo */
void   destruir_lista(Lista *lista);

/* -------------------------------------------------------
   Exercicio 3 — Inserção no início
   Retorna 1 em sucesso, 0 em falha.
   ------------------------------------------------------- */
int inserir_inicio(Lista *lista, int valor);

/* -------------------------------------------------------
   Exercicio 4 — Inserção no fim
   Retorna 1 em sucesso, 0 em falha.
   ------------------------------------------------------- */
int inserir_fim(Lista *lista, int valor);

/* -------------------------------------------------------
   Exercicio 5 — Impressão bidirecional
   ------------------------------------------------------- */
void imprimir_inicio_fim(Lista *lista);
void imprimir_fim_inicio(Lista *lista);

/* -------------------------------------------------------
   Exercicio 6 — Remoção do início
   Retorna 1 em sucesso, 0 se lista vazia.
   O valor removido é escrito em *valor_removido.
   ------------------------------------------------------- */
int remover_inicio(Lista *lista, int *valor_removido);

/* -------------------------------------------------------
   Exercicio 7 — Remoção do fim
   Retorna 1 em sucesso, 0 se lista vazia.
   ------------------------------------------------------- */
int remover_fim(Lista *lista, int *valor_removido);

/* -------------------------------------------------------
   Exercicio 8 — Busca por valor
   Retorna ponteiro para o nodo ou NULL.
   ------------------------------------------------------- */
Nodo* buscar(Lista *lista, int valor);

/* -------------------------------------------------------
   Exercicio 9 — Inserção em posição específica
   Posição 0 = início; posição == tamanho = fim.
   Retorna 1 em sucesso, 0 em falha/posição inválida.
   ------------------------------------------------------- */
int inserir_posicao(Lista *lista, int valor, int posicao);

/* -------------------------------------------------------
   Exercicio 10 — Remoção por valor
   Remove a primeira ocorrência.
   Retorna 1 em sucesso, 0 se não encontrado.
   ------------------------------------------------------- */
int remover_valor(Lista *lista, int valor);

#endif
