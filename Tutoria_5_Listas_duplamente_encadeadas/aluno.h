#ifndef ALUNO_H
#define ALUNO_H

/* =======================================================
   Desafio Extra — Lista duplamente encadeada de Alunos
   ======================================================= */

#define NOME_MAX 50

typedef struct {
    int   matricula;
    char  nome[NOME_MAX];
    float media;
} Aluno;

/* Nodo especializado para armazenar Aluno */
typedef struct NodoAluno {
    Aluno           dado;
    struct NodoAluno *anterior;
    struct NodoAluno *proximo;
} NodoAluno;

typedef struct {
    NodoAluno *inicio;
    NodoAluno *fim;
    int        tamanho;
} ListaAluno;

/* --- Funções da lista ----------------------------------- */
ListaAluno* criar_lista_aluno(void);
void        destruir_lista_aluno(ListaAluno *lista);
int         esta_vazia_aluno(ListaAluno *lista);

int      inserir_aluno_inicio(ListaAluno *lista, Aluno aluno);
int      inserir_aluno_fim   (ListaAluno *lista, Aluno aluno);

NodoAluno* buscar_por_matricula  (ListaAluno *lista, int matricula);
int        remover_por_matricula (ListaAluno *lista, int matricula);

void imprimir_aprovados (ListaAluno *lista);  /* media >= 7.0 */
void imprimir_reprovados(ListaAluno *lista);  /* media <  7.0 */
void imprimir_todos     (ListaAluno *lista);

#endif
