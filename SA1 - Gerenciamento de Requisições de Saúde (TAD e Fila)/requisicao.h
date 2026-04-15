#ifndef REQUISICAO_H
#define REQUISICAO_H
#define NOME_MAX       40
#define PROCEDIMENTO_MAX 10

/* Estrutura que representa uma requisicao de atendimento */
typedef struct {
    char nome_paciente[NOME_MAX];        /* Nome do paciente          */
    int  codigo_inscricao;               /* Codigo de inscricao unico */
    char codigo_procedimento[PROCEDIMENTO_MAX]; /* Codigo do procedimento    */
} Requisicao;

/* ---------- Assinaturas das funcoes ---------- */

/**
 * Cria e retorna uma Requisicao preenchida com os dados fornecidos.
 * Complexidade: O(1)
 */
Requisicao requisicao_criar(const char *nome, int codigo_inscricao,
                             const char *codigo_procedimento);

/**
 * Exibe os dados de uma requisicao na saida padrao.
 * Complexidade: O(1)
 */
void requisicao_exibir(const Requisicao *req);

#endif /* REQUISICAO_H */
