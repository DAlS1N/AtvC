#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

/* -------------------------------------------------------
   Exercício 4 — Criar um novo nó
   - Aloca memória com malloc
   - Armazena o valor
   - Inicializa esquerda e direita com NULL
------------------------------------------------------- */
No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }
    novo->valor    = valor;
    novo->esquerda = NULL;
    novo->direita  = NULL;
    return novo;
}

/* -------------------------------------------------------
   Auxiliar para remoção: retorna o nó com menor valor
   na subárvore (o nó mais à esquerda)
------------------------------------------------------- */
No* encontrarMinimo(No* raiz) {
    while (raiz != NULL && raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

/* -------------------------------------------------------
   Exercício 6 — Inserção na árvore binária de busca
   - Valores menores vão para a esquerda
   - Valores maiores vão para a direita
------------------------------------------------------- */
No* inserir(No* raiz, int valor) {
    if (raiz == NULL)
        return criarNo(valor);

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita  = inserir(raiz->direita,  valor);
    /* valor == raiz->valor: duplicatas são ignoradas */

    return raiz;
}

/* -------------------------------------------------------
   Exercício 8 — Busca na árvore
   - Retorna 1 se o valor for encontrado
   - Retorna 0 se não for encontrado
------------------------------------------------------- */
int buscar(No* raiz, int valor) {
    if (raiz == NULL)
        return 0;
    if (raiz->valor == valor)
        return 1;
    if (valor < raiz->valor)
        return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

/* -------------------------------------------------------
   Exercício 9 — Percurso em ordem (in-order)
   Ordem: esquerda -> raiz -> direita
   Resultado: valores impressos em ordem crescente
------------------------------------------------------- */
void emOrdem(No* raiz) {
    if (raiz == NULL)
        return;
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->valor);
    emOrdem(raiz->direita);
}

/* -------------------------------------------------------
   Exercício 11 — Remoção de um nó
   Três casos tratados:
   1. Nó folha              → simplesmente removido
   2. Nó com um filho       → filho substitui o nó
   3. Nó com dois filhos    → substituído pelo sucessor
                              (menor valor da subárvore
                              direita)
------------------------------------------------------- */
No* remover(No* raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita  = remover(raiz->direita,  valor);
    } else {
        /* Nó encontrado — verificar os três casos */

        /* Caso 1 e 2: sem filho esquerdo */
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }
        /* Caso 2: sem filho direito */
        if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        /* Caso 3: dois filhos
           Encontra o sucessor (mínimo da subárvore direita),
           copia seu valor e remove o sucessor da subárvore */
        No* succ      = encontrarMinimo(raiz->direita);
        raiz->valor   = succ->valor;
        raiz->direita = remover(raiz->direita, succ->valor);
    }
    return raiz;
}

/* -------------------------------------------------------
   Exercício 11 — Liberar toda a árvore da memória
   Percurso pós-ordem: libera filhos antes do pai
------------------------------------------------------- */
void liberarArvore(No* raiz) {
    if (raiz == NULL)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}