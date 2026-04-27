/*
 * ============================================================
 * EXERCICIO 4 - A Danca dos Ponteiros (Insercao no Meio)
 * ============================================================
 *
 * Objetivo: inserir o no novo logo APOS o no atual
 *
 * REGRA DE OURO:
 *
 * "Ligue a rede do novo no antes de desconectar os antigos."
 *
 * Ou seja: primeiro conecte o novo, depois atualize os
 * vizinhos, nunca o contrario para nao perder referencias.
 *
 * As 4 linhas essenciais:
 *
 * 1. novo->next = atual->next;
 * 2. novo->previous = atual;
 * 3. atual->next->previous = novo;
 * 4. atual->next = novo;
 *
 * A linha 3 DEVE vir antes da linha 4
 *
 * Se invertermos 3 e 4, atual->next ja sera novo
 * na hora de executar a linha 3 e perderiamos o no
 * que estava depois de atual.
 *
 * CASO ESPECIAL: insercao apos o Tail
 *
 * Se atual e o Tail (atual->next == NULL), a linha 3
 * causaria erro. Nesse caso apenas atualizamos
 * list->tail = novo.
 *
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Estruturas ---------- */

typedef struct Paciente {
    int id;
    char nome[50];
    int prioridade;
} Paciente;

typedef struct Node {
    Paciente dados;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct DList {
    Node *head;
    Node *tail;
    int size;
} DList;

/* ---------- Funcoes auxiliares ---------- */

DList *criar_lista(void) {
    DList *list = (DList *)malloc(sizeof(DList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

Node *criar_no(int id, const char *nome, int prioridade) {
    Node *novo = (Node *)malloc(sizeof(Node));

    novo->dados.id = id;
    novo->dados.prioridade = prioridade;

    strncpy(novo->dados.nome, nome, sizeof(novo->dados.nome) - 1);
    novo->dados.nome[sizeof(novo->dados.nome) - 1] = '\0';

    novo->next = NULL;
    novo->previous = NULL;

    return novo;
}

void inserir_tail(DList *list, int id, const char *nome, int prioridade) {
    Node *novo = criar_no(id, nome, prioridade);

    if (!list->tail) {
        list->head = novo;
        list->tail = novo;
    } else {
        novo->previous = list->tail;
        list->tail->next = novo;
        list->tail = novo;
    }

    list->size++;
}

void imprimir_lista(DList *list) {
    printf("\n=== Fila de Triagem [size=%d] ===\n", list->size);

    Node *cur = list->head;
    int pos = 1;

    while (cur) {
        printf("  %d. [id=%-3d | %-15s | prioridade=%d]",
               pos++,
               cur->dados.id,
               cur->dados.nome,
               cur->dados.prioridade);

        if (cur == list->head) {
            printf(" HEAD");
        }

        if (cur == list->tail) {
            printf(" TAIL");
        }

        printf("\n");
        cur = cur->next;
    }

    printf("=================================\n\n");
}

void liberar_lista(DList *list) {
    Node *cur = list->head;

    while (cur) {
        Node *prox = cur->next;
        free(cur);
        cur = prox;
    }

    free(list);
}

/*
 * -------------------------------------------------------
 * AS 4 LINHAS ESSENCIAIS
 * -------------------------------------------------------
 *
 * Requer que atual->next != NULL
 * Insercao no meio puro
 */

void inserir_apos_4linhas(Node *atual, Node *novo) {
    /*
     * Estado antes:
     *
     * atual <-> proximo
     *
     * Queremos:
     *
     * atual <-> novo <-> proximo
     */

    /* Linha 1 */

    novo->next = atual->next;

    /* Linha 2 */

    novo->previous = atual;

    /* Linha 3 */

    atual->next->previous = novo;

    /* Linha 4 */

    atual->next = novo;
}

/*
 * -------------------------------------------------------
 * inserir_apos
 * -------------------------------------------------------
 *
 * Insere novo logo apos atual
 *
 * Trata:
 * - meio da lista
 * - insercao apos o Tail
 */

void inserir_apos(DList *list, Node *atual, Node *novo) {
    if (!atual || !novo) {
        return;
    }

    if (atual->next == NULL) {
        /*
         * atual e o Tail
         */

        novo->previous = atual;
        novo->next = NULL;
        atual->next = novo;
        list->tail = novo;
    } else {
        /*
         * Insercao no meio
         */

        novo->next = atual->next;
        novo->previous = atual;
        atual->next->previous = novo;
        atual->next = novo;
    }

    list->size++;

    printf("[INSERIDO] id=%d (%s) apos id=%d (%s)\n",
           novo->dados.id,
           novo->dados.nome,
           atual->dados.id,
           atual->dados.nome);
}

/*
 * Busca simples por id
 */

Node *buscar_no(DList *list, int id) {
    Node *cur = list->head;

    while (cur) {
        if (cur->dados.id == id) {
            return cur;
        }

        cur = cur->next;
    }

    return NULL;
}

/* ---------- Main demonstrativa ---------- */

int main(void) {
    printf("=============================================\n");
    printf(" EXERCICIO 4 - A Danca dos Ponteiros\n");
    printf(" Insercao no Meio da Lista\n");
    printf("=============================================\n");

    DList *lista = criar_lista();

    inserir_tail(lista, 1, "Ana Paula", 3);
    inserir_tail(lista, 2, "Carlos Melo", 1);
    inserir_tail(lista, 3, "Diana Costa", 4);

    printf("\nLista inicial:\n");
    imprimir_lista(lista);

    /*
     * Inserir Bruno apos Ana
     */

    Node *ana = buscar_no(lista, 1);
    Node *bruno = criar_no(10, "Bruno Lima", 2);

    inserir_apos(lista, ana, bruno);

    printf("\nApos inserir Bruno depois de Ana:\n");
    imprimir_lista(lista);

    /*
     * Inserir Eduardo apos Diana
     */

    Node *diana = buscar_no(lista, 3);
    Node *eduardo = criar_no(20, "Eduardo Reis", 5);

    inserir_apos(lista, diana, eduardo);

    printf("\nApos inserir Eduardo depois de Diana:\n");
    imprimir_lista(lista);

    /*
     * Verificacao reversa
     */

    printf("Verificacao reversa (Tail para Head):\n");

    Node *cur = lista->tail;

    while (cur) {
        printf("  id=%d (%s)\n",
               cur->dados.id,
               cur->dados.nome);

        cur = cur->previous;
    }

    printf("\n");

    liberar_lista(lista);

    return 0;
}