/*
 * ============================================================
 * EXERCICIO 3 - Navegacao no Tempo (Busca Bidirecional)
 * ============================================================
 *
 * Funcao: buscar_paciente_reverso(DList *list, int id_procurado)
 *
 * Estrategia:
 *
 * - Comeca no Tail da lista
 * - Navega em direcao ao Head usando o ponteiro previous
 * - Retorna 1 se o paciente for encontrado, 0 caso contrario
 *
 * Vantagem da busca reversa:
 *
 * Quando se sabe (ou suspeita) que o elemento procurado
 * foi inserido recentemente (e portanto esta proximo do
 * final da fila), a busca a partir do Tail pode encontrar
 * o alvo muito mais rapido na pratica, especialmente se
 * comparada a sempre comecar pelo Head.
 *
 * O pior caso continua O(n), mas o caso medio melhora.
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
    printf("HEAD <-> ");

    Node *cur = list->head;

    while (cur) {
        printf("[id=%d | %s | p=%d]",
               cur->dados.id,
               cur->dados.nome,
               cur->dados.prioridade);

        if (cur->next) {
            printf(" <-> ");
        }

        cur = cur->next;
    }

    printf(" <-> TAIL\n");
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
 * buscar_paciente_reverso
 * -------------------------------------------------------
 *
 * Percorre a lista do Tail ao Head usando previous
 *
 * Parametros:
 *
 * list         - ponteiro para a lista duplamente encadeada
 * id_procurado - id do paciente a ser localizado
 *
 * Retorno:
 *
 * 1 - paciente encontrado
 * 0 - paciente nao encontrado
 */

int buscar_paciente_reverso(DList *list, int id_procurado) {
    if (!list || !list->tail) {
        printf("[BUSCA REVERSA] Lista vazia.\n");
        return 0;
    }

    printf("[BUSCA REVERSA] Procurando id=%d a partir do Tail...\n",
           id_procurado);

    Node *atual = list->tail;
    int passos = 0;

    while (atual != NULL) {
        passos++;

        printf("  passo %d - verificando id=%d (%s)\n",
               passos,
               atual->dados.id,
               atual->dados.nome);

        if (atual->dados.id == id_procurado) {
            printf("  ENCONTRADO em %d passo(s)\n",
                   passos);

            printf("  Paciente: %s | prioridade: %d\n\n",
                   atual->dados.nome,
                   atual->dados.prioridade);

            return 1;
        }

        atual = atual->previous;
    }

    printf("  id=%d NAO encontrado apos %d passo(s)\n\n",
           id_procurado,
           passos);

    return 0;
}

/* Versao que retorna o ponteiro para o no */

Node *buscar_no_reverso(DList *list, int id_procurado) {
    Node *atual = list ? list->tail : NULL;

    while (atual) {
        if (atual->dados.id == id_procurado) {
            return atual;
        }

        atual = atual->previous;
    }

    return NULL;
}

/* ---------- Main demonstrativa ---------- */

int main(void) {
    printf("=============================================\n");
    printf(" EXERCICIO 3 - Busca Bidirecional Reversa\n");
    printf("=============================================\n");

    DList *lista = criar_lista();

    inserir_tail(lista, 101, "Ana Paula", 3);
    inserir_tail(lista, 102, "Bruno Lima", 2);
    inserir_tail(lista, 103, "Carlos Melo", 1);
    inserir_tail(lista, 104, "Diana Costa", 4);
    inserir_tail(lista, 105, "Eduardo Reis", 5);

    imprimir_lista(lista);

    /* Busca pelo primeiro elemento */

    buscar_paciente_reverso(lista, 101);

    /* Busca pelo ultimo elemento */

    buscar_paciente_reverso(lista, 105);

    /* Busca por id inexistente */

    buscar_paciente_reverso(lista, 999);

    /* Busca por elemento do meio */

    buscar_paciente_reverso(lista, 103);

    liberar_lista(lista);

    return 0;
}