#include <stdio.h>
#include <stdlib.h>

/* ===================== BST ===================== */

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
 * Busca na arvore contando comparacoes.
 * Retorna 1 se encontrado, 0 caso contrario.
 * O contador e passado por ponteiro para ser atualizado.
 */
int buscarArvore(No *raiz, int alvo, int *comparacoes) {
    if (raiz == NULL) return 0;
    (*comparacoes)++;
    if (alvo == raiz->valor) return 1;
    if (alvo < raiz->valor)  return buscarArvore(raiz->esq, alvo, comparacoes);
    return buscarArvore(raiz->dir, alvo, comparacoes);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* ================ Busca Sequencial ================ */

/*
 * Percorre o vetor elemento a elemento.
 * Retorna o indice encontrado ou -1.
 */
int buscaSequencial(int *vetor, int tamanho, int alvo, int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (vetor[i] == alvo) return i;
    }
    return -1;
}

/* ===================== main ===================== */

int main(void) {
    /* Valores desordenados para tornar a comparacao justa */
    int valores[] = {
        45, 12, 78, 34, 90, 23, 67, 5, 89, 56,
        11, 72, 38, 49, 63, 81, 17, 95, 29, 75
    };
    int tamanho = sizeof(valores) / sizeof(valores[0]);

    /* Monta vetor e arvore com os mesmos dados */
    No *raiz = NULL;
    for (int i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    int alvos[] = {75, 5, 100};
    int nAlvos  = sizeof(alvos) / sizeof(alvos[0]);

    for (int a = 0; a < nAlvos; a++) {
        int alvo = alvos[a];
        int compSeq = 0, compArv = 0;

        int idxSeq   = buscaSequencial(valores, tamanho, alvo, &compSeq);
        int achouArv = buscarArvore(raiz, alvo, &compArv);

        printf("=== Valor buscado: %d ===\n", alvo);

        printf("\nBusca sequencial:\n");
        printf("  %s\n", idxSeq >= 0 ? "Encontrado." : "Nao encontrado.");
        printf("  Comparacoes: %d\n", compSeq);

        printf("\nBusca na arvore:\n");
        printf("  %s\n", achouArv ? "Encontrado." : "Nao encontrado.");
        printf("  Comparacoes: %d\n", compArv);

        printf("\n");
    }

    liberarArvore(raiz);
    return 0;
}
