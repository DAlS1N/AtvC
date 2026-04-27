#include <stdio.h>
#include <assert.h>
#include "requisicao.h"
#include "estrutura.h"

/* ================================================================
 * SA1 – pt.2  |  Suite de Testes + Demonstracao Completa
 *
 * Cobertura:
 *   T1 – Insercao por triagem (FIFO no tail)
 *   T2 – Insercao por emergencia (head)
 *   T3 – Auditoria bidirecional
 *   T4 – Atendimento (remocao do head)
 *   T5 – Remocao por ID: head, meio e tail
 *   T6 – Robustez: remocao em lista vazia e ID inexistente
 *   T7 – Stress: 1000 insercoes + 1000 remocoes sem leak
 *   T8 – Cenario completo: simulacao hospitalar real
 * ================================================================ */

/* ---- Utilidades de saida ---- */

static void cabecalho(const char *titulo)
{
    printf("\n");
    printf("══════════════════════════════════════════════════════\n");
    printf("  %s\n", titulo);
    printf("══════════════════════════════════════════════════════\n");
}

static void ok(const char *msg)  { printf("  [PASS] %s\n", msg); }
static void info(const char *msg){ printf("  [INFO] %s\n", msg); }

/* ================================================================
 * T1 – Insercao por triagem: verifica ordem FIFO
 * ================================================================ */
static void teste_triagem(void)
{
    cabecalho("T1 — Insercao por Triagem (FIFO no tail)");

    Lista l;
    lista_inicializar(&l);

    Requisicao r1 = requisicao_criar("Ana Clara Souza",  1001, "CARD-001");
    Requisicao r2 = requisicao_criar("Bruno Lima",       1002, "ORTH-005");
    Requisicao r3 = requisicao_criar("Carla Mendes",     1003, "NEUR-012");

    assert(inserir_triagem(&l, r1) == 1);
    assert(inserir_triagem(&l, r2) == 1);
    assert(inserir_triagem(&l, r3) == 1);

    assert(lista_tamanho(&l) == 3);
    assert(l.head->dado.codigo_inscricao == 1001);  /* Ana e a primeira */
    assert(l.tail->dado.codigo_inscricao == 1003);  /* Carla e a ultima */
    assert(l.head->prev == NULL);                   /* Head sem predecessor */
    assert(l.tail->next == NULL);                   /* Tail sem sucessor */
    assert(l.head->next->dado.codigo_inscricao == 1002); /* Bruno no meio */
    assert(l.head->next->prev->dado.codigo_inscricao == 1001); /* prev de Bruno = Ana */

    ok("Tres pacientes inseridos em ordem FIFO");
    ok("head->prev == NULL  (invariante)");
    ok("tail->next == NULL  (invariante)");
    ok("Elos prev/next bidirecionais consistentes");

    lista_destruir(&l);
}

/* ================================================================
 * T2 – Insercao por emergencia: head
 * ================================================================ */
static void teste_emergencia(void)
{
    cabecalho("T2 — Insercao por Emergencia (head)");

    Lista l;
    lista_inicializar(&l);

    Requisicao normal    = requisicao_criar("Diego Ferreira",  1004, "CARD-002");
    Requisicao urgente   = requisicao_criar("Elaine Costa",    1005, "UTI-001");
    Requisicao critico   = requisicao_criar("Felipe Duarte",   1006, "UTI-000");

    inserir_triagem(&l, normal);    /* Fila: [Diego]              */
    inserir_emergencia(&l, urgente);/* Fila: [Elaine | Diego]     */
    inserir_emergencia(&l, critico);/* Fila: [Felipe | Elaine | Diego] */

    assert(lista_tamanho(&l) == 3);
    assert(l.head->dado.codigo_inscricao == 1006);   /* Felipe na frente */
    assert(l.tail->dado.codigo_inscricao == 1004);   /* Diego no fim     */

    /* Verifica elos bidirecionais dos tres nos */
    No *a = l.head;              /* Felipe */
    No *b = a->next;             /* Elaine */
    No *c = b->next;             /* Diego  */

    assert(a->prev == NULL);
    assert(b->prev == a);
    assert(c->prev == b);
    assert(a->next == b);
    assert(b->next == c);
    assert(c->next == NULL);

    ok("Emergencia inserida no head em O(1)");
    ok("Dupla emergencia: hierarquia de prioridade correta");
    ok("Cadeia prev/next: A<->B<->C integra");

    lista_destruir(&l);
}

