#include "ordenacao.h"
#include <stddef.h>

// ============================================================
//  Ordenação — Bubble Sort na lista encadeada
//  Troca apenas os dados (Atendimento) entre os nós,
//  mantendo a estrutura de ponteiros intacta.
// ============================================================

static void trocar_dados(NoLista *a, NoLista *b) {
    Atendimento temp = a->dado;
    a->dado = b->dado;
    b->dado = temp;
}

// Ordena por prioridade decrescente (Alta=3 primeiro)
void ordenar_por_prioridade(Lista *l) {
    if (lista_vazia(l) || l->tamanho == 1) return;
    int trocou;
    do {
        trocou = 0;
        NoLista *atual = l->cabeca;
        while (atual->proximo != NULL) {
            if (atual->dado.prioridade < atual->proximo->dado.prioridade) {
                trocar_dados(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
    } while (trocou);
}

// Ordena por tempo estimado crescente (menor tempo primeiro)
void ordenar_por_tempo(Lista *l) {
    if (lista_vazia(l) || l->tamanho == 1) return;
    int trocou;
    do {
        trocou = 0;
        NoLista *atual = l->cabeca;
        while (atual->proximo != NULL) {
            if (atual->dado.tempo_estimado > atual->proximo->dado.tempo_estimado) {
                trocar_dados(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
    } while (trocou);
}
