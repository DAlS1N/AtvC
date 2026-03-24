#include <stdio.h>
#include "caixa.h"

int main() {
    Caixa* c;

    c = criar_caixa(100);


    if(c == NULL){
        printf("Erro ao criar a caixa.\n");
        return 1;

    }

    printf("Valor inicial da caixa: %d\n", ler_valor(c));
    escrever_valor(c, 200);
    printf("Valor atualizado da caixa: %d\n", ler_valor(c));

    destruir_caixa(c);
    return 0;
}