/*
 * ============================================================
 * EXERCICIO 5 - O Desafio da Promocao (Refatoracao)
 * ============================================================
 *
 * Funcao: promover_paciente(DList *list, int id)
 *
 * Objetivo:
 *
 * Um paciente cujo estado se agravou precisa ir imediatamente
 * para o topo (Head) da fila de triagem.
 *
 * ESTRATEGIA (reutilizacao de funcoes existentes)
 * ------------------------------------------------
 *
 * Ao inves de criar logica do zero, combinamos duas operacoes:
 *
 * Passo 1 - remover_no_da_lista(list, no_alvo)
 *
 * Remove o no de onde ele estiver na lista,
 * reconectando corretamente os seus vizinhos.
 *
 * Passo 2 - inserir_no_head(list, no_alvo)
 *
 * Reinsere o no removido na posicao Head.
 * O no traz consigo todos os seus dados intactos,
 * apenas seus ponteiros sao reconfigurados.
 *
 * CUIDADO IMPORTANTE:
 *
 * Nao fazemos free() + malloc() novo.
 * Apenas desconectamos o no de sua posicao atual
 * e o reposicionamos no Head, reutilizando o mesmo
 * bloco de memoria.
 *
 * CASOS ESPECIAIS TRATADOS:
 *
 * - Paciente nao encontrado
 * - Paciente ja e o Head
 * - Lista vazia
 * - Paciente e o Tail
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
 * PASSO 1 - remover_no_da_lista
 * -------------------------------------------------------
 *
 * Remove o no de sua posicao atual SEM liberar memoria
 * Reconecta os vizinhos corretamente
 * Retorna o proprio no removido
 */

Node *remover_no_da_lista(DList *list, Node *alvo) {
    if (!alvo) {
        return NULL;
    }

    if (alvo->previous) {
        alvo->previous->next = alvo->next;
    } else {
        list->head = alvo->next;
    }

    if (alvo->next) {
        alvo->next->previous = alvo->previous;
    } else {
        list->tail = alvo->previous;
    }

    list->size--;

    alvo->next = NULL;
    alvo->previous = NULL;

    return alvo;
}

/*
 * -------------------------------------------------------
 * PASSO 2 - inserir_no_head
 * -------------------------------------------------------
 *
 * Insere um no ja existente na posicao Head
 */

void inserir_no_head(DList *list, Node *novo) {
    if (!novo) {
        return;
    }

    if (!list->head) {
        list->head = novo;
        list->tail = novo;

        novo->next = NULL;
        novo->previous = NULL;
    } else {
        novo->next = list->head;
        novo->previous = NULL;

        list->head->previous = novo;
        list->head = novo;
    }

    list->size++;
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

/*
 * -------------------------------------------------------
 * promover_paciente
 * -------------------------------------------------------
 *
 * Move qualquer paciente para o topo da fila
 */

void promover_paciente(DList *list, int id) {
    printf("Promovendo paciente id=%d para o HEAD...\n", id);

    if (!list || !list->head) {
        printf("ERRO: Lista vazia.\n\n");
        return;
    }

    Node *alvo = buscar_no(list, id);

    if (!alvo) {
        printf("ERRO: Paciente id=%d nao encontrado.\n\n", id);
        return;
    }

    if (alvo == list->head) {
        printf("INFO: Paciente %s ja esta no HEAD.\n\n",
               alvo->dados.nome);
        return;
    }

    remover_no_da_lista(list, alvo);

    inserir_no_head(list, alvo);

    printf("OK: %s promovido ao topo da fila.\n\n",
           alvo->dados.nome);
}

/* ---------- Main demonstrativa ---------- */

int main(void) {
    printf("=============================================\n");
    printf(" EXERCICIO 5 - O Desafio da Promocao\n");
    printf(" promover_paciente: remover + inserir_head\n");
    printf("=============================================\n");

    DList *lista = criar_lista();

    inserir_tail(lista, 101, "Ana Paula", 2);
    inserir_tail(lista, 102, "Bruno Lima", 1);
    inserir_tail(lista, 103, "Carlos Melo", 3);
    inserir_tail(lista, 104, "Diana Costa", 2);
    inserir_tail(lista, 105, "Eduardo Reis", 1);

    printf("\nFila inicial de triagem:\n");
    imprimir_lista(lista);

    promover_paciente(lista, 103);

    printf("Apos promover Carlos:\n");
    imprimir_lista(lista);

    promover_paciente(lista, 105);

    printf("Apos promover Eduardo:\n");
    imprimir_lista(lista);

    promover_paciente(lista, 105);

    printf("Tentativa de promover Eduardo novamente:\n");
    imprimir_lista(lista);

    promover_paciente(lista, 999);

    printf("Verificacao reversa final (Tail para Head):\n");

    Node *cur = lista->tail;

    while (cur) {
        printf("  id=%d (%s)%s\n",
               cur->dados.id,
               cur->dados.nome,
               cur->previous == NULL ? " HEAD" : "");

        cur = cur->previous;
    }

    printf("\n");

    liberar_lista(lista);

    return 0;
}