#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"

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
    if (nodo == NULL) return -1;
    return nodo->valor;
}

void definir_valor(Nodo *nodo, int valor) {
    if (nodo == NULL) return;
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

void destruir_nodo(Nodo *nodo) {
    if (nodo == NULL) return;
    free(nodo);
}
