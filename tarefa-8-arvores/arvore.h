#ifndef ARVORE_H
#define ARVORE_H

/* Exercício 3 — Struct do nó */
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

/* Exercício 4 */
No* criarNo(int valor);

/* Exercício 6 */
No* inserir(No* raiz, int valor);

/* Exercício 8 */
int buscar(No* raiz, int valor);

/* Exercício 9 */
void emOrdem(No* raiz);

/* Exercício 11 */
No* remover(No* raiz, int valor);
void liberarArvore(No* raiz);

/* Auxiliar para remoção */
No* encontrarMinimo(No* raiz);

#endif