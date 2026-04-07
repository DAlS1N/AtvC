#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *proximo;
} No;

typedef struct
{
    No *topo;
    int quantidade;
} Pilha;


void inicializar(Pilha *p){
    p->topo = NULL;
    p->quantidade = 0;
}

int push(Pilha *p, int valor){
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Sem memoria disponivel,libere espaço e tente novamente");
       return 0;
    }

    novo->valor = valor;
    novo->proximo = p->topo;

    //salvou o topo
    p->topo = novo;
    p->quantidade++;
    return 1;
}

int pop(Pilha *p, int *valor){
    No *temp;
    
    if(p->topo == NULL){
        printf("Pilha vazia, pulando pop");
        return 0;
    }

    temp = p->topo;


    *valor = temp->valor;
    p->topo = temp->proximo;


    free(temp);

    p->quantidade--;

    return 1;
}


int main()
{


    Pilha p;
    int removido;

    inicializar(&p);

       push(&p,10);
       push(&p,20);
       push(&p,30);
       push(&p,40);
       push(&p,50);
       push(&p,60);

    
       while(pop(&p,&removido)){
           printf("Valor removido: %d\n",removido);
       }

   

    return 0;
}