/*
 * ============================================================
 * EXERCICIO 2 - Caca ao Bug (Memory Leak / Use-After-Free)
 * ============================================================
 *
 * CODIGO BUGADO ORIGINAL:
 * -----------------------
 *
 *   free(atual);
 *   atual->previous->next = atual->next;
 *   atual->next->previous = atual->previous;
 *   list->size--;
 *
 * ERRO FATAL:
 * -----------
 *
 * O free(atual) e chamado ANTES de usar os ponteiros
 * atual->previous e atual->next.
 *
 * O que acontece na Heap:
 *
 * 1. free(atual) devolve o bloco de memoria ao sistema
 *    operacional (ou ao gerenciador de heap do C).
 *
 * 2. As proximas linhas tentam ler atual->previous e
 *    atual->next, mas essa memoria ja foi liberada.
 *
 * 3. Isso e chamado de Use-After-Free (UAF):
 *    comportamento indefinido (Undefined Behavior).
 *
 *    Na pratica pode causar:
 *    - Segmentation Fault imediato
 *    - Corrupcao silenciosa de dados na Heap
 *    - Falhas aleatorias e dificeis de depurar
 *
 * 4. Adicionalmente, os nos vizinhos de atual ficam com
 *    ponteiros apontando para o bloco liberado
 *    (dangling pointers), corrompendo toda a lista.
 *
 * REGRA DE OURO:
 * --------------
 *
 * Reconecte os vizinhos PRIMEIRO, depois libere o no.
 *
 * "Rearranjar antes de demolir."
 *
 * CODIGO CORRIGIDO:
 * -----------------
 *
 *   atual->previous->next = atual->next;
 *   atual->next->previous = atual->previous;
 *   list->size--;
 *   free(atual);
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

Node *criar_no(int id, const char *nome) {
    Node *novo = (Node *)malloc(sizeof(Node));

    novo->dados.id = id;

    strncpy(novo->dados.nome, nome, sizeof(novo->dados.nome) - 1);
    novo->dados.nome[sizeof(novo->dados.nome) - 1] = '\0';

    novo->next = NULL;
    novo->previous = NULL;

    return novo;
}

void inserir_tail(DList *list, int id, const char *nome) {
    Node *novo = criar_no(id, nome);

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
    printf("Lista [size=%d]: ", list->size);

    Node *cur = list->head;

    while (cur) {
        printf("[%d:%s]", cur->dados.id, cur->dados.nome);

        if (cur->next) {
            printf(" <-> ");
        }

        cur = cur->next;
    }

    printf("\n");
}

/*
 * -------------------------------------------------------
 * VERSAO BUGADA - NAO USAR EM PRODUCAO
 * Use-After-Free: free() antes de usar os ponteiros
 * -------------------------------------------------------
 */

void remover_meio_BUGADO(DList *list, Node *atual) {
    printf("\n[BUGADO] Tentando remover id=%d...\n", atual->dados.id);

    free(atual);

    /* As linhas abaixo acessam memoria ja liberada */

    atual->previous->next = atual->next;
    atual->next->previous = atual->previous;

    list->size--;

    /* Resultado: lista corrompida e possivel crash */
}

/*
 * -------------------------------------------------------
 * VERSAO CORRETA - Reconectar vizinhos antes do free()
 * -------------------------------------------------------
 *
 * Trata tambem os casos de borda:
 * remocao do Head e do Tail
 */

void remover_meio_CORRETO(DList *list, Node *atual) {
    if (!atual) {
        return;
    }

    printf("\n[CORRETO] Removendo id=%d (%s)...\n",
           atual->dados.id,
           atual->dados.nome);

    /* Passo 1: Reconectar o no anterior */

    if (atual->previous) {
        atual->previous->next = atual->next;
    } else {
        /* atual e o Head */
        list->head = atual->next;
    }

    /* Passo 2: Reconectar o proximo no */

    if (atual->next) {
        atual->next->previous = atual->previous;
    } else {
        /* atual e o Tail */
        list->tail = atual->previous;
    }

    /* Passo 3: Atualizar o tamanho */

    list->size--;

    /* Passo 4: Agora sim liberar memoria */

    free(atual);
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

/* ---------- Main demonstrativa ---------- */

int main(void) {
    printf("=============================================\n");
    printf(" EXERCICIO 2 - Caca ao Bug (Use-After-Free)\n");
    printf("=============================================\n\n");

    DList *lista = criar_lista();

    inserir_tail(lista, 1, "Ana");
    inserir_tail(lista, 2, "Bruno");
    inserir_tail(lista, 3, "Carlos");
    inserir_tail(lista, 4, "Diana");

    printf("Lista inicial:\n");
    imprimir_lista(lista);

    /* Localiza o no do meio (id = 2) */

    Node *alvo = lista->head->next;

    remover_meio_CORRETO(lista, alvo);

    printf("Lista apos remocao correta do meio:\n");
    imprimir_lista(lista);

    /* Remocao do Head */

    remover_meio_CORRETO(lista, lista->head);

    printf("Lista apos remocao do Head:\n");
    imprimir_lista(lista);

    /* Remocao do Tail */

    remover_meio_CORRETO(lista, lista->tail);

    printf("Lista apos remocao do Tail:\n");
    imprimir_lista(lista);

    liberar_lista(lista);

    printf("\n--- Resumo do Bug ---\n");
    printf("ERRADO: free(atual) depois acessar atual->previous\n");
    printf("CORRETO: reconectar vizinhos primeiro e depois free(atual)\n");

    return 0;
}