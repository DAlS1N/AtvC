#include <stdio.h>

int main() {

    char nome[50];
    char data[20];
    double peso, altura;
    char cpf[15];
    char sexo;

    printf("Digite seu nome: \n");
    scanf("%s", nome);

    printf("Digite sua data de nascimento: \n");
    scanf("%s", data);

    printf("Digite seu peso: Ex: 70.5 \n");
    scanf("%lf", &peso);

    printf("Digite sua altura: Ex: 1.75 \n");
    scanf("%lf", &altura);

    printf("Digite seu CPF: \n");
    scanf("%s", cpf);

    printf("Digite seu sexo:M ou F \n");
    scanf(" %c", &sexo);

    printf("Seu nome e: %s\nvoce nasceu em: %s\nsua altura e de %.2lf\nseu peso e de: %.2lf\nseu CPF e: %s \ne por fim seu sexo e: %c\n", nome, data, altura, peso, cpf, sexo);

}