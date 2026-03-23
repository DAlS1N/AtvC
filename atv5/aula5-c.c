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
    scanf("%s", p->nome);


    printf("Digite sua data de nascimento: \n");
    scanf("%d/%d/%d", &p->dia, &p->mes, &p->ano);

    printf("Digite seu peso: Ex: 70.5 \n");
    scanf("%f", &p->peso);

    printf("Digite sua altura: Ex: 1.75 \n");
    scanf("%f", &p->altura);

    printf("Digite seu CPF: \n");
    scanf("%s", p->cpf);

    printf("Digite seu sexo:M ou F \n");
    scanf(" %c", &p->sexo);

   
}


void mostrarPessoa(struct pessoa *p) {

 printf("Seu nome e: %s\nvoce nasceu em: %d/%d/%d\nsua altura e de %.2f\nseu peso e de: %.2f\nseu CPF e: %s \ne por fim seu sexo e: %c\n", p->nome, p->dia, p->mes, p->ano, p->altura, p->peso, p->cpf, p->sexo);

}


int main() {

    struct pessoa Strpessoa;

    cadastrarPessoa(&Strpessoa);
    mostrarPessoa(&Strpessoa);

    return 0;
} 