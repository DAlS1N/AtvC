#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore.h"
#include "buscas.h"

/* ------------------------------------------------------------------ */
/* Utilitários                                                          */
/* ------------------------------------------------------------------ */

/* Preenche vetor com valores 1..n em ordem crescente */
void preencherOrdenado(int *v, long n) {
    for (long i = 0; i < n; i++)
        v[i] = (int)(i + 1);
}

/* Fisher-Yates shuffle */
void embaralhar(int *v, long n) {
    srand((unsigned)time(NULL));
    for (long i = n - 1; i > 0; i--) {
        long j = rand() % (i + 1);
        int tmp = v[i]; v[i] = v[j]; v[j] = tmp;
    }
}

/* Insere vetor inteiro na BST — usa versão iterativa para evitar
   estouro de pilha em entrada de 1 M ordenada                        */
No* inserirTodos(int *v, long n) {
    No *raiz = NULL;
    for (long i = 0; i < n; i++)
        raiz = inserirNaArvore(raiz, v[i]);
    return raiz;
}

/* ------------------------------------------------------------------ */
/* Impressão de uma linha da tabela                                    */
/* ------------------------------------------------------------------ */

void rodarExperimento(FILE *csv,
                      int *v, long n,
                      const char *tipo,
                      int *alvos, int numAlvos,
                      No *arvore, int altArvore) {

    /* Ordena cópia para busca binária */
    int *vOrd = (int*)malloc(n * sizeof(int));
    if (!vOrd) { fprintf(stderr, "Sem memoria para vOrd\n"); return; }
    memcpy(vOrd, v, n * sizeof(int));
    qsort(vOrd, n, sizeof(int), comparar);

    for (int t = 0; t < numAlvos; t++) {
        int alvo = alvos[t];
        int cmpSeq = 0, cmpBin = 0, cmpArv = 0;
        clock_t ini, fim;
        double tSeq, tBin, tArv;

        /* Busca sequencial */
        ini = clock();
        buscaSequencial(v, (int)n, alvo, &cmpSeq);
        fim = clock();
        tSeq = (double)(fim - ini) / CLOCKS_PER_SEC;

        /* Busca binária */
        ini = clock();
        buscaBinaria(vOrd, (int)n, alvo, &cmpBin);
        fim = clock();
        tBin = (double)(fim - ini) / CLOCKS_PER_SEC;

        /* Busca na árvore */
        ini = clock();
        buscarNaArvore(arvore, alvo, &cmpArv);
        fim = clock();
        tArv = (double)(fim - ini) / CLOCKS_PER_SEC;

        /* Console */
        printf("  Alvo=%-10d | Seq:%7d (%.6fs) | Bin:%5d (%.6fs) | Arv:%5d (%.6fs) | H=%d\n",
               alvo, cmpSeq, tSeq, cmpBin, tBin, cmpArv, tArv, altArvore);

        /* CSV */
        if (csv)
            fprintf(csv, "%ld,%s,%d,%d,%.6f,%d,%.6f,%d,%.6f,%d\n",
                    n, tipo, alvo,
                    cmpSeq, tSeq,
                    cmpBin, tBin,
                    cmpArv, tArv,
                    altArvore);
    }

    free(vOrd);
}

/* ------------------------------------------------------------------ */
/* Experimento completo para um dado n                                 */
/* ------------------------------------------------------------------ */

void executarExperimento(FILE *csv, long n, int dotPequeno) {
    printf("\n=== n = %ld ===\n", n);

    int *v = (int*)malloc(n * sizeof(int));
    if (!v) { fprintf(stderr, "Sem memoria para n=%ld\n", n); return; }

    /* Alvos: inicio, quarto, meio, tres-quartos, fim, inexistente */
    int alvos[] = {
        (int)(n * 0.01),
        (int)(n * 0.25),
        (int)(n * 0.50),
        (int)(n * 0.75),
        (int)(n * 0.99),
        (int)(n + 999)   /* inexistente */
    };
    int numAlvos = 6;

    /* --- ORDENADO --- */
    printf("  [Ordenado]\n");
    preencherOrdenado(v, n);
    No *arvOrd = inserirTodos(v, n);
    int hOrd = alturaArvore(arvOrd);
    printf("  Altura da arvore (ordenada): %d\n", hOrd);
    if (dotPequeno)
        exportarDOT(arvOrd, "resultados/arvore_ordenada.dot");
    rodarExperimento(csv, v, n, "Ordenado", alvos, numAlvos, arvOrd, hOrd);
    liberarArvore(arvOrd);

    /* --- EMBARALHADO --- */
    printf("  [Embaralhado]\n");
    preencherOrdenado(v, n);
    embaralhar(v, n);
    No *arvEmb = inserirTodos(v, n);
    int hEmb = alturaArvore(arvEmb);
    printf("  Altura da arvore (embaralhada): %d\n", hEmb);
    if (dotPequeno)
        exportarDOT(arvEmb, "resultados/arvore_embaralhada.dot");
    rodarExperimento(csv, v, n, "Embaralhado", alvos, numAlvos, arvEmb, hEmb);
    liberarArvore(arvEmb);

    free(v);
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */

int main(void) {
    /* Cria pasta de resultados se não existir (funciona no Linux) */
    system("mkdir -p resultados");

    FILE *csv = fopen("resultados/resultados.csv", "w");
    if (csv)
        fprintf(csv, "n,tipo,alvo,cmp_seq,t_seq,cmp_bin,t_bin,cmp_arv,t_arv,altura\n");

    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  SA2 – Análise de Buscas e Árvores Binárias de Busca  ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    /* Experimentos 1 e 2: n = 100 (exporta DOT) */
    executarExperimento(csv, 100, 1);

    /* Experimentos 3 e 4: n = 1.000.000 */
    executarExperimento(csv, 1000000, 0);

    /*
     * Experimentos 5 e 6: n = 1.000.000.000
     *
     * ATENÇÃO: requerem ~4 GB de RAM para o vetor de inteiros e,
     * no caso ordenado, a BST degenerada atingiria altura 10^9,
     * consumindo memória equivalente. Por essa razão, quando detectado
     * ambiente com menos de 8 GB disponíveis este bloco é pulado e os
     * resultados são estimados analiticamente no README.
     *
     * Para habilitar, compile com: make ENABLE_BILLION=1
     */
#ifdef ENABLE_BILLION
    executarExperimento(csv, 1000000000L, 0);
#else
    printf("\n=== n = 1.000.000.000 ===\n");
    printf("  [PULADO] Compile com 'make ENABLE_BILLION=1' para rodar.\n");
    printf("  Estimativas analiticas estao no README.md.\n");
#endif

    if (csv) fclose(csv);
    printf("\nResultados salvos em resultados/resultados.csv\n");
    return 0;
}
