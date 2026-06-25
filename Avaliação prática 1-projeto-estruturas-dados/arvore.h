#ifndef ARVORE_H
#define ARVORE_H

#include "atendimento.h"

// ============================================================
//  TAD Árvore Binária de Busca (BST) — busca por ID
//  Vantagem: busca em O(log n) no caso médio vs O(n) na lista.
//  Chave de busca: campo `id` do Atendimento.
// ============================================================

typedef struct NoArvore {
    Atendimento dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

// Insere um atendimento na árvore. Retorna a nova raiz.
NoArvore *arvore_inserir(NoArvore *raiz, Atendimento a);

// Busca um atendimento pelo id. Retorna o nó encontrado ou NULL.
NoArvore *arvore_buscar(NoArvore *raiz, int id);

// Imprime a árvore em ordem crescente de id (in-order traversal).
void arvore_imprimir_inorder(const NoArvore *raiz);

// Libera toda a memória da árvore.
void arvore_destruir(NoArvore *raiz);

#endif // ARVORE_H
