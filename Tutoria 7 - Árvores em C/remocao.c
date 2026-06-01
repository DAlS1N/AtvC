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

void imprimirEmOrdem(No *raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    imprimirEmOrdem(raiz->dir);
}

/*
 * Encontra o no com menor valor na subarvore (sucessor in-order).
 * Usado no caso de remocao de no com dois filhos.
 */
No *menorNo(No *raiz) {
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

/*
 * Remove um valor da BST tratando os tres casos:
 *   1. No folha            -> simplesmente libera e retorna NULL
 *   2. No com um filho     -> substitui pelo filho existente
 *   3. No com dois filhos  -> substitui pelo sucessor in-order (menor da
 *                             subarvore direita) e remove o sucessor
 */
No *remover(No *raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d nao encontrado na arvore.\n", valor);
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        /* No encontrado — verificar qual dos tres casos */

        /* Caso 1 e 2: sem filho esquerdo */
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        /* Caso 2: sem filho direito */
        if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        /* Caso 3: dois filhos
         * Copia o valor do sucessor in-order para este no
         * e remove o sucessor da subarvore direita.
         */
        No *sucessor = menorNo(raiz->dir);
        raiz->valor = sucessor->valor;
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }
    return raiz;
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/*
 * Arvore inicial do enunciado:
 *         50
 *        /  \
 *      30    70
 *     / \   / \
 *   20  40 60  80
 */
int main(void) {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) raiz = inserir(raiz, valores[i]);

    printf("Arvore inicial em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n\n");

    /* Caso 1: remover no folha */
    printf("Removendo 20 (no folha)...\n");
    raiz = remover(raiz, 20);
    printf("Em ordem apos remocao: ");
    imprimirEmOrdem(raiz);
    printf("\n\n");

    /* Caso 2: remover no com filhos */
    printf("Removendo 30 (no com filho(s))...\n");
    raiz = remover(raiz, 30);
    printf("Em ordem apos remocao: ");
    imprimirEmOrdem(raiz);
    printf("\n\n");

    /* Caso 3: remover raiz com dois filhos */
    printf("Removendo 50 (raiz com dois filhos)...\n");
    raiz = remover(raiz, 50);
    printf("Em ordem apos remocao: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}
