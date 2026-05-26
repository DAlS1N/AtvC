#ifndef ARVORE_H
#define ARVORE_H

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

No* criarNo(int valor);
No* inserir(No* raiz, int valor);
No* buscar(No* raiz, int valor);
No* remover(No* raiz, int valor);
No* encontrarMinimo(No* raiz);

#endif