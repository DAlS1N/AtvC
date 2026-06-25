#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// ============================================================
//  TAD Lista Encadeada — implementação
// ============================================================

void lista_inicializar(Lista *l) {
    l->cabeca  = NULL;
    l->tamanho = 0;
}

int lista_vazia(const Lista *l) {
    return l->cabeca == NULL;
}

void lista_inserir(Lista *l, Atendimento a) {
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (!novo) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    novo->dado    = a;
    novo->proximo = NULL;

    if (lista_vazia(l)) {
        l->cabeca = novo;
    } else {
        NoLista *atual = l->cabeca;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo;
    }
    l->tamanho++;
}

int lista_atualizar_status(Lista *l, int id, const char *novo_status) {
    NoLista *atual = l->cabeca;
    while (atual != NULL) {
        if (atual->dado.id == id) {
            strncpy(atual->dado.status, novo_status, sizeof(atual->dado.status) - 1);
            atual->dado.status[sizeof(atual->dado.status) - 1] = '\0';
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void lista_listar(const Lista *l) {
    if (lista_vazia(l)) {
        printf("  Historico vazio.\n");
        return;
    }
    printf("  === Historico de Atendimentos (%d registro(s)) ===\n", l->tamanho);
    NoLista *atual = l->cabeca;
    while (atual != NULL) {
        atendimento_imprimir(&atual->dado);
        atual = atual->proximo;
    }
}

void lista_buscar_por_cliente(const Lista *l, const char *nome) {
    int encontrados = 0;
    NoLista *atual = l->cabeca;
    while (atual != NULL) {
        // Busca parcial — verifica se o nome está contido no campo cliente
        if (strstr(atual->dado.cliente, nome) != NULL) {
            atendimento_imprimir(&atual->dado);
            encontrados++;
        }
        atual = atual->proximo;
    }
    if (encontrados == 0)
        printf("  Nenhum atendimento encontrado para \"%s\".\n", nome);
    else
        printf("  %d resultado(s) encontrado(s).\n", encontrados);
}

void lista_buscar_por_prioridade(const Lista *l, int prioridade) {
    int encontrados = 0;
    NoLista *atual = l->cabeca;
    while (atual != NULL) {
        if (atual->dado.prioridade == prioridade) {
            atendimento_imprimir(&atual->dado);
            encontrados++;
        }
        atual = atual->proximo;
    }
    if (encontrados == 0)
        printf("  Nenhum atendimento com essa prioridade.\n");
    else
        printf("  %d resultado(s) encontrado(s).\n", encontrados);
}

void lista_destruir(Lista *l) {
    NoLista *atual = l->cabeca;
    while (atual != NULL) {
        NoLista *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    l->cabeca  = NULL;
    l->tamanho = 0;
}
