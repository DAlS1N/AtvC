#include <stdio.h>

int main() {
    int N, horas, minutos, segundos, resto;

    if (scanf("%d", &N) != 1) return 0;

    horas = N / 3600;
    resto = N % 3600;

    minutos = resto / 60;

    segundos = resto % 60;

    printf("%d:%d:%d\n", horas, minutos, segundos);

    return 0;
}