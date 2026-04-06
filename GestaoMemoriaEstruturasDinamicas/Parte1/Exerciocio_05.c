#include <stdio.h>

void dobrar(int *x) {
    *x = (*x) * 2;
}

int main() {

    int num;

    printf("Digite um numero: ");
    scanf("%d", &num);

    dobrar(&num);

    printf("Valor dobrado: %d\n", num);

    free(num);
    return 0;
}