#include <stdio.h>

int main() {
    int numero, horas;
    double valorPorHora, salario;

    scanf("%d %d %lf", &numero, &horas, &valorPorHora);

    salario = horas * valorPorHora;

    printf("NUMBER = %d\n", numero);
    printf("SALARY = U$ %.2lf\n", salario);

    return 0;
}
