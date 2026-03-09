#include <stdio.h>

int main() {
    
    double A, B, C;
    double triangulo, circulo, trapezio, quadrado, retangulo;
    double pi = 3.14159;


    if (scanf("%lf %lf %lf", &A, &B, &C) != 3) return 0;

    // Cálculos das áreas
    triangulo = (A * C) / 2.0;
    circulo = pi * (C * C);
    trapezio = ((A + B) * C) / 2.0;
    quadrado = B * B;
    retangulo = A * B;

    printf("TRIANGULO: %.3f\n", triangulo);
    printf("CIRCULO: %.3f\n", circulo);
    printf("TRAPEZIO: %.3f\n", trapezio);
    printf("QUADRADO: %.3f\n", quadrado);
    printf("RETANGULO: %.3f\n", retangulo);

    return 0;
}