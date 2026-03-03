#include <stdio.h>

#define FATOR 10

int main() {
    int numero;

    printf("Digite um número: ");
    scanf("%d", &numero);

    printf("Resultado: %d\n", numero * FATOR);

    return 0;
}