#include <stdio.h>

int main() {
    int valor, resto, atual;

    if (scanf("%d", &valor) != 1) return 0;

    printf("%d\n", valor);

    atual = valor;

    // Notas de 100
    printf("%d nota(s) de R$ 100,00\n", atual / 100);
    atual = atual % 100;

    // Notas de 50
    printf("%d nota(s) de R$ 50,00\n", atual / 50);
    atual = atual % 50;

    // Notas de 20
    printf("%d nota(s) de R$ 20,00\n", atual / 20);
    atual = atual % 20;

    // Notas de 10
    printf("%d nota(s) de R$ 10,00\n", atual / 10);
    atual = atual % 10;

    // Notas de 5
    printf("%d nota(s) de R$ 5,00\n", atual / 5);
    atual = atual % 5;

    // Notas de 2
    printf("%d nota(s) de R$ 2,00\n", atual / 2);
    atual = atual % 2;

    // Notas de 1
    printf("%d nota(s) de R$ 1,00\n", atual / 1);

    return 0;
}