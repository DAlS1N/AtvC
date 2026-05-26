#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

/* Imprime separador visual */
static void separador(void) {
    printf("------------------------------------------\n");
}

/* Busca e imprime resultado (retorna 1 ou 0) */
static void testarBusca(No* raiz, int valor) {
    if (buscar(raiz, valor))
        printf("  Busca %d: ENCONTRADO\n", valor);
    else
        printf("  Busca %d: nao encontrado\n", valor);
}

int main(void) {

    /* ==================================================
       EXERCÍCIO 10 — Testando no main
       - Cria a árvore vazia
       - Insere 50, 30, 70, 20, 40, 60, 80
       - Imprime em ordem crescente
       - Busca 40 e 90
    ================================================== */
    separador();
    printf("EXERCÍCIO 10\n");
    separador();

    No* raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Arvore em ordem crescente:\n  ");
    emOrdem(raiz);
    printf("\n");

    printf("Resultados das buscas:\n");
    testarBusca(raiz, 40);
    testarBusca(raiz, 90);

    liberarArvore(raiz);
    raiz = NULL;

    /* ==================================================
       EXERCÍCIO 11 — Programa completo
       - Insere valores
       - Imprime em ordem antes das remoções
       - Remove nó folha, nó com 1 filho e nó com 2 filhos
       - Imprime em ordem após cada remoção
       - Busca valores pelo usuário
       - Libera a árvore ao final
    ================================================== */
    separador();
    printf("EXERCÍCIO 11\n");
    separador();

    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 23);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 75);  /* filho direito de 70 */

    printf("Arvore inicial em ordem crescente:\n  ");
    emOrdem(raiz);
    printf("\n");
    separador();

    /* --- Busca interativa --- */
    int op, valorBusca;
    printf("Deseja buscar um valor? (1 = sim / 0 = nao): ");
    scanf("%d", &op);
    if (op == 1) {
        printf("Digite o valor: ");
        scanf("%d", &valorBusca);
        testarBusca(raiz, valorBusca);
        separador();
    }

    /* --- Caso 1: remoção de nó FOLHA (10) --- */
    printf("Removendo 10 (no folha)...\n");
    raiz = remover(raiz, 10);
    printf("Arvore apos remocao:\n  ");
    emOrdem(raiz);
    printf("\n");
    separador();

    /* --- Caso 2: remoção de nó com UM filho (23 tem só filho 30) --- */
    printf("Removendo 23 (no com um filho)...\n");
    raiz = remover(raiz, 23);
    printf("Arvore apos remocao:\n  ");
    emOrdem(raiz);
    printf("\n");
    separador();

    /* --- Caso 3: remoção de nó com DOIS filhos (60 tem 50 e 70) --- */
    printf("Removendo 60 (no com dois filhos)...\n");
    raiz = remover(raiz, 60);
    printf("Arvore apos remocao:\n  ");
    emOrdem(raiz);
    printf("\n");
    separador();

    /* --- Remoção de valor inexistente --- */
    printf("Tentando remover 99 (nao existe na arvore)...\n");
    raiz = remover(raiz, 99);
    printf("Arvore apos tentativa:\n  ");
    emOrdem(raiz);
    printf("\n");
    separador();

    /* --- Liberação completa da memória --- */
    liberarArvore(raiz);
    raiz = NULL;
    printf("Memoria liberada com sucesso.\n");
    separador();

    return 0;
}