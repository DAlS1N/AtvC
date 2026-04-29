#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

/* =======================================================
   Funções internas de auxílio
   ======================================================= */

/* Aloca um NodoAluno com os dados do aluno fornecido. */
static NodoAluno* criar_nodo_aluno(Aluno aluno) {
    NodoAluno *novo = (NodoAluno*) malloc(sizeof(NodoAluno));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar NodoAluno.\n");
        return NULL;
    }
    novo->dado     = aluno;   /* cópia da struct por valor */
    novo->anterior = NULL;
    novo->proximo  = NULL;
    return novo;
}

/* =======================================================
   Criar / destruir lista
   ======================================================= */

ListaAluno* criar_lista_aluno(void) {
    ListaAluno *lista = (ListaAluno*) malloc(sizeof(ListaAluno));
    if (lista == NULL) {
        fprintf(stderr, "Erro: falha ao alocar ListaAluno.\n");
        return NULL;
    }
    lista->inicio  = NULL;
    lista->fim     = NULL;
    lista->tamanho = 0;
    return lista;
}

void destruir_lista_aluno(ListaAluno *lista) {
    if (lista == NULL) return;

    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        NodoAluno *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    free(lista);
}

int esta_vazia_aluno(ListaAluno *lista) {
    if (lista == NULL) return 1;
    return (lista->tamanho == 0);
}

/* =======================================================
   Inserção no início  O(1)
   ======================================================= */
int inserir_aluno_inicio(ListaAluno *lista, Aluno aluno) {
    if (lista == NULL) return 0;

    NodoAluno *novo = criar_nodo_aluno(aluno);
    if (novo == NULL) return 0;

    if (esta_vazia_aluno(lista)) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        novo->proximo           = lista->inicio;
        lista->inicio->anterior = novo;
        lista->inicio           = novo;
    }

    lista->tamanho++;
    return 1;
}

/* =======================================================
   Inserção no fim  O(1)
   ======================================================= */
int inserir_aluno_fim(ListaAluno *lista, Aluno aluno) {
    if (lista == NULL) return 0;

    NodoAluno *novo = criar_nodo_aluno(aluno);
    if (novo == NULL) return 0;

    if (esta_vazia_aluno(lista)) {
        lista->inicio = novo;
        lista->fim    = novo;
    } else {
        novo->anterior      = lista->fim;
        lista->fim->proximo = novo;
        lista->fim          = novo;
    }

    lista->tamanho++;
    return 1;
}

/* =======================================================
   Busca por matrícula  O(n)
   ======================================================= */
NodoAluno* buscar_por_matricula(ListaAluno *lista, int matricula) {
    if (lista == NULL) return NULL;

    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado.matricula == matricula) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

/* =======================================================
   Remoção por matrícula  O(n)
   ======================================================= */
int remover_por_matricula(ListaAluno *lista, int matricula) {
    if (lista == NULL || esta_vazia_aluno(lista)) return 0;

    NodoAluno *alvo = buscar_por_matricula(lista, matricula);
    if (alvo == NULL) {
        fprintf(stderr, "Erro: matricula %d nao encontrada.\n", matricula);
        return 0;
    }

    if (lista->tamanho == 1) {
        lista->inicio = NULL;
        lista->fim    = NULL;

    } else if (alvo == lista->inicio) {
        lista->inicio           = alvo->proximo;
        lista->inicio->anterior = NULL;

    } else if (alvo == lista->fim) {
        lista->fim          = alvo->anterior;
        lista->fim->proximo = NULL;

    } else {
        alvo->anterior->proximo = alvo->proximo;
        alvo->proximo->anterior = alvo->anterior;
    }

    free(alvo);
    lista->tamanho--;
    return 1;
}

/* =======================================================
   Impressão auxiliar de um NodoAluno
   ======================================================= */
static void imprimir_nodo_aluno(NodoAluno *n) {
    printf("  Matricula: %-6d | Nome: %-30s | Media: %.1f | Situacao: %s\n",
           n->dado.matricula,
           n->dado.nome,
           n->dado.media,
           n->dado.media >= 7.0f ? "APROVADO" : "REPROVADO");
}

/* =======================================================
   Impressão de aprovados (media >= 7.0)
   ======================================================= */
void imprimir_aprovados(ListaAluno *lista) {
    if (lista == NULL || esta_vazia_aluno(lista)) {
        printf("  [lista vazia]\n");
        return;
    }

    int encontrou = 0;
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado.media >= 7.0f) {
            imprimir_nodo_aluno(atual);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou) printf("  Nenhum aluno aprovado.\n");
}

/* =======================================================
   Impressão de reprovados (media < 7.0)
   ======================================================= */
void imprimir_reprovados(ListaAluno *lista) {
    if (lista == NULL || esta_vazia_aluno(lista)) {
        printf("  [lista vazia]\n");
        return;
    }

    int encontrou = 0;
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado.media < 7.0f) {
            imprimir_nodo_aluno(atual);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou) printf("  Nenhum aluno reprovado.\n");
}

/* =======================================================
   Impressão de todos os alunos
   ======================================================= */
void imprimir_todos(ListaAluno *lista) {
    if (lista == NULL || esta_vazia_aluno(lista)) {
        printf("  [lista vazia]\n");
        return;
    }
    NodoAluno *atual = lista->inicio;
    while (atual != NULL) {
        imprimir_nodo_aluno(atual);
        atual = atual->proximo;
    }
}
