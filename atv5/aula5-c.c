#include <stdio.h>

struct pessoa {
    char nome[50];
    int dia, mes, ano;
    float peso, altura;
    char cpf[15];
    char sexo;
};


void cadastrarPessoa(struct pessoa *p) {

    printf("Digite seu nome: \n");
    scanf("%s", Strpessoa.nome);


    printf("Digite sua data de nascimento: \n");
    scanf("%d/%d/%d", &Strpessoa.dia, &Strpessoa.mes, &Strpessoa.ano);

    printf("Digite seu peso: Ex: 70.5 \n");
    scanf("%lf", &Strpessoa.peso);

    printf("Digite sua altura: Ex: 1.75 \n");
    scanf("%lf", &Strpessoa.altura);

    printf("Digite seu CPF: \n");
    scanf("%s", Strpessoa.cpf);

    printf("Digite seu sexo:M ou F \n");
    scanf(" %c", &Strpessoa.sexo);

    printf("Seu nome e: %s\nvoce nasceu em: %d/%d/%d\nsua altura e de %.2f\nseu peso e de: %.2f\nseu CPF e: %s \ne por fim seu sexo e: %c\n", Strpessoa.nome, Strpessoa.dia, Strpessoa.mes, Strpessoa.ano, Strpessoa.altura, Strpessoa.peso, Strpessoa.cpf, Strpessoa.sexo);

}
