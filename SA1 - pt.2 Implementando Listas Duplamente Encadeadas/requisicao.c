#include <stdio.h>
#include <string.h>
#include "requisicao.h"

/* ----------------------------------------------------------
 * requisicao_criar
 * Preenche e retorna uma struct Requisicao por valor.
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
Requisicao requisicao_criar(const char *nome, int codigo_inscricao,
                             const char *codigo_procedimento)
{
    Requisicao req;

    strncpy(req.nome_paciente, nome, NOME_MAX - 1);
    req.nome_paciente[NOME_MAX - 1] = '\0';

    req.codigo_inscricao = codigo_inscricao;

    strncpy(req.codigo_procedimento, codigo_procedimento, PROCEDIMENTO_MAX - 1);
    req.codigo_procedimento[PROCEDIMENTO_MAX - 1] = '\0';

    return req;
}

/* ----------------------------------------------------------
 * requisicao_exibir
 * Imprime os campos de uma requisicao no terminal.
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
void requisicao_exibir(const Requisicao *req)
{
    if (req == NULL) {
        printf("[ERRO] Ponteiro de requisicao invalido.\n");
        return;
    }
    printf("  Paciente  : %s\n", req->nome_paciente);
    printf("  Inscricao : %d\n", req->codigo_inscricao);
    printf("  Proc.     : %s\n", req->codigo_procedimento);
}
