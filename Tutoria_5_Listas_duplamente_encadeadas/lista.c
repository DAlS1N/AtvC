#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* =======================================================
   Exercicio 2 — Estrutura base da lista duplamente encadeada
   ======================================================= */

/* Aloca e retorna uma lista vazia. */
Lista* criar_lista(void) {
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    if (lista == NULL) {
        fprintf(stderr, "Erro: falha ao alocar lista.\n");
        return NULL;
    }
    lista->inicio  = NULL;
    lista->fim     = NULL;
    lista->tamanho = 0;
    return lista;
}

/* Retorna 1 se a lista está vazia, 0 caso contrário. */
int esta_vazia(Lista *lista) {
    if (lista == NULL) return 1;
    return (lista->tamanho == 0);
}

/* Retorna o número de elementos na lista. */
int tamanho_lista(Lista *lista) {
    if (lista == NULL) return 0;
    return lista->tamanho;
}

/* Libera todos os nodos e a própria lista. */
void destruir_lista(Lista *lista) {
    if (lista == NULL) return;

    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        Nodo *prox = atual->proximo;
        destruir_nodo(atual);
        atual = prox;
    }
    free(lista);
}

/* =======================================================
   Exercicio 3 — Inserção no início  O(1)
   ======================================================= */
int inserir_inicio(Lista *lista, int valor) {
    if (lista == NULL) return 0;

    Nodo *novo = criar_nodo(valor);
    if (novo == NULL) return 0;   /* falha de alocação */

    if (esta_vazia(lista)) {
        /* Lista vazia: novo é início e fim */
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        /* Liga novo <-> antigo início */
        novo->proximo          = lista->inicio;
        lista->inicio->anterior = novo;
        lista->inicio           = novo;
    }

    lista->tamanho++;
    return 1;
}

/* =======================================================
   Exercicio 4 — Inserção no fim  O(1)
   ======================================================= */
int inserir_fim(Lista *lista, int valor) {
    if (lista == NULL) return 0;

    Nodo *novo = criar_nodo(valor);
    if (novo == NULL) return 0;

    if (esta_vazia(lista)) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        /* Liga antigo fim <-> novo */
        novo->anterior      = lista->fim;
        lista->fim->proximo = novo;
        lista->fim          = novo;
    }

    lista->tamanho++;
    return 1;
}

/* =======================================================
   Exercicio 5 — Impressão bidirecional
   ======================================================= */
void imprimir_inicio_fim(Lista *lista) {
    if (lista == NULL || esta_vazia(lista)) {
        printf("[lista vazia]\n");
        return;
    }
    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        printf("%d", atual->valor);
        if (atual->proximo != NULL) printf(" ");
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_fim_inicio(Lista *lista) {
    if (lista == NULL || esta_vazia(lista)) {
        printf("[lista vazia]\n");
        return;
    }
    Nodo *atual = lista->fim;
    while (atual != NULL) {
        printf("%d", atual->valor);
        if (atual->anterior != NULL) printf(" ");
        atual = atual->anterior;
    }
    printf("\n");
}

/* =======================================================
   Exercicio 6 — Remoção do início  O(1)
   ======================================================= */
int remover_inicio(Lista *lista, int *valor_removido) {
    if (lista == NULL || esta_vazia(lista)) {
        fprintf(stderr, "Erro: lista vazia, nao e possivel remover do inicio.\n");
        return 0;
    }

    Nodo *alvo = lista->inicio;
    *valor_removido = alvo->valor;

    if (lista->tamanho == 1) {
        /* Único elemento: lista fica vazia */
        lista->inicio = NULL;
        lista->fim    = NULL;
    } else {
        lista->inicio           = alvo->proximo;
        lista->inicio->anterior = NULL;
    }

    destruir_nodo(alvo);
    lista->tamanho--;
    return 1;
}

/* =======================================================
   Exercicio 7 — Remoção do fim  O(1)
   ======================================================= */
int remover_fim(Lista *lista, int *valor_removido) {
    if (lista == NULL || esta_vazia(lista)) {
        fprintf(stderr, "Erro: lista vazia, nao e possivel remover do fim.\n");
        return 0;
    }

    Nodo *alvo = lista->fim;
    *valor_removido = alvo->valor;

    if (lista->tamanho == 1) {
        lista->inicio = NULL;
        lista->fim    = NULL;
    } else {
        /* O ponteiro 'anterior' evita percorrer a lista toda — O(1) */
        lista->fim          = alvo->anterior;
        lista->fim->proximo = NULL;
    }

    destruir_nodo(alvo);
    lista->tamanho--;
    return 1;
}

/* =======================================================
   Exercicio 8 — Busca por valor  O(n)
   ======================================================= */
Nodo* buscar(Lista *lista, int valor) {
    if (lista == NULL) return NULL;

    Nodo *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->valor == valor) return atual;
        atual = atual->proximo;
    }
    return NULL;   /* não encontrado */
}

/* =======================================================
   Exercicio 9 — Inserção em posição específica  O(n)
   ======================================================= */
int inserir_posicao(Lista *lista, int valor, int posicao) {
    if (lista == NULL) return 0;

    /* Posição inválida */
    if (posicao < 0 || posicao > lista->tamanho) {
        fprintf(stderr, "Erro: posicao %d invalida (tamanho = %d).\n",
                posicao, lista->tamanho);
        return 0;
    }

    /* Casos extremos reutilizam as funções já implementadas */
    if (posicao == 0)               return inserir_inicio(lista, valor);
    if (posicao == lista->tamanho)  return inserir_fim(lista, valor);

    /* Inserção no meio: percorre até o nodo que está na posição */
    Nodo *novo = criar_nodo(valor);
    if (novo == NULL) return 0;

    Nodo *atual = lista->inicio;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proximo;
    }

    /*  ... <-> anterior <-> [novo] <-> atual <-> ...  */
    Nodo *ant = atual->anterior;

    novo->proximo  = atual;
    novo->anterior = ant;
    ant->proximo   = novo;
    atual->anterior = novo;

    lista->tamanho++;
    return 1;
}

/* =======================================================
   Exercicio 10 — Remoção por valor  O(n)
   ======================================================= */
int remover_valor(Lista *lista, int valor) {
    if (lista == NULL || esta_vazia(lista)) return 0;

    /* Busca o primeiro nodo com o valor */
    Nodo *alvo = buscar(lista, valor);
    if (alvo == NULL) {
        fprintf(stderr, "Erro: valor %d nao encontrado.\n", valor);
        return 0;
    }

    /* Caso: único elemento */
    if (lista->tamanho == 1) {
        lista->inicio = NULL;
        lista->fim    = NULL;
        destruir_nodo(alvo);
        lista->tamanho--;
        return 1;
    }

    /* Caso: remoção no início */
    if (alvo == lista->inicio) {
        lista->inicio           = alvo->proximo;
        lista->inicio->anterior = NULL;

    /* Caso: remoção no fim */
    } else if (alvo == lista->fim) {
        lista->fim          = alvo->anterior;
        lista->fim->proximo = NULL;

    /* Caso: remoção no meio — ajuste de 4 ponteiros */
    } else {
        alvo->anterior->proximo = alvo->proximo;
        alvo->proximo->anterior = alvo->anterior;
    }

    destruir_nodo(alvo);
    lista->tamanho--;
    return 1;
}
