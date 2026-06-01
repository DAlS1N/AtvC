#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    int matricula;
    char nome[50];
    float nota;
} Aluno;

typedef struct No {
    Aluno aluno;
    struct No *esq;
    struct No *dir;
} No;

No *criarNo(int matricula, const char *nome, float nota) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        exit(1);
    }
    novo->aluno.matricula = matricula;
    strncpy(novo->aluno.nome, nome, 49);
    novo->aluno.nome[49] = '\0';
    novo->aluno.nota = nota;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int matricula, const char *nome, float nota) {
    if (raiz == NULL) {
        printf("Inserindo aluno %d - %s\n", matricula, nome);
        return criarNo(matricula, nome, nota);
    }
    if (matricula < raiz->aluno.matricula) {
        raiz->esq = inserir(raiz->esq, matricula, nome, nota);
    } else if (matricula > raiz->aluno.matricula) {
        raiz->dir = inserir(raiz->dir, matricula, nome, nota);
    } else {
        printf("Matricula %d ja existe na arvore.\n", matricula);
    }
    return raiz;
}

No *buscar(No *raiz, int matricula) {
    if (raiz == NULL || raiz->aluno.matricula == matricula) {
        return raiz;
    }
    if (matricula < raiz->aluno.matricula) {
        return buscar(raiz->esq, matricula);
    }
    return buscar(raiz->dir, matricula);
}

void imprimirEmOrdem(No *raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq);
    printf("%d - %s - Nota: %.1f\n",
           raiz->aluno.matricula,
           raiz->aluno.nome,
           raiz->aluno.nota);
    imprimirEmOrdem(raiz->dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main(void) {
    No *raiz = NULL;

    raiz = inserir(raiz, 102, "Ana",   9.0f);
    raiz = inserir(raiz, 55,  "Bruno", 8.5f);
    raiz = inserir(raiz, 180, "Carla", 7.5f);
    raiz = inserir(raiz, 30,  "Diego", 6.0f);
    raiz = inserir(raiz, 75,  "Eva",   9.5f);

    printf("\nAlunos em ordem:\n");
    imprimirEmOrdem(raiz);

    int buscas[] = {102, 55, 999};
    int n = sizeof(buscas) / sizeof(buscas[0]);

    for (int i = 0; i < n; i++) {
        printf("\nBuscar matricula %d:\n", buscas[i]);
        No *encontrado = buscar(raiz, buscas[i]);
        if (encontrado) {
            printf("Aluno encontrado: %s (Nota: %.1f)\n",
                   encontrado->aluno.nome,
                   encontrado->aluno.nota);
        } else {
            printf("Matricula %d nao encontrada.\n", buscas[i]);
        }
    }

    liberarArvore(raiz);
    return 0;
}
