#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

No* encontrarMinimo(No* raiz) {
    while (raiz && raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor) 
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor) 
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (raiz->valor > valor)
        return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}


No* remover(No* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);
    else {
        if (raiz->esquerda == NULL) return raiz->direita;
        if (raiz->direita == NULL) return raiz->esquerda;

        No* succ = encontrarMinimo(raiz->direita);
        raiz->valor = succ->valor;
        raiz->direita = remover(raiz->direita, succ->valor);
    }
    return raiz;
}