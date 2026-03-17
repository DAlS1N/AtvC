#include <stdio.h>

int a = 10;
int *ptra = &a;



struct pessoa {

    char nome[50];
    char data[20];
    double peso, altura;
    char cpf[15];
    char sexo;
};


int main() {

    struct pessoa Strpessoa;

    printf("Digite seu nome: \n");
    scanf("%s", Strpessoa.nome);

    printf("Digite sua data de nascimento: \n");
    scanf("%s", Strpessoa.data);

    printf("Digite seu peso: Ex: 70.5 \n");
    scanf("%lf", &Strpessoa.peso);

    printf("Digite sua altura: Ex: 1.75 \n");
    scanf("%lf", &Strpessoa.altura);

    printf("Digite seu CPF: \n");
    scanf("%s", Strpessoa.cpf);

    printf("Digite seu sexo:M ou F \n");
    scanf(" %c", &Strpessoa.sexo);

    printf("Seu nome e: %s\nvoce nasceu em: %s\nsua altura e de %.2lf\nseu peso e de: %.2lf\nseu CPF e: %s \ne por fim seu sexo e: %c\n", Strpessoa.nome, Strpessoa.data, Strpessoa.altura, Strpessoa.peso, Strpessoa.cpf, Strpessoa.sexo);

}

