#ifndef HASH_H
#define HASH_H

#include "lista.h"

// ============================================================
//  TAD Tabela Hash — agrupamento por categoria
//  Resolve colisões com encadeamento (cada bucket é uma Lista).
//  Vantagem: busca/inserção O(1) no caso médio.
// ============================================================

#define HASH_TAMANHO 10  // número de buckets

typedef struct {
    Lista buckets[HASH_TAMANHO];
} TabelaHash;

// Inicializa a tabela hash.
void hash_inicializar(TabelaHash *h);

// Função de hash: converte uma string de categoria em índice.
int hash_funcao(const char *categoria);

// Insere um atendimento na tabela hash (indexado por categoria).
void hash_inserir(TabelaHash *h, Atendimento a);

// Busca e lista todos os atendimentos de uma categoria.
void hash_buscar_por_categoria(const TabelaHash *h, const char *categoria);

// Exibe todos os buckets com seus conteúdos.
void hash_listar_todos(const TabelaHash *h);

// Libera toda a memória da tabela hash.
void hash_destruir(TabelaHash *h);

#endif // HASH_H
