#include <stdio.h>
#include "lista.h"

/* Utilitário para separar seções no terminal */
static void secao(const char *titulo) {
    printf("\n========================================\n");
    printf(" %s\n", titulo);
    printf("========================================\n");
}

int main(void) {

    /* --------------------------------------------------
       Exercicio 2 — Criar lista e funções base
       -------------------------------------------------- */
    secao("Exercicio 2: Criar lista");
    Lista *l = criar_lista();
    printf("Lista criada. Vazia? %s | Tamanho: %d\n",
           esta_vazia(l) ? "Sim" : "Nao", tamanho_lista(l));

    /* --------------------------------------------------
       Exercicio 3 — Inserção no início
       -------------------------------------------------- */
    secao("Exercicio 3: Insercao no inicio");
    inserir_inicio(l, 30);
    inserir_inicio(l, 20);
    inserir_inicio(l, 10);
    printf("Apos inserir 10, 20, 30 no inicio:\n");
    imprimir_inicio_fim(l);   /* antecipa Ex.5 para visualizar */
    printf("Tamanho: %d\n", tamanho_lista(l));

    /* --------------------------------------------------
       Exercicio 4 — Inserção no fim
       -------------------------------------------------- */
    secao("Exercicio 4: Insercao no fim");
    inserir_fim(l, 40);
    inserir_fim(l, 50);
    printf("Apos inserir 40, 50 no fim:\n");
    imprimir_inicio_fim(l);
    printf("Tamanho: %d\n", tamanho_lista(l));

    /* --------------------------------------------------
       Exercicio 5 — Impressão bidirecional
       -------------------------------------------------- */
    secao("Exercicio 5: Impressao bidirecional");
    printf("Inicio para fim:\n");
    imprimir_inicio_fim(l);
    printf("Fim para inicio:\n");
    imprimir_fim_inicio(l);

    /* --------------------------------------------------
       Exercicio 6 — Remoção do início
       -------------------------------------------------- */
    secao("Exercicio 6: Remocao do inicio");
    int removido;
    remover_inicio(l, &removido);
    printf("Valor removido do inicio: %d\n", removido);
    printf("Lista apos remocao:\n");
    imprimir_inicio_fim(l);

    /* --------------------------------------------------
       Exercicio 7 — Remoção do fim
       -------------------------------------------------- */
    secao("Exercicio 7: Remocao do fim");
    remover_fim(l, &removido);
    printf("Valor removido do fim: %d\n", removido);
    printf("Lista apos remocao:\n");
    imprimir_inicio_fim(l);

    /* --------------------------------------------------
       Exercicio 8 — Busca por valor
       -------------------------------------------------- */
    secao("Exercicio 8: Busca por valor");
    /* lista atual: 20 30 40 */
    Nodo *encontrado = buscar(l, 30);
    if (encontrado != NULL)
        printf("buscar(30): encontrado -> valor = %d\n", obter_valor(encontrado));
    else
        printf("buscar(30): NAO encontrado\n");

    encontrado = buscar(l, 99);
    if (encontrado != NULL)
        printf("buscar(99): encontrado -> valor = %d\n", obter_valor(encontrado));
    else
        printf("buscar(99): NAO encontrado (NULL)\n");

    /* --------------------------------------------------
       Exercicio 9 — Inserção em posição específica
       -------------------------------------------------- */
    secao("Exercicio 9: Insercao em posicao especifica");
    /* lista: 20 30 40 */
    printf("Lista antes:\n");
    imprimir_inicio_fim(l);

    inserir_posicao(l, 25, 1);  /* entre 20 e 30 */
    printf("Apos inserir_posicao(25, 1):\n");
    imprimir_inicio_fim(l);     /* esperado: 20 25 30 40 */

    inserir_posicao(l, 10, 0);  /* inicio */
    printf("Apos inserir_posicao(10, 0) [inicio]:\n");
    imprimir_inicio_fim(l);     /* esperado: 10 20 25 30 40 */

    inserir_posicao(l, 50, tamanho_lista(l));  /* fim */
    printf("Apos inserir_posicao(50, tamanho) [fim]:\n");
    imprimir_inicio_fim(l);     /* esperado: 10 20 25 30 40 50 */

    inserir_posicao(l, 999, 99); /* posicao invalida */

    /* --------------------------------------------------
       Exercicio 10 — Remoção por valor
       -------------------------------------------------- */
    secao("Exercicio 10: Remocao por valor");
    /* lista: 10 20 25 30 40 50 */
    printf("Lista antes:\n");
    imprimir_inicio_fim(l);

    remover_valor(l, 25);  /* meio */
    printf("Apos remover_valor(25) [meio]:\n");
    imprimir_inicio_fim(l);

    remover_valor(l, 10);  /* inicio */
    printf("Apos remover_valor(10) [inicio]:\n");
    imprimir_inicio_fim(l);

    remover_valor(l, 50);  /* fim */
    printf("Apos remover_valor(50) [fim]:\n");
    imprimir_inicio_fim(l);

    remover_valor(l, 999); /* valor inexistente */

    printf("\nLista final:\n");
    imprimir_inicio_fim(l);
    printf("Tamanho: %d\n", tamanho_lista(l));

    destruir_lista(l);
    printf("\nLista destruida com sucesso.\n");
    return 0;
}
