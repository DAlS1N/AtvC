#include <stdio.h>
#include <stdlib.h>

struct Aluno {
    char nome[100];
    float nota;
};

int main() {

    struct Aluno *alunos = (struct Aluno *) malloc(3 * sizeof(struct Aluno));

    for(int i = 0; i < 3; i++) {
        printf("Aluno %d\n", i + 1);

        printf("Nome: ");
       scanf("%s", (alunos + i)->nome);

        printf("Nota: ");
        scanf("%f", &(alunos + i)->nota);
    }

    printf("\nLista de Alunos\n");
    for(int i = 0; i < 3; i++) {
        printf("Nome: %s | Nota: %.2f\n", alunos[i].nome, alunos[i].nota);
    }

    free(alunos);

    return 0;
}