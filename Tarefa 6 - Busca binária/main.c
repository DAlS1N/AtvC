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

/* ---------- utilitários ---------- */
 
/* Copia todos os produtos de um vetor para outro.
   Usada antes de cada algoritmo para que todos comecem com os mesmos dados. */
void copiar(Produto dest[], Produto orig[], int n) {
    for (int i = 0; i < n; i++) dest[i] = orig[i];
}
 
/* Mostra todos os produtos na tela. */
void imprimir(Produto v[], int n) {
    for (int i = 0; i < n; i++)
        printf("  Cod: %3d | %-12s | R$ %.2f\n", v[i].codigo, v[i].nome, v[i].valor);
}

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

/* ---------- geração de cenários ---------- */

/* Cenário 1: dados com codigos sorteados aleatoriamente (situação real). */
void gerar_aleatorio(Produto v[], int n) {
    const char *nomes[] = {"Teclado","Mouse","Monitor","Notebook","Headset",
                           "Webcam","Impressora","Roteador","SSD","Pendrive"};
    for (int i = 0; i < n; i++) {
        v[i].codigo = rand() % (n * 10);
        snprintf(v[i].nome, sizeof(v[i].nome), "%s", nomes[i % 10]);
        v[i].valor = (rand() % 50000) / 100.0f;
    }
}

/* Cenário 2: dados já em ordem crescente de codigo (melhor caso). */
void gerar_ordenado(Produto v[], int n) {
    const char *nomes[] = {"Teclado","Mouse","Monitor","Notebook","Headset",
                           "Webcam","Impressora","Roteador","SSD","Pendrive"};
    for (int i = 0; i < n; i++) {
        v[i].codigo = i + 1;
        snprintf(v[i].nome, sizeof(v[i].nome), "%s", nomes[i % 10]);
        v[i].valor = (i + 1) * 10.0f;
    }
}

/* Cenário 3: dados em ordem decrescente de codigo (pior caso). */
void gerar_inverso(Produto v[], int n) {
    const char *nomes[] = {"Teclado","Mouse","Monitor","Notebook","Headset",
                           "Webcam","Impressora","Roteador","SSD","Pendrive"};
    for (int i = 0; i < n; i++) {
        v[i].codigo = n - i;
        snprintf(v[i].nome, sizeof(v[i].nome), "%s", nomes[i % 10]);
        v[i].valor = (n - i) * 10.0f;
    }
}
 