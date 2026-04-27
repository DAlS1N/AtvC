#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

/* ================================================================
 * SA1 – pt.2  |  Implementacao do TAD Lista Duplamente Encadeada
 * ================================================================ */

/* ----------------------------------------------------------------
 * Auxiliar interno: aloca e inicializa um novo No.
 * Retorna o ponteiro ou NULL em falha de alocacao.
 * ---------------------------------------------------------------- */
static No *criar_no(Requisicao req)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] criar_no: falha ao alocar memoria.\n");
        return NULL;
    }
    novo->dado = req;   /* Copia por valor */
    novo->prev = NULL;
    novo->next = NULL;
    return novo;
}

/* ----------------------------------------------------------
 * lista_inicializar
 * Prepara a struct Lista para uso, zerando todos os campos.
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
void lista_inicializar(Lista *l)
{
    if (l == NULL) return;
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

/* ----------------------------------------------------------
 * inserir_emergencia  —  insercao no HEAD  O(1)
 *
 * Caso 1: lista vazia  → novo no e o unico (head e tail).
 * Caso 2: lista nao vazia:
 *   novo->next  = head atual
 *   head->prev  = novo          ← religamento do elo "para tras"
 *   head        = novo          ← atualiza o ponteiro gerenciador
 *
 * Retorno: 1 = sucesso | 0 = falha de alocacao
 * ---------------------------------------------------------- */
int inserir_emergencia(Lista *l, Requisicao req)
{
    if (l == NULL) return 0;

    No *novo = criar_no(req);
    if (novo == NULL) return 0;

    if (lista_vazia(l)) {
        l->head = novo;
        l->tail = novo;
    } else {
        /* Dança dos ponteiros – insercao no inicio */
        novo->next       = l->head; /* 1. novo aponta para o atual head */
        l->head->prev    = novo;    /* 2. atual head olha para tras      */
        l->head          = novo;    /* 3. head gerenciador avanca        */
        /* novo->prev ja e NULL (inicializado em criar_no)               */
    }

    l->size++;
    return 1;
}

/* ----------------------------------------------------------
 * inserir_triagem  —  insercao no TAIL  O(1)
 *
 * Caso 1: lista vazia  → novo no e o unico (head e tail).
 * Caso 2: lista nao vazia:
 *   tail->next  = novo          ← encadeia apos o atual tail
 *   novo->prev  = tail          ← novo olha para seu predecessor
 *   tail        = novo          ← atualiza o ponteiro gerenciador
 *
 * Retorno: 1 = sucesso | 0 = falha de alocacao
 * ---------------------------------------------------------- */
int inserir_triagem(Lista *l, Requisicao req)
{
    if (l == NULL) return 0;

    No *novo = criar_no(req);
    if (novo == NULL) return 0;

    if (lista_vazia(l)) {
        l->head = novo;
        l->tail = novo;
    } else {
        /* Dança dos ponteiros – insercao no final */
        l->tail->next = novo;   /* 1. tail atual aponta para o novo     */
        novo->prev    = l->tail;/* 2. novo olha para tras               */
        l->tail       = novo;   /* 3. tail gerenciador avanca           */
        /* novo->next ja e NULL (inicializado em criar_no)               */
    }

    l->size++;
    return 1;
}

/* ----------------------------------------------------------
 * atender_paciente  —  remocao do HEAD  O(1)
 *
 * Remove o no de maior prioridade (head).
 * Apos remocao, o novo head perde seu elo "para tras" (prev=NULL).
 *
 * Retorno: 1 = sucesso | 0 = lista vazia
 * ---------------------------------------------------------- */
int atender_paciente(Lista *l, Requisicao *atendido)
{
    if (l == NULL || lista_vazia(l)) {
        fprintf(stderr, "[AVISO] atender_paciente: lista vazia.\n");
        return 0;
    }

    No *saindo = l->head;

    if (atendido != NULL) {
        *atendido = saindo->dado;   /* Entrega dados ao chamador */
    }

    l->head = saindo->next;         /* Avanca o head */

    if (l->head != NULL) {
        l->head->prev = NULL;       /* Novo head nao tem predecessor */
    } else {
        l->tail = NULL;             /* Lista ficou vazia: tail tbm nulo */
    }

    free(saindo);
    l->size--;
    return 1;
}

/* ----------------------------------------------------------
 * remover_paciente_id  —  remocao em posicao arbitraria  O(n)
 *
 * Percorre a lista buscando o no com codigo_inscricao == id.
 * Ao encontrar, executa a "Danca dos 4 Ponteiros":
 *
 *   anterior->next = alvo->next   (1)
 *   proximo->prev  = alvo->prev   (2)
 *
 * Casos especiais (head / tail) sao tratados explicitamente.
 *
 * Retorno: 1 = sucesso | 0 = ID nao encontrado
 * ---------------------------------------------------------- */
