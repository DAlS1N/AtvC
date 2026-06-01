#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *criarNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) { fprintf(stderr, "Memoria insuficiente.\n"); exit(1); }
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)      raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/*
 * O menor valor sempre esta no no mais a esquerda.
 * Descemos pela subarvore esquerda ate nao haver mais filho esquerdo.
 */
int menorValor(No *raiz) {
    if (raiz == NULL) {
        fprintf(stderr, "Arvore vazia.\n");
        exit(1);
    }
    if (raiz->esq == NULL) return raiz->valor;
    return menorValor(raiz->esq);
}

/*
 * O maior valor sempre esta no no mais a direita.
 * Descemos pela subarvore direita ate nao haver mais filho direito.
 */
int maiorValor(No *raiz) {
    if (raiz == NULL) {
        fprintf(stderr, "Arvore vazia.\n");
        exit(1);
    }
    if (raiz->dir == NULL) return raiz->valor;
    return maiorValor(raiz->dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main(void) {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 75};
    int n = sizeof(valores) / sizeof(valores[0]);

    printf("Inserindo valores:");
    for (int i = 0; i < n; i++) {
        printf(" %d", valores[i]);
        raiz = inserir(raiz, valores[i]);
    }
    printf("\n\n");

    printf("Menor valor da arvore: %d\n", menorValor(raiz));
    printf("Maior valor da arvore: %d\n", maiorValor(raiz));

    liberarArvore(raiz);
    return 0;
}
