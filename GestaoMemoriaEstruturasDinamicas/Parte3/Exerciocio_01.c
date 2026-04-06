#include <stdio.h>
#include <stdlib.h>

int main() {

    //Redimensionamento: Aloque um vetor para 2 inteiros. 
    //Use realloc para expandir o tamanho para 4 inteiros conforme o usuário insere novos dados .
    int *vetor;
    
    vetor = (int *) malloc(2 * sizeof(int));

    for(int i = 0; i < 2; i++) {
        printf("Digite um valor: ");
        scanf("%d", &vetor[i]);
    }

    vetor = (int *) realloc(vetor, 4 * sizeof(int));

    for(int i = 2; i < 4; i++) {
        printf("Digite mais um valor: ");
        scanf("%d", &vetor[i]);
    }

    printf("\nValores no vetor:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d ", vetor[i]);
    }

    free(vetor);

    return 0;
}