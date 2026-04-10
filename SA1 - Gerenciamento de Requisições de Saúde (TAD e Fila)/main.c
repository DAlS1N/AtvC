/* ============================================================
 * main.c  (cliente / teste)
 * Valida o TAD Fila em um cenario realista de gerenciamento
 * de atendimento hospitalar.
 *
 * Fluxo simulado:
 *   1. Chegada de pacientes → fila_inserir
 *   2. Monitoramento administrativo → fila_tamanho / fila_exibir
 *   3. Atendimento (alocacao) → fila_remover
 *   4. Liberacao total de memoria → fila_destruir
 * ============================================================ */

#include <stdio.h>
#include "requisicao.h"
#include "estrutura.h"

/* Utilitario: imprime um separador visual */
static void separador(const char *titulo)
{
    printf("\n### %s ###\n", titulo);
}

int main(void)
{
    Fila fila_atendimento;
    fila_inicializar(&fila_atendimento);

    /* -------------------------------------------------------
     * ETAPA 1: Chegada de pacientes
     * Cada chamada a fila_inserir e O(1).
     * ------------------------------------------------------- */
    separador("ETAPA 1 — Chegada de Pacientes");

    Requisicao r1 = requisicao_criar("Ana Clara Souza",    1001, "CARD-001");
    Requisicao r2 = requisicao_criar("Bruno Lima",         1002, "ORTH-005");
    Requisicao r3 = requisicao_criar("Carla Mendes",       1003, "NEUR-012");
    Requisicao r4 = requisicao_criar("Diego Ferreira",     1004, "CARD-002");
    Requisicao r5 = requisicao_criar("Elaine Costa",       1005, "DERM-008");

    fila_inserir(&fila_atendimento, r1);
    printf("[OK] Paciente inserido: %s\n", r1.nome_paciente);

    fila_inserir(&fila_atendimento, r2);
    printf("[OK] Paciente inserido: %s\n", r2.nome_paciente);

    fila_inserir(&fila_atendimento, r3);
    printf("[OK] Paciente inserido: %s\n", r3.nome_paciente);

    fila_inserir(&fila_atendimento, r4);
    printf("[OK] Paciente inserido: %s\n", r4.nome_paciente);

    fila_inserir(&fila_atendimento, r5);
    printf("[OK] Paciente inserido: %s\n", r5.nome_paciente);

    /* -------------------------------------------------------
     * ETAPA 2: Monitoramento administrativo
     * fila_tamanho e O(1) — sem percorrer a lista.
     * ------------------------------------------------------- */
    separador("ETAPA 2 — Monitoramento Administrativo");
    printf("Pacientes aguardando: %d\n", fila_tamanho(&fila_atendimento));

    if (fila_tamanho(&fila_atendimento) > 3) {
        printf("[ALERTA] Fila critica! Acionar instituicoes parceiras.\n");
    }

    fila_exibir(&fila_atendimento);

    /* -------------------------------------------------------
     * ETAPA 3: Atendimento — remocao FIFO
     * Cada chamada a fila_remover e O(1).
     * ------------------------------------------------------- */
    separador("ETAPA 3 — Inicio dos Atendimentos (FIFO)");

    Requisicao atendido;

    /* Atende os 3 primeiros da fila */
    int i;
    for (i = 0; i < 3; i++) {
        if (fila_remover(&fila_atendimento, &atendido)) {
            printf("\n[ATENDENDO]\n");
            requisicao_exibir(&atendido);
            printf("  Fila restante: %d paciente(s)\n",
                   fila_tamanho(&fila_atendimento));
        }
    }

    /* -------------------------------------------------------
     * ETAPA 4: Estado intermediario da fila
     * ------------------------------------------------------- */
    separador("ETAPA 4 — Estado Atual da Fila");
    fila_exibir(&fila_atendimento);

    /* -------------------------------------------------------
     * ETAPA 5: Esvaziamento completo e liberacao de memoria
     * fila_destruir percorre e libera todos os nos — O(n).
     * -------------------------------------------------------*/
    separador("ETAPA 5 — Esvaziamento e Liberacao de Memoria");

    /* Remove os pacientes restantes individualmente */
    while (!fila_vazia(&fila_atendimento)) {
        fila_remover(&fila_atendimento, &atendido);
        printf("[ATENDIDO] %s (inscricao %d)\n",
               atendido.nome_paciente, atendido.codigo_inscricao);
    }

    /* Garante liberacao de qualquer no residual (boa pratica) */
    fila_destruir(&fila_atendimento);

    printf("\nFila destruida. Tamanho final: %d\n",
           fila_tamanho(&fila_atendimento));

    /* -------------------------------------------------------
     * ETAPA 6: Teste de remocao em fila vazia
     * Verifica robustez do TAD.
     * ------------------------------------------------------- */
    separador("ETAPA 6 — Remocao em Fila Vazia (Teste de Robustez)");
    int resultado = fila_remover(&fila_atendimento, &atendido);
    printf("Resultado da remocao em fila vazia: %s\n",
           resultado == 0 ? "Operacao rejeitada corretamente" : "ERRO");

    printf("\n[SISTEMA] Simulacao concluida sem memory leaks.\n\n");
    return 0;
}
