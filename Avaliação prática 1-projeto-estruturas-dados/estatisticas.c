#include <stdio.h>
#include <string.h>
#include "estatisticas.h"

// ============================================================
//  Estatísticas — implementação
// ============================================================

void estatisticas_exibir(const Lista *historico) {
    int total      = 0;
    int atendidos  = 0;
    int cancelados = 0;
    int abertos    = 0;
    int baixa      = 0;
    int media      = 0;
    int alta       = 0;

    NoLista *atual = historico->cabeca;
    while (atual != NULL) {
        total++;
        if (strcmp(atual->dado.status, "atendido")  == 0) atendidos++;
        if (strcmp(atual->dado.status, "cancelado") == 0) cancelados++;
        if (strcmp(atual->dado.status, "aberto")    == 0) abertos++;
        if (atual->dado.prioridade == 1) baixa++;
        if (atual->dado.prioridade == 2) media++;
        if (atual->dado.prioridade == 3) alta++;
        atual = atual->proximo;
    }

    printf("  === Estatisticas do Sistema ===\n");
    printf("  Total de atendimentos : %d\n", total);
    printf("  Abertos               : %d\n", abertos);
    printf("  Atendidos             : %d\n", atendidos);
    printf("  Cancelados            : %d\n", cancelados);
    printf("  ---------------------------\n");
    printf("  Por prioridade:\n");
    printf("    Alta  (3): %d\n", alta);
    printf("    Media (2): %d\n", media);
    printf("    Baixa (1): %d\n", baixa);
}

void estatisticas_categoria_top(const Lista *historico) {
    // Abordagem simples: array de categorias únicas + contagem
    char categorias[100][30];
    int  contagens[100];
    int  num_categorias = 0;

    NoLista *atual = historico->cabeca;
    while (atual != NULL) {
        const char *cat = atual->dado.categoria;
        int encontrou = 0;
        for (int i = 0; i < num_categorias; i++) {
            if (strcmp(categorias[i], cat) == 0) {
                contagens[i]++;
                encontrou = 1;
                break;
            }
        }
        if (!encontrou && num_categorias < 100) {
            strncpy(categorias[num_categorias], cat, 29);
            categorias[num_categorias][29] = '\0';
            contagens[num_categorias] = 1;
            num_categorias++;
        }
        atual = atual->proximo;
    }

    if (num_categorias == 0) {
        printf("  Sem atendimentos registrados.\n");
        return;
    }

    int idx_max = 0;
    for (int i = 1; i < num_categorias; i++)
        if (contagens[i] > contagens[idx_max])
            idx_max = i;

    printf("  Categoria com mais atendimentos: %s (%d)\n",
           categorias[idx_max], contagens[idx_max]);
}
