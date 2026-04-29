#include <stdio.h>
#include "nodo.h"

int main(void) {
    printf("=== Exercicio 1: Nodo Duplo ===\n\n");

    Nodo *a = criar_nodo(10);
    Nodo *b = criar_nodo(20);
    Nodo *c = criar_nodo(30);

    /* Liga manualmente: a <-> b <-> c */
    definir_proximo(a, b);
    definir_anterior(b, a);
    definir_proximo(b, c);
    definir_anterior(c, b);

    printf("Valores criados: %d, %d, %d\n",
           obter_valor(a), obter_valor(b), obter_valor(c));

    printf("Percurso a->b->c: %d -> %d -> %d\n",
           obter_valor(a),
           obter_valor(obter_proximo(a)),
           obter_valor(obter_proximo(obter_proximo(a))));

    printf("Percurso c->b->a: %d -> %d -> %d\n",
           obter_valor(c),
           obter_valor(obter_anterior(c)),
           obter_valor(obter_anterior(obter_anterior(c))));

    /* Atualiza valor de b */
    definir_valor(b, 99);
    printf("Apos definir_valor(b, 99): %d\n", obter_valor(b));

    destruir_nodo(a);
    destruir_nodo(b);
    destruir_nodo(c);

    printf("\nNodos destruidos com sucesso.\n");
    return 0;
}
