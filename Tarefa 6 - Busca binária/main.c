#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 10

typedef struct
{
    int codigo;
    char nome[50];
    float valor;
} Produto;

/* ---------- algoritmos de ordenação ---------- */
 

void bubble_sort(Produto v[], int n, long *comp, long *trocas) {
    *comp = *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comp)++;                              /* conta a comparação */
            if (v[j].codigo > v[j+1].codigo) {
                Produto tmp = v[j]; v[j] = v[j+1]; v[j+1] = tmp;
                (*trocas)++;                        /* conta a troca */
            }
        }
    }
}


void selection_sort(Produto v[], int n, long *comp, long *trocas) {
    *comp = *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comp)++;                              /* conta a comparação */
            if (v[j].codigo < v[min].codigo) min = j;
        }
        if (min != i) {
            Produto tmp = v[i]; v[i] = v[min]; v[min] = tmp;
            (*trocas)++;                            /* conta a troca */
        }
    }
}


void insertion_sort(Produto v[], int n, long *comp, long *trocas) {
    *comp = *trocas = 0;
    for (int i = 1; i < n; i++) {
        Produto atual = v[i];   /* guarda o produto que será encaixado */
        int j = i - 1;
        while (j >= 0) {
            (*comp)++;          /* conta a comparação (inclusive quando falha) */
            if (v[j].codigo > atual.codigo) {
                v[j+1] = v[j]; /* empurra o maior uma casa para a direita */
                (*trocas)++;
                j--;
            } else break;
        }
        v[j+1] = atual;        /* encaixa o produto na posição correta */
    }
}