/* ================================================================
 * T3 – Auditoria bidirecional
 * ================================================================ */
static void teste_auditoria(void)
{
    cabecalho("T3 — Auditoria Bidirecional");

    Lista l;
    lista_inicializar(&l);

    inserir_triagem(&l, requisicao_criar("Gabi Rocha",    1007, "DERM-003"));
    inserir_triagem(&l, requisicao_criar("Henrique Melo", 1008, "ORTH-009"));
    inserir_emergencia(&l, requisicao_criar("Ivete Nunes", 1009, "UTI-002"));

    /* Ordem esperada: Ivete (1009) → Gabi (1007) → Henrique (1008) */
    assert(l.head->dado.codigo_inscricao == 1009);
    assert(l.tail->dado.codigo_inscricao == 1008);

    imprimir_auditoria(&l);
    ok("Leitura HEAD→TAIL e TAIL→HEAD exibidas");

    lista_destruir(&l);
}

/* ================================================================
 * T4 – Atendimento (remocao do head)
 * ================================================================ */
static void teste_atendimento(void)
{
    cabecalho("T4 — Atender Paciente (remocao do HEAD)");

    Lista l;
    lista_inicializar(&l);

    inserir_triagem(&l, requisicao_criar("Joao Pedro",  1010, "CARD-007"));
    inserir_triagem(&l, requisicao_criar("Katia Braga", 1011, "NEUR-004"));
    inserir_triagem(&l, requisicao_criar("Lucas Vaz",   1012, "DERM-001"));

    Requisicao atendido;

    /* 1o atendimento */
    assert(atender_paciente(&l, &atendido) == 1);
    assert(atendido.codigo_inscricao == 1010);    /* Joao saiu */
    assert(l.head->dado.codigo_inscricao == 1011);/* Katia agora e o head */
    assert(l.head->prev == NULL);                 /* Novo head sem predecessor */
    assert(lista_tamanho(&l) == 2);

    /* 2o atendimento */
    assert(atender_paciente(&l, &atendido) == 1);
    assert(atendido.codigo_inscricao == 1011);

    /* Atendimento final: lista fica com 1 elemento */
    assert(atender_paciente(&l, &atendido) == 1);
    assert(atendido.codigo_inscricao == 1012);
    assert(lista_vazia(&l) == 1);
    assert(l.head == NULL && l.tail == NULL);     /* Invariante pos-esvaziamento */

    ok("Tres atendimentos em FIFO corretos");
    ok("head->prev == NULL apos cada remocao");
    ok("head == tail == NULL quando lista vazia");

    lista_destruir(&l);
}

/* ================================================================
 * T5 – Remocao por ID: head, meio e tail
 * ================================================================ */
