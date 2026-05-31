#ifndef BUSCAS_H
#define BUSCAS_H

int buscaSequencial(int vetor[], int tamanho, int valor, int *comparacoes);
int buscaBinaria(int vetor[], int tamanho, int valor, int *comparacoes);
int comparar(const void *a, const void *b);

#endif
