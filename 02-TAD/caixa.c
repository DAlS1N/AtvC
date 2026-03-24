#include <stdio.h>
#include "caixa.h"

struct caixa {
    int valor;
};

Caixa* criar_caixa(int valorIncial){
    Caixa *c;

    c = (Caixa *)malloc(sizeof(Caixa));
    if(c == NULL){
        return NULL;
    }

    c->valor = valorIncial;
    return c;

}

int ler_valor(Caixa* c){
    if(c == NULL){
        return -1; // Retorna -1 para indicar erro
    }
    return c->valor;
}

void escrever_valor(Caixa* c,int valor){
    if(c == NULL){
        return;
    }
    c-> valor = valor;
}

void destruir_caixa(Caixa* c){
    if(c == NULL){
       return;
    }
     free(c);
}
