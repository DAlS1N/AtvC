#include <stdio.h>
#include <stdlib.h>

int main() {

    int pilha[5];
    int indiceTopo = -1;

    pilha[++indiceTopo] = 10;
    pilha[++indiceTopo] = 20;
    pilha[++indiceTopo] = 30;
    pilha[++indiceTopo] = 40;
    pilha[++indiceTopo] = 50;

    printf("Topo atual: %d\n", pilha[indiceTopo]);

    printf("Removendo: %d\n", pilha[indiceTopo--]);

    printf("Novo topo: %d",pilha[indiceTopo]);

    return 0;
}