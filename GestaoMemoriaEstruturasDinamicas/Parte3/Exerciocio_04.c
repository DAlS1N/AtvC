#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    // Vetor de Strings: Aloque um vetor de ponteiros para char para armazenar uma lista de nomes de cidades informada pelo usuário .
    int n;

    printf("Quantas cidades deseja cadastrar? ");
    scanf("%d", &n);

    char **cidades = (char **)malloc(n * sizeof(char *));

    char buffer[100];

    for (int i = 0; i < n; i++)
    {
        printf("Cidade %d: ", i + 1);
        scanf("%s", buffer);

        cidades[i] = (char *)malloc(strlen(buffer) + 1);

        strcpy(cidades[i], buffer);
    }

    printf("\nLista de cidades:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", cidades[i]);
    }

    for (int i = 0; i < n; i++)
    {
        free(cidades[i]);
    }
    free(cidades);

    return 0;
}