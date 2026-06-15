#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// ============================================================
//  TAD Árvore Binária de Busca — implementação
// ============================================================

NoArvore *arvore_inserir(NoArvore *raiz, Atendimento a) {
    // Caso base: posição vazia encontrada
    if (raiz == NULL) {
        NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore));
        if (!novo) {
            fprintf(stderr, "Erro: memoria insuficiente.\n");
            exit(EXIT_FAILURE);
        }
        novo->dado     = a;
        novo->esquerda = NULL;
        novo->direita  = NULL;
        return novo;
    }

    // Navega pela árvore comparando o id
    if (a.id < raiz->dado.id)
        raiz->esquerda = arvore_inserir(raiz->esquerda, a);
    else if (a.id > raiz->dado.id)
        raiz->direita = arvore_inserir(raiz->direita, a);
    // Se id igual, ignora (ids devem ser únicos)

    return raiz;
}

NoArvore *arvore_buscar(NoArvore *raiz, int id) {
    if (raiz == NULL)        return NULL;  // não encontrado
    if (id == raiz->dado.id) return raiz;  // encontrado

    if (id < raiz->dado.id)
        return arvore_buscar(raiz->esquerda, id);
    else
        return arvore_buscar(raiz->direita, id);
}

void arvore_imprimir_inorder(const NoArvore *raiz) {
    if (raiz == NULL) return;
    arvore_imprimir_inorder(raiz->esquerda);
    atendimento_imprimir(&raiz->dado);
    arvore_imprimir_inorder(raiz->direita);
}

void arvore_destruir(NoArvore *raiz) {
    if (raiz == NULL) return;
    arvore_destruir(raiz->esquerda);
    arvore_destruir(raiz->direita);
    free(raiz);
}
