#include <stdio.h>

int main() {
    int tempo, velocidade;
    double distancia, litros;

    if (scanf("%d %d", &tempo, &velocidade) != 2) return 0;

    distancia = (double)tempo * velocidade;

    litros = distancia / 12.0;

    printf("%.3f\n", litros);

    return 0;
}