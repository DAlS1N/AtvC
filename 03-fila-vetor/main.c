#include <stdio.h>

int main() {

    int fila[5];
    int tamanho = 0;
    int i;

    fila[tamanho] = 10;
    tamanho++;

    fila[tamanho] = 20;
    tamanho++;

    fila[tamanho] = 30;
    tamanho++;  


    printf("Fila antes da remoção:\n");
    for(i = 0; i < tamanho; i++) {
        printf("%d ", fila[i]);
    }  
    printf("\n");

    printf("Removendo o primeiro elemento da fila: %d\n", fila[0]);

    for(i = 1; i < tamanho; i++) {
        fila[i - 1] = fila[i];
    }
    tamanho--;

    printf("Fila após a remoção:\n");
        for(i = 0; i < tamanho; i++) {
        printf("%d ", fila[i]);
    }  
    printf("\n");


}