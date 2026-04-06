#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Endereco {
    char rua[100];
    int numero;
};

struct Pessoa {
    char nome[100];
    struct Endereco *endereco; 
};

int main() {

    struct Pessoa *p = (struct Pessoa *) malloc(sizeof(struct Pessoa));

    p->endereco = (struct Endereco *) malloc(sizeof(struct Endereco));

    printf("Digite o nome: ");
    scanf("%s", p->nome);

    printf("Digite a rua: ");
    scanf("%s", p->endereco->rua);

    printf("Digite o numero: ");
    scanf("%d", &p->endereco->numero);

    printf("\n--- Dados da Pessoa ---\n");
    printf("Nome: %s\n", p->nome);
    printf("Rua: %s\n", p->endereco->rua);
    printf("Numero: %d\n", p->endereco->numero);
    
    free(p->endereco);
    free(p);

    return 0;
}