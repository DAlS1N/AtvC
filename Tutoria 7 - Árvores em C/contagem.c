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

/* Conta todos os nos da arvore */
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

/* Conta apenas as folhas (sem filhos) */
int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return 1;
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

/* Conta nos que possuem exatamente dois filhos */
int contarNosComDoisFilhos(No *raiz) {
    if (raiz == NULL) return 0;
    int atual = (raiz->esq != NULL && raiz->dir != NULL) ? 1 : 0;
    return atual
         + contarNosComDoisFilhos(raiz->esq)
         + contarNosComDoisFilhos(raiz->dir);
}

/* Retorna a altura da arvore (arvore vazia = 0) */
int altura(No *raiz) {
    if (raiz == NULL) return 0;
    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/*
 * Arvore do enunciado:
 *         50
 *        /  \
 *      30    70
 *     / \      \
 *   20  40      80
 */
int main(void) {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 80};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("Total de nos: %d\n",           contarNos(raiz));
    printf("Total de folhas: %d\n",        contarFolhas(raiz));
    printf("Nos com dois filhos: %d\n",    contarNosComDoisFilhos(raiz));
    printf("Altura: %d\n",                 altura(raiz));

    liberarArvore(raiz);
    return 0;
}
