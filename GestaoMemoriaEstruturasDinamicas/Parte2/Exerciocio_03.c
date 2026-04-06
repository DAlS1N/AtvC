#include <stdio.h>

struct Produto {
    int ID;
    int preco;
};

void reset_estoque(struct Produto *p) {
    p->ID = 0;
    p->preco = 0;
}

int main() {

    struct Produto prod;

    prod.ID = 10;
    prod.preco = 200;

    printf("Antes: ID:%d, Preco:%d\n", prod.ID, prod.preco);

    reset_estoque(&prod);

    printf("Depois: ID:%d, Preco:%d\n", prod.ID, prod.preco);
    free(prod);
    return 0;
}