#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"

/* Aloca e inicializa um novo nodo com o valor fornecido.
   Retorna NULL se a alocação falhar. */
Nodo* criar_nodo(int valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar nodo.\n");
        return NULL;
    }
    novo->valor    = valor;
    novo->anterior = NULL;
    novo->proximo  = NULL;
    return novo;
}

int obter_valor(Nodo *nodo) {
    if (nodo == NULL) {
        fprintf(stderr, "Erro: nodo nulo em obter_valor.\n");
        return -1;
    }
    return nodo->valor;
}

void definir_valor(Nodo *nodo, int valor) {
    if (nodo == NULL) {
        fprintf(stderr, "Erro: nodo nulo em definir_valor.\n");
        return;
    }
    nodo->valor = valor;
}

Nodo* obter_anterior(Nodo *nodo) {
    if (nodo == NULL) return NULL;
    return nodo->anterior;
}

Nodo* obter_proximo(Nodo *nodo) {
    if (nodo == NULL) return NULL;
    return nodo->proximo;
}

void definir_anterior(Nodo *nodo, Nodo *anterior) {
    if (nodo == NULL) return;
    nodo->anterior = anterior;
}

void definir_proximo(Nodo *nodo, Nodo *proximo) {
    if (nodo == NULL) return;
    nodo->proximo = proximo;
}

/* Libera a memória do nodo. Não desfaz os vínculos com vizinhos —
   isso é responsabilidade da lista. */
void destruir_nodo(Nodo *nodo) {
    if (nodo == NULL) return;
    free(nodo);
}