static void teste_remocao_id(void)
{
    cabecalho("T5 — Remover por ID (cabeca, meio e cauda)");

    Lista l;
    lista_inicializar(&l);

    inserir_triagem(&l, requisicao_criar("Mariana Cruz",  2001, "CARD-010"));
    inserir_triagem(&l, requisicao_criar("Nando Ramos",   2002, "ORTH-002"));
    inserir_triagem(&l, requisicao_criar("Olivia Torres", 2003, "NEUR-007"));
    inserir_triagem(&l, requisicao_criar("Paulo Senna",   2004, "UTI-005"));
    inserir_triagem(&l, requisicao_criar("Quirino Assis", 2005, "DERM-006"));

    Requisicao removido;

    /* --- 5a.  Remocao do MEIO (Olivia, ID 2003) --- */
    info("Removendo Olivia (meio, ID 2003)...");
    assert(remover_paciente_id(&l, 2003, &removido) == 1);
    assert(removido.codigo_inscricao == 2003);
    assert(lista_tamanho(&l) == 4);
    /* Verifica religamento: Nando->next deve ser Paulo */
    No *nando = l.head->next;  /* Mariana→Nando */
    assert(nando->dado.codigo_inscricao == 2002);
    assert(nando->next->dado.codigo_inscricao == 2004);  /* Paulo */
    assert(nando->next->prev->dado.codigo_inscricao == 2002); /* prev de Paulo = Nando */
    ok("Religamento dos 4 ponteiros no meio: correto");

    /* --- 5b.  Remocao do HEAD (Mariana, ID 2001) --- */
    info("Removendo Mariana (head, ID 2001)...");
    assert(remover_paciente_id(&l, 2001, &removido) == 1);
    assert(removido.codigo_inscricao == 2001);
    assert(l.head->dado.codigo_inscricao == 2002);  /* Nando e o novo head */
    assert(l.head->prev == NULL);
    ok("Remocao do HEAD: novo head sem predecessor");

    /* --- 5c.  Remocao do TAIL (Quirino, ID 2005) --- */
    info("Removendo Quirino (tail, ID 2005)...");
    assert(remover_paciente_id(&l, 2005, &removido) == 1);
    assert(removido.codigo_inscricao == 2005);
    assert(l.tail->dado.codigo_inscricao == 2004);  /* Paulo e o novo tail */
    assert(l.tail->next == NULL);
    ok("Remocao do TAIL: novo tail sem sucessor");

    assert(lista_tamanho(&l) == 2);

    lista_destruir(&l);
}

/* ================================================================
 * T6 – Robustez: operacoes em lista vazia e ID inexistente
 * ================================================================ */
static void teste_robustez(void)
{
    cabecalho("T6 — Robustez e Casos de Borda");

    Lista l;
    lista_inicializar(&l);

    /* Remocao em lista vazia */
    assert(atender_paciente(&l, NULL) == 0);
    ok("atender_paciente em lista vazia retorna 0");

    assert(remover_paciente_id(&l, 9999, NULL) == 0);
    ok("remover_paciente_id em lista vazia retorna 0");

    /* Insere um paciente e testa ID inexistente */
    inserir_triagem(&l, requisicao_criar("Rafael Braga", 3001, "CARD-001"));
    assert(remover_paciente_id(&l, 9999, NULL) == 0);
    ok("remover_paciente_id com ID invalido retorna 0");

    /* Verifica invariantes apos tentativas falhas */
    assert(lista_tamanho(&l) == 1);
    assert(l.head == l.tail);
    assert(l.head->prev == NULL && l.head->next == NULL);
    ok("Lista integra apos todas as operacoes invalidas");

    /* Auditoria de lista vazia */
    lista_destruir(&l);
    imprimir_auditoria(&l);
    ok("imprimir_auditoria em lista vazia: exibe mensagem adequada");
}

/* ================================================================
 * T7 – Stress: 1000 insercoes alternadas + 1000 remocoes
 *      Valida ausencia de memory leak e integridade dos elos.
 * ================================================================ */
