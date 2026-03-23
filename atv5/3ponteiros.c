#include <stdio.h>

// Definição da struct
struct Pessoa {
    char nome[100];
    char cpf[15];
    char sexo;
    int dia, mes, ano;
    float peso;
    float altura;
};

// Função para cadastrar pessoa
void cadastrarPessoa(struct Pessoa *p) {

    printf("\n=== Cadastro de Pessoa ===\n");

    printf("Nome: ");
    scanf(" %[^\n]", p->nome);

    printf("CPF: ");
    scanf("%s", p->cpf);

    printf("Sexo (M/F): ");
    scanf(" %c", &p->sexo);

    printf("Dia de nascimento: ");
    scanf("%d", &p->dia);

    printf("Mes de nascimento: ");
    scanf("%d", &p->mes);

    printf("Ano de nascimento: ");
    scanf("%d", &p->ano);

    printf("Peso (kg): ");
    scanf("%f", &p->peso);

    printf("Altura (m): ");
    scanf("%f", &p->altura);
}

// Função para mostrar dados
void mostrarPessoa(struct Pessoa *p) {

    printf("\n=== Dados Cadastrados ===\n");
    printf("Nome: %s\n", p->nome);
    printf("CPF: %s\n", p->cpf);
    printf("Sexo: %c\n", p->sexo);
    printf("Nascimento: %02d/%02d/%04d\n", p->dia, p->mes, p->ano);
    printf("Peso: %.2f kg\n", p->peso);
    printf("Altura: %.2f m\n", p->altura);
}

int main() {

    struct Pessoa pessoa;

    cadastrarPessoa(&pessoa);  // passando endereço da struct
    mostrarPessoa(&pessoa);

    return 0;
}


// crie um ponteiro de inteiro
int *ptr;