#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Usuario
{

    char *nome;
};

int main()
{

    // Strings Dinâmicas: Crie uma struct Usuario que contenha um ponteiro char *nome.
    // Aloque a struct e depois aloque o espaço exato para o nome lido do teclado usando strlen.

    struct Usuario *user;

    user = (struct Usuario *) malloc(sizeof(struct Usuario));

    char buffer[100];

    printf("Digite seu nome:\n");
    scanf("%s",buffer);
     
    user->nome = (char *) malloc(strlen(buffer) + 1);

    strcpy(user->nome, buffer);

    printf("Nome armazenado: %s\n", user->nome);

    free(user->nome);
    free(user);

    return 0;

}