int remover_paciente_id(Lista *l, int id, Requisicao *removido)
{
    if (l == NULL || lista_vazia(l)) {
        fprintf(stderr, "[AVISO] remover_paciente_id: lista vazia.\n");
        return 0;
    }

    /* --- Busca linear pelo ID --- */
    No *alvo = l->head;
    while (alvo != NULL && alvo->dado.codigo_inscricao != id) {
        alvo = alvo->next;
    }

    if (alvo == NULL) {
        fprintf(stderr, "[AVISO] remover_paciente_id: ID %d nao encontrado.\n", id);
        return 0;
    }

    /* --- Entrega os dados antes de liberar --- */
    if (removido != NULL) {
        *removido = alvo->dado;
    }

    /* =========================================================
     * DANÇA DOS 4 PONTEIROS
     * ---------------------------------------------------------
     * Temos tres situacoes possiveis:
     *
     *   A) alvo e o HEAD (sem predecessor)
     *   B) alvo e o TAIL (sem sucessor)
     *   C) alvo esta no MEIO (tem predecessor E sucessor)
     *
     * Em todos os casos garantimos que:
     *   1. O predecessor passa a apontar para o sucessor de alvo
     *   2. O sucessor passa a apontar para o predecessor de alvo
     * ========================================================= */

    /* Ponteiro 1: religamento do predecessor */
    if (alvo->prev != NULL) {
        alvo->prev->next = alvo->next;  /* P1: anterior salta sobre alvo */
    } else {
        /* alvo era o HEAD: o proximo se torna o novo head */
        l->head = alvo->next;
    }

    /* Ponteiro 2: religamento do sucessor */
    if (alvo->next != NULL) {
        alvo->next->prev = alvo->prev;  /* P2: proximo olha para o anterior */
    } else {
        /* alvo era o TAIL: o anterior se torna o novo tail */
        l->tail = alvo->prev;
    }

    free(alvo);
    l->size--;
    return 1;
}

/* ----------------------------------------------------------
 * imprimir_auditoria
 * Percorre HEAD → TAIL e depois TAIL → HEAD,
 * provando a navegacao bidirecional completa.
 * Complexidade: O(n)
 * ---------------------------------------------------------- */
void imprimir_auditoria(const Lista *l)
{
    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║          RELATORIO DE AUDITORIA DA FILA          ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");

    if (l == NULL || lista_vazia(l)) {
        printf("║        [Nenhuma requisicao aguardando]           ║\n");
        printf("╚══════════════════════════════════════════════════╝\n\n");
        return;
    }

    printf("║  Pacientes em espera: %-27d║\n", l->size);

    /* ---------- Passagem DIRETA: HEAD → TAIL ---------- */
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  ▶  LEITURA DIRETA  (HEAD → TAIL)                ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");

    const No *atual = l->head;
    int posicao = 1;
    while (atual != NULL) {
        printf("║  [%02d] Paciente  : %-29s║\n",
               posicao, atual->dado.nome_paciente);
        printf("║       Inscricao : %-4d  Proc.: %-14s║\n",
               atual->dado.codigo_inscricao,
               atual->dado.codigo_procedimento);
        if (atual->next != NULL) {
            printf("║       ↓                                          ║\n");
        }
        posicao++;
        atual = atual->next;
    }

    /* ---------- Passagem REVERSA: TAIL → HEAD ---------- */
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  ◀  LEITURA REVERSA (TAIL → HEAD)                ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");

    atual = l->tail;
    posicao = l->size;
    while (atual != NULL) {
        printf("║  [%02d] Paciente  : %-29s║\n",
               posicao, atual->dado.nome_paciente);
        printf("║       Inscricao : %-4d  Proc.: %-14s║\n",
               atual->dado.codigo_inscricao,
               atual->dado.codigo_procedimento);
        if (atual->prev != NULL) {
            printf("║       ↑                                          ║\n");
        }
        posicao--;
        atual = atual->prev;
    }

    printf("╚══════════════════════════════════════════════════╝\n\n");
}

/* ----------------------------------------------------------
 * lista_tamanho  –  O(1)
 * ---------------------------------------------------------- */
int lista_tamanho(const Lista *l)
{
    if (l == NULL) return 0;
    return l->size;
}

/* ----------------------------------------------------------
 * lista_vazia  –  O(1)
 * ---------------------------------------------------------- */
int lista_vazia(const Lista *l)
{
    if (l == NULL) return 1;
    return (l->size == 0);
}

/* ----------------------------------------------------------
 * lista_destruir  –  O(n)
 * Percorre e libera todos os nos, reinicia os campos.
 * ---------------------------------------------------------- */
void lista_destruir(Lista *l)
{
    if (l == NULL) return;

    No *atual = l->head;
    while (atual != NULL) {
        No *proximo = atual->next;
        free(atual);
        atual = proximo;
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}
