#include <stdio.h>
#include <stdlib.h>
#define CAPACIDADE 5

    int pilha[CAPACIDADE];
    int topo = -1;


int push(int valor){

    if(topo == CAPACIDADE - 1){
        printf("Capacidade excedida. Retornando\n");
        return 0;
    }

    pilha[++topo] = valor;
    return 1;

}


int pop(int *valor){
    if (topo == -1){
        printf("Todos os elementos foram retirados");
        return 0;
    }

    *valor = pilha[topo--];
    return 1;
}


int main() {
  
    int removido;

    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60);

    while(pop(&removido)){
        printf("Valor removido: %d\n",removido);
    }


 
    return 0;
}