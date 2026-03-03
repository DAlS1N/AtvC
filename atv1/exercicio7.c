#include <stdio.h>

int main() {
    float n1 = 7.5, n2 = 6.0, n3 = 8.0;
    float media = (n1 + n2 + n3) / 3;

    printf("Média: %.2f\n", media);

    if (media >= 6.0) {
        printf("Aprovado\n");
    } else {
        printf("Reprovado\n");
    }

    return 0;
}