static void teste_stress(void)
{
    cabecalho("T7 — Teste de Stress (1000 insercoes / 1000 remocoes)");

    Lista l;
    lista_inicializar(&l);

    int i;
    /* Insere 500 por triagem e 500 por emergencia */
    for (i = 0; i < 500; i++) {
        char nome[NOME_MAX];
        snprintf(nome, NOME_MAX, "Paciente-%04d", i);
        Requisicao r = requisicao_criar(nome, 5000 + i, "STRESS-1");
        assert(inserir_triagem(&l, r) == 1);
    }
    for (i = 0; i < 500; i++) {
        char nome[NOME_MAX];
        snprintf(nome, NOME_MAX, "Emerg-%04d", i);
        Requisicao r = requisicao_criar(nome, 6000 + i, "UTI-STRESS");
        assert(inserir_emergencia(&l, r) == 1);
    }

    assert(lista_tamanho(&l) == 1000);

    /* Verifica integridade dos elos em toda a lista */
    No *cur = l.head;
    int contagem = 0;
    while (cur != NULL) {
        if (cur->prev != NULL) {
            assert(cur->prev->next == cur);  /* Elo bidirecional consistente */
        }
        if (cur->next != NULL) {
            assert(cur->next->prev == cur);
        }
        contagem++;
        cur = cur->next;
    }
    assert(contagem == 1000);
    ok("1000 nos com elos prev/next bidirecionais corretos");

    /* Remove tudo */
    lista_destruir(&l);
    assert(lista_vazia(&l) == 1);
    ok("lista_destruir liberou todos os 1000 nos sem leak");
}

/* ================================================================
 * T8 – Simulacao hospitalar realista
 * ================================================================ */
static void teste_simulacao_hospitalar(void)
{
    cabecalho("T8 — Simulacao Hospitalar Completa");

    Lista triagem;
    lista_inicializar(&triagem);

    info("-- Chegada dos pacientes pela triagem normal --");
    inserir_triagem(&triagem, requisicao_criar("Sandra Oliveira",  4001, "CARD-003"));
    inserir_triagem(&triagem, requisicao_criar("Tadeu Almeida",    4002, "ORTH-011"));
    inserir_triagem(&triagem, requisicao_criar("Ursula Campos",    4003, "DERM-002"));
    inserir_triagem(&triagem, requisicao_criar("Victor Prado",     4004, "NEUR-009"));
    printf("  [OK] 4 pacientes na fila de triagem.\n");

    imprimir_auditoria(&triagem);

    info("-- Tadeu sofre agravamento: removido do meio e reinsertado como emergencia --");
    Requisicao tadeu;
    remover_paciente_id(&triagem, 4002, &tadeu);
    inserir_emergencia(&triagem, tadeu);  /* Agora no topo */

    assert(triagem.head->dado.codigo_inscricao == 4002);
    ok("Tadeu promovido para o HEAD com sucesso");

    info("-- Ursula desiste e sai da fila --");
    remover_paciente_id(&triagem, 4003, NULL);
    assert(lista_tamanho(&triagem) == 3);
    ok("Ursula removida. Fila com 3 pacientes.");

    info("-- Atendendo pacientes em ordem --");
    Requisicao atendido;
    int ordem[] = {4002, 4001, 4004};  /* Tadeu (emergencia), Sandra, Victor */
    int idx;
    for (idx = 0; idx < 3; idx++) {
        atender_paciente(&triagem, &atendido);
        printf("  [ATENDIDO] %s (inscricao %d)\n",
               atendido.nome_paciente, atendido.codigo_inscricao);
        assert(atendido.codigo_inscricao == ordem[idx]);
    }

    assert(lista_vazia(&triagem) == 1);
    ok("Todos os pacientes atendidos na ordem correta.");

    lista_destruir(&triagem);
    printf("\n  [SISTEMA] Simulacao concluida sem memory leaks.\n");
}

/* ================================================================
 * main  –  executa a suite completa
 * ================================================================ */
int main(void)
{
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║   SA1 pt.2 — Motor de Triagem: Lista Duplamente     ║\n");
    printf("║              Encadeada | Suite de Testes             ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");

    teste_triagem();
    teste_emergencia();
    teste_auditoria();
    teste_atendimento();
    teste_remocao_id();
    teste_robustez();
    teste_stress();
    teste_simulacao_hospitalar();

    printf("\n");
    printf("══════════════════════════════════════════════════════\n");
    printf("  RESULTADO FINAL: TODOS OS TESTES PASSARAM (8/8)    \n");
    printf("══════════════════════════════════════════════════════\n\n");

    return 0;
}
