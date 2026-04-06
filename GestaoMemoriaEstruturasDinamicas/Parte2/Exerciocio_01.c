#include <stdio.h>
#include <stdlib.h>

struct Produto
{
   int ID;
   int preco;
};


int main() {

//Entidade Produto: Defina uma struct Produto (ID e Preço). 
//Aloque-a dinamicamente e atribua valores utilizando exclusivamente o operador seta (->).

    struct Produto *p = (struct Produto *) malloc(sizeof(struct Produto));

    p->ID = 1;
    p->preco = 100;

    printf("ID: %d\n", p->ID);
    printf("Preco: %d\n", p->preco);

    free(p);

    return 0;


}



