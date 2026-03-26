#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor;
    int i;
    int capacidade;

    printf("Digite a capacidade do vetor: ");
    scanf("%d", &capacidade);

    vetor = (int *)malloc(capacidade * sizeof(int));

    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    PrencherVetor(vetor, capacidade);

    printf("Coneteudo do vetor:\n");
       for(i = 0; i < capacidade; i++) {
        printf("%d ", vetor[i]);
       }
    printf("\n");

    free(vetor);
}

int PrencherVetor(int *vetor, int capacidade) {
        for(int i = 0; i < capacidade; i++) {
        vetor[i] = (i + 1) * 10; // Preenche o vetor com valores (10, 20, 30, ...)
    }
    return 0;
    
}