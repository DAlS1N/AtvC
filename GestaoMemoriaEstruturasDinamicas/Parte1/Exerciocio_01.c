#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Alocação Simples: Declare um ponteiro para float, aloque memória dinamicamente,
    // receba um valor via teclado e exiba-o com duas casas decimais .
    float *ponteiro;

    ponteiro = (float *)malloc(sizeof(float));

    
    printf("Digite um valor: ");
    scanf("%f", ponteiro);


    printf("Valor digitado: %.2f\n", *ponteiro);
    printf("Endereço de memória alocado: %p\n", (void *)ponteiro);

    free(ponteiro);
    return 0;
}