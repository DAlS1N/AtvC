#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[50];
    float nota;
} Aluno;

int main()
{

    // Filtragem: Dado um vetor de alunos,
    // gere um novo vetor dinâmico contendo apenas os endereços dos alunos aprovados (nota > 7.0) .

    Aluno turma[] = {
        {"Alice", 8.5}, {"Bob", 6.0}, {"Charlie", 9.2}, {"David", 5.5}};
    int tamOriginal = 4;

    int qtdAprovados = 0;
    for (int i = 0; i < tamOriginal; i++)
    {
        if (turma[i].nota > 7.0)
        {
            qtdAprovados++;
        }
    }

    Aluno **aprovados = (Aluno **)malloc(qtdAprovados * sizeof(Aluno *));

    if (aprovados == NULL)
    {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    int j = 0;
    for (int i = 0; i < tamOriginal; i++)
    {
        if (turma[i].nota > 7.0)
        {
            aprovados[j] = &turma[i];
            j++;
        }
    }

    printf("--- Lista de Aprovados ---\n");
    for (int i = 0; i < qtdAprovados; i++)
    {
        printf("Nome: %-10s | Nota: %.1f | Endereco: %p\n",
               aprovados[i]->nome, aprovados[i]->nota, (void *)aprovados[i]);
    }

    free(aprovados);

    return 0;
}