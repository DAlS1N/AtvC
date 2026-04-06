#include <stdio.h>
#include <stdlib.h>

// Vetores Dinâmicos: Peça ao usuário um tamanho N,
// aloque um vetor de inteiros, preencha-o e calcule a média aritmética. Use sizeof(int) para garantir a portabilidade.

int main()
{
    int *vetor;
    int i;
    int capacidade;
    int soma;
    double media;

    printf("Digite a capacidade do vetor: ");
    scanf("%d", &capacidade);

    vetor = (int *)malloc(capacidade * sizeof(int));

    if (vetor == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    PreencherVetor(vetor, capacidade);

    printf("somar vetor:\n");
    for (i = 0; i < capacidade; i++)
    {
        soma += vetor[i];
        printf("%d ", soma);
    }

    media = soma/capacidade;

    printf("\nMedia: %.2f", media);


    printf("\n");

    free(vetor);
}

int PreencherVetor(int *vetor, int capacidade) 
{
    for (int i = 0; i < capacidade; i++) 
    {
        printf("Digite um valor para a posicao %d: ", i);
        // Passa o endereço da posição i diretamente
        scanf("%d", &vetor[i]); 
    }
    return 0;
}