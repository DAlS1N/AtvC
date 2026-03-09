#include <stdio.h>

int main() {
    char nome[50];
    double salarioFixo, totalVendas, totalReceber;
    
    scanf("%s", nome);
    scanf("%lf %lf", &salarioFixo, &totalVendas);

    totalReceber = salarioFixo + (totalVendas * 0.15);

    printf("TOTAL = R$ %.2lf\n", totalReceber);

    return 0;
}
