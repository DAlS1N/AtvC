#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include "requisicao.h"

/* ================================================================
 * SA1 – pt.2  |  Motor de Triagem com Lista Duplamente Encadeada
 * ================================================================
 *
 * Evolucao da SA1 pt.1:
 *   - No agora possui dois elos: *prev e *next (lista bidirecional)
 *   - Fila renomeada para Lista (semantica mais precisa)
 *   - Contador rebatizado de tamanho -> size (padrao internacional)
 *   - Novas operacoes: emergencia, remocao por ID, auditoria
 * ================================================================ */

/* ----------------------------------------------------------------
 * No  –  celula da lista duplamente encadeada
 * ---------------------------------------------------------------- */
typedef struct No {
    Requisicao  dado;   /* Copia da requisicao armazenada no no      */
    struct No  *prev;   /* Elo com o passado  (no anterior)          */
    struct No  *next;   /* Elo com o futuro   (proximo no)           */
} No;

/* ----------------------------------------------------------------
 * Lista  –  estrutura gerenciadora
 * ---------------------------------------------------------------- */
typedef struct {
    No  *head;  /* Inicio da lista – proximo a ser atendido          */
    No  *tail;  /* Fim da lista   – ultimo a chegar                  */
    int  size;  /* Quantidade de nos atualmente na lista             */
} Lista;

/* ================================================================
 * Interface publica do TAD
 * ================================================================ */

/**
 * Inicializa a lista, zerando todos os campos.
 * Deve ser chamada antes de qualquer outra operacao.
 * Complexidade: O(1)
 */
void lista_inicializar(Lista *l);

/**
 * Insere paciente de ALTA PRIORIDADE diretamente no HEAD.
 * Usado em casos de emergencia — paciente atendido imediatamente.
 * Retorna 1 em sucesso, 0 em falha de alocacao.
 * Complexidade: O(1)
 */
int inserir_emergencia(Lista *l, Requisicao req);

/**
 * Insere paciente de prioridade normal no TAIL (ordem FIFO).
 * Fluxo padrao de triagem.
 * Retorna 1 em sucesso, 0 em falha de alocacao.
 * Complexidade: O(1)
 */
int inserir_triagem(Lista *l, Requisicao req);

/**
 * Remove e entrega o paciente no HEAD (proximo da fila).
 * Armazena os dados em *atendido se o ponteiro nao for NULL.
 * Retorna 1 em sucesso, 0 se a lista estiver vazia.
 * Complexidade: O(1)
 */
int atender_paciente(Lista *l, Requisicao *atendido);

/**
 * Localiza e remove o paciente cujo codigo_inscricao == id,
 * independentemente de sua posicao (head, meio ou tail).
 * Executa a "Danca dos 4 Ponteiros" para religamento seguro.
 * Armazena os dados em *removido se o ponteiro nao for NULL.
 * Retorna 1 em sucesso, 0 se o ID nao for encontrado.
 * Complexidade: O(n)
 */
int remover_paciente_id(Lista *l, int id, Requisicao *removido);

/**
 * Imprime a fila do HEAD ao TAIL e, em seguida, do TAIL ao HEAD,
 * provando a navegacao bidirecional da lista.
 * Complexidade: O(n)
 */
void imprimir_auditoria(const Lista *l);

/**
 * Retorna o numero de pacientes na lista.
 * Complexidade: O(1)
 */
int lista_tamanho(const Lista *l);

/**
 * Retorna 1 se a lista estiver vazia, 0 caso contrario.
 * Complexidade: O(1)
 */
int lista_vazia(const Lista *l);

/**
 * Libera toda a memoria alocada.
 * Apos a chamada, a lista fica no estado inicializado (vazia).
 * Complexidade: O(n)
 */
void lista_destruir(Lista *l);

#endif /* ESTRUTURA_H */
