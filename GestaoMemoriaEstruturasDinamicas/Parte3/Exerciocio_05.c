#include <stdio.h>
#include <stdlib.h>

struct Produto {
    int ID;
    int preco;
};

struct Produto* clonar(struct Produto *origem);

int main() {

//Clonagem: Escreva uma função Produto* clonar(Produto *origem) que aloca um novo espaço e copia os dados de um produto existente .

    struct Produto p1;
    p1.ID = 10;
    p1.preco = 200;

    struct Produto *p2 = clonar(&p1);

    if (p2 != NULL) {
        printf("Original: ID=%d, Preco=%d\n", p1.ID, p1.preco);
        printf("Clone: ID=%d, Preco=%d\n", p2->ID, p2->preco);
    }

    free(p2);

    return 0;
}

struct Produto* clonar(struct Produto *origem) {
    if (origem == NULL) return NULL;

    struct Produto *novo = (struct Produto *) malloc(sizeof(struct Produto));
    if (novo == NULL) return NULL;

    novo->ID = origem->ID;
    novo->preco = origem->preco;

    return novo;
}