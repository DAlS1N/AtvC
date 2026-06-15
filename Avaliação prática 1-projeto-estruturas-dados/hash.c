#include <stdio.h>
#include <string.h>
#include "hash.h"

// ============================================================
//  TAD Tabela Hash — implementação
// ============================================================

void hash_inicializar(TabelaHash *h) {
    for (int i = 0; i < HASH_TAMANHO; i++)
        lista_inicializar(&h->buckets[i]);
}

int hash_funcao(const char *categoria) {
    // Função djb2 simplificada: soma os códigos ASCII e aplica módulo
    unsigned long hash = 0;
    while (*categoria) {
        hash = hash * 31 + (unsigned char)(*categoria);
        categoria++;
    }
    return (int)(hash % HASH_TAMANHO);
}

void hash_inserir(TabelaHash *h, Atendimento a) {
    int indice = hash_funcao(a.categoria);
    lista_inserir(&h->buckets[indice], a);
}

void hash_buscar_por_categoria(const TabelaHash *h, const char *categoria) {
    int indice = hash_funcao(categoria);
    const Lista *bucket = &h->buckets[indice];

    printf("  === Categoria: %s (bucket %d) ===\n", categoria, indice);

    int encontrados = 0;
    NoLista *atual = bucket->cabeca;
    while (atual != NULL) {
        // Compara a categoria exata (case-sensitive)
        if (strcmp(atual->dado.categoria, categoria) == 0) {
            atendimento_imprimir(&atual->dado);
            encontrados++;
        }
        atual = atual->proximo;
    }

    if (encontrados == 0)
        printf("  Nenhum atendimento encontrado para essa categoria.\n");
    else
        printf("  %d resultado(s) encontrado(s).\n", encontrados);
}

void hash_listar_todos(const TabelaHash *h) {
    printf("  === Tabela Hash — todos os buckets ===\n");
    for (int i = 0; i < HASH_TAMANHO; i++) {
        if (!lista_vazia(&h->buckets[i])) {
            printf("  [Bucket %d]\n", i);
            lista_listar(&h->buckets[i]);
        }
    }
}

void hash_destruir(TabelaHash *h) {
    for (int i = 0; i < HASH_TAMANHO; i++)
        lista_destruir(&h->buckets[i]);
}
