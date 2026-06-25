#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// ============================================================
//  TAD Fila Dinâmica — implementação
// ============================================================

void fila_inicializar(Fila *f) {
    f->frente  = NULL;
    f->cauda   = NULL;
    f->tamanho = 0;
}

int fila_vazia(const Fila *f) {
    return f->frente == NULL;
}

void fila_enqueue(Fila *f, Atendimento a) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (!novo) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    novo->dado    = a;
    novo->proximo = NULL;

    if (fila_vazia(f)) {
        f->frente = novo;
        f->cauda  = novo;
    } else {
        f->cauda->proximo = novo;
        f->cauda = novo;
    }
    f->tamanho++;
}

Atendimento fila_dequeue(Fila *f) {
    NoFila *temp = f->frente;
    Atendimento dado = temp->dado;

    f->frente = f->frente->proximo;
    if (f->frente == NULL)
        f->cauda = NULL;

    free(temp);
    f->tamanho--;
    return dado;
}

Atendimento fila_frente(const Fila *f) {
    return f->frente->dado;
}

void fila_listar(const Fila *f) {
    if (fila_vazia(f)) {
        printf("  Fila de espera vazia.\n");
        return;
    }
    printf("  === Fila de Espera (%d atendimento(s)) ===\n", f->tamanho);
    NoFila *atual = f->frente;
    int pos = 1;
    while (atual != NULL) {
        printf("  [Posicao %d]\n", pos++);
        atendimento_imprimir(&atual->dado);
        atual = atual->proximo;
    }
}

void fila_destruir(Fila *f) {
    while (!fila_vazia(f))
        fila_dequeue(f);
}
