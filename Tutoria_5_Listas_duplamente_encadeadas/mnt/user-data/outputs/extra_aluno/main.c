#include <stdio.h>
#include <string.h>
#include "aluno.h"

static void secao(const char *titulo) {
    printf("\n========================================\n");
    printf(" %s\n", titulo);
    printf("========================================\n");
}

/* Monta uma Aluno de forma legível no main */
static Aluno make_aluno(int mat, const char *nome, float media) {
    Aluno a;
    a.matricula = mat;
    strncpy(a.nome, nome, NOME_MAX - 1);
    a.nome[NOME_MAX - 1] = '\0';
    a.media = media;
    return a;
}

int main(void) {
    ListaAluno *lista = criar_lista_aluno();

    /* --------------------------------------------------
       Inserções
       -------------------------------------------------- */
    secao("Desafio Extra: Inserindo alunos");

    inserir_aluno_fim(lista, make_aluno(1001, "Ana Lima",       8.5f));
    inserir_aluno_fim(lista, make_aluno(1002, "Bruno Souza",    5.0f));
    inserir_aluno_fim(lista, make_aluno(1003, "Carla Pereira",  7.0f));
    inserir_aluno_fim(lista, make_aluno(1004, "Diego Martins",  4.2f));
    inserir_aluno_fim(lista, make_aluno(1005, "Elisa Campos",   9.1f));

    inserir_aluno_inicio(lista, make_aluno(1000, "Aldo Ferreira", 6.9f));

    printf("Todos os alunos cadastrados:\n");
    imprimir_todos(lista);

    /* --------------------------------------------------
       Busca por matrícula
       -------------------------------------------------- */
    secao("Busca por matricula");
    NodoAluno *achou = buscar_por_matricula(lista, 1003);
    if (achou)
        printf("Encontrado: %s (media %.1f)\n",
               achou->dado.nome, achou->dado.media);

    achou = buscar_por_matricula(lista, 9999);
    if (!achou)
        printf("Matricula 9999: nao encontrada.\n");

    /* --------------------------------------------------
       Remoção por matrícula
       -------------------------------------------------- */
    secao("Remocao por matricula (1002 - Bruno)");
    remover_por_matricula(lista, 1002);
    printf("Apos remocao:\n");
    imprimir_todos(lista);

    /* --------------------------------------------------
       Aprovados e reprovados
       -------------------------------------------------- */
    secao("Aprovados (media >= 7.0)");
    imprimir_aprovados(lista);

    secao("Reprovados (media < 7.0)");
    imprimir_reprovados(lista);

    destruir_lista_aluno(lista);
    printf("\nLista de alunos destruida.\n");
    return 0;
}
