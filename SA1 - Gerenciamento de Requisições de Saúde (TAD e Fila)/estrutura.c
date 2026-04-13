#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

/* ----------------------------------------------------------
 * fila_inicializar
 * Prepara a struct Fila para uso, zerando todos os campos.
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
void fila_inicializar(Fila *f)
{
    if (f == NULL) return;
    f->head    = NULL;
    f->tail    = NULL;
    f->tamanho = 0;
}

/* ----------------------------------------------------------
 * fila_inserir  (enqueue)
 * Aloca um novo no, copia a requisicao e o anexa ao tail.
 * Como guardamos o ponteiro do tail, nao precisamos percorrer
 * a lista — operacao garantidamente O(1).
 *
 * Retorno: 1 = sucesso | 0 = falha de alocacao
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
int fila_inserir(Fila *f, Requisicao req)
{
    if (f == NULL) return 0;

    /* Aloca o novo no com sizeof para portabilidade */
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        /* malloc retornou NULL: sem memoria disponivel */
        fprintf(stderr, "[ERRO] fila_inserir: falha ao alocar memoria.\n");
        return 0;
    }

    novo->dado = req;   /* Copia a requisicao por valor */
    novo->prox = NULL;  /* Novo no sera sempre o ultimo */

    if (fila_vazia(f)) {
        /* Fila estava vazia: head e tail apontam para o unico no */
        f->head = novo;
        f->tail = novo;
    } else {
        /* Encadeia o novo no apos o atual tail e atualiza tail */
        f->tail->prox = novo;
        f->tail        = novo;
    }

    f->tamanho++;
    return 1;
}

/* ----------------------------------------------------------
 * fila_remover  (dequeue)
 * Remove o no do head, opcionalmente entrega os dados ao
 * chamador via ponteiro e libera a memoria com free().
 *
 * Retorno: 1 = sucesso | 0 = fila vazia
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
int fila_remover(Fila *f, Requisicao *removida)
{
    if (f == NULL || fila_vazia(f)) {
        fprintf(stderr, "[AVISO] fila_remover: fila vazia ou invalida.\n");
        return 0;
    }

    No *saindo = f->head;           /* No que sera removido             */

    /* Entrega os dados ao chamador antes de liberar a memoria */
    if (removida != NULL) {
        *removida = saindo->dado;
    }

    f->head = saindo->prox;         /* Avanca o head para o proximo no  */

    /* Se a fila ficou vazia, tail tambem deve ser nulo */
    if (f->head == NULL) {
        f->tail = NULL;
    }

    free(saindo);                   /* Libera a memoria do no removido   */
    f->tamanho--;
    return 1;
}

/* ----------------------------------------------------------
 * fila_tamanho
 * Retorna o campo tamanho mantido em O(1) a cada insercao
 * e remocao — evita percorrer a lista para contar.
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
int fila_tamanho(const Fila *f)
{
    if (f == NULL) return 0;
    return f->tamanho;
}

/* ----------------------------------------------------------
 * fila_vazia
 * Verifica se nao ha requisicoes na fila.
 * Complexidade: O(1)
 * ---------------------------------------------------------- */
int fila_vazia(const Fila *f)
{
    if (f == NULL) return 1;
    return (f->tamanho == 0);
}

/* ----------------------------------------------------------
 * fila_destruir
 * Percorre todos os nos e os libera com free().
 * Ao final, recoloca a fila no estado inicializado.
 * Essencial para evitar memory leaks ao encerrar o programa.
 * Complexidade: O(n)
 * ---------------------------------------------------------- */
void fila_destruir(Fila *f)
{
    if (f == NULL) return;

    No *atual = f->head;
    while (atual != NULL) {
        No *proximo = atual->prox;  /* Guarda referencia antes do free */
        free(atual);
        atual = proximo;
    }

    /* Reinicia os campos — fila pronta para ser reutilizada */
    f->head    = NULL;
    f->tail    = NULL;
    f->tamanho = 0;
}

/* ----------------------------------------------------------
 * fila_exibir
 * Percorre a fila do head ao tail sem modificar a estrutura.
 * Util para depuracao e monitoramento administrativo.
 * Complexidade: O(n)
 * ---------------------------------------------------------- */
void fila_exibir(const Fila *f)
{
    if (f == NULL || fila_vazia(f)) {
        printf("[FILA] Nenhuma requisicao aguardando.\n");
        return;
    }

    printf("  FILA DE ATENDIMENTO — %d paciente(s)\n", f->tamanho);

    const No *atual = f->head;
    int posicao = 1;
    while (atual != NULL) {
        printf("  [%d] ------------------------------------\n", posicao++);
        requisicao_exibir(&atual->dado);
        atual = atual->prox;
    }
    printf("========================================\n");
}
