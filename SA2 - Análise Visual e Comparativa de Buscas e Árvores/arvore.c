#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

No* criarNo(int valor) {
    No *novo = (No*)malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

No* inserirNaArvore(No *raiz, int valor) {
    if (raiz == NULL)
        return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserirNaArvore(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserirNaArvore(raiz->direita, valor);
    return raiz;
}

int buscarNaArvore(No *raiz, int valor, int *comparacoes) {
    if (raiz == NULL) {
        (*comparacoes)++;
        return 0;
    }
    (*comparacoes)++;
    if (valor == raiz->valor)
        return 1;
    if (valor < raiz->valor)
        return buscarNaArvore(raiz->esquerda, valor, comparacoes);
    return buscarNaArvore(raiz->direita, valor, comparacoes);
}

int alturaArvore(No *raiz) {
    if (raiz == NULL)
        return 0;
    int altEsq = alturaArvore(raiz->esquerda);
    int altDir = alturaArvore(raiz->direita);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

/* Exporta a arvore para formato DOT (Graphviz) */
static void _exportarNos(No *no, FILE *f) {
    if (!no) return;
    if (no->esquerda)
        fprintf(f, "    %d -> %d;\n", no->valor, no->esquerda->valor);
    if (no->direita)
        fprintf(f, "    %d -> %d;\n", no->valor, no->direita->valor);
    _exportarNos(no->esquerda, f);
    _exportarNos(no->direita, f);
}

void exportarDOT(No *raiz, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        fprintf(stderr, "Erro ao criar arquivo DOT.\n");
        return;
    }
    fprintf(f, "digraph Arvore {\n");
    fprintf(f, "    node [shape=circle];\n");
    _exportarNos(raiz, f);
    fprintf(f, "}\n");
    fclose(f);
    printf("  Arquivo DOT exportado: %s\n", nomeArquivo);
}
