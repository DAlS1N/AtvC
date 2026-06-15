#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h"
#include "fila.h"
#include "lista.h"
#include "ordenacao.h"
#include "arvore.h"
#include "hash.h"
#include "estatisticas.h"

// ============================================================
//  Variável global de ID auto-incrementado
// ============================================================
static int proximo_id = 1;

// ============================================================
//  Funções auxiliares do menu
// ============================================================

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\n  Pressione ENTER para continuar...");
    limpar_buffer();
}

void exibir_menu() {
    printf("\n========================================\n");
    printf("      SISTEMA DE ATENDIMENTOS\n");
    printf("========================================\n");
    printf("  1  - Cadastrar atendimento\n");
    printf("  2  - Atender proximo da fila\n");
    printf("  3  - Cancelar atendimento\n");
    printf("  4  - Listar fila de espera\n");
    printf("  5  - Listar historico\n");
    printf("  6  - Buscar por nome do cliente\n");
    printf("  7  - Buscar por prioridade\n");
    printf("  8  - Buscar por ID (arvore BST)\n");
    printf("  9  - Buscar por categoria (hash)\n");
    printf("  10 - Ordenar historico por prioridade\n");
    printf("  11 - Ordenar historico por tempo\n");
    printf("  12 - Exibir estatisticas\n");
    printf("  0  - Sair\n");
    printf("----------------------------------------\n");
    printf("  Opcao: ");
}

// ============================================================
//  Operações do menu
// ============================================================

void op_cadastrar(Fila *fila, Lista *historico, NoArvore **raiz_arvore, TabelaHash *hash) {
    char cliente[50], categoria[30];
    int prioridade, tempo;

    printf("\n  --- Cadastrar Atendimento ---\n");
    printf("  Nome do cliente  : ");
    fgets(cliente, sizeof(cliente), stdin);
    cliente[strcspn(cliente, "\n")] = '\0';

    printf("  Categoria        : ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    printf("  Prioridade (1=Baixa / 2=Media / 3=Alta): ");
    scanf("%d", &prioridade);
    limpar_buffer();
    if (prioridade < 1 || prioridade > 3) {
        printf("  Prioridade invalida. Usando 1 (Baixa).\n");
        prioridade = 1;
    }

    printf("  Tempo estimado (min): ");
    scanf("%d", &tempo);
        if (tempo <= 0) {
            printf("  Tempo invalido. Usando 15 minutos.\n");
            tempo = 15;
        }
    limpar_buffer();

    Atendimento a = atendimento_criar(proximo_id++, cliente, categoria, prioridade, tempo);

    fila_enqueue(fila, a);
    lista_inserir(historico, a);
    *raiz_arvore = arvore_inserir(*raiz_arvore, a);
    hash_inserir(hash, a);

    printf("\n  Atendimento cadastrado com ID %d!\n", a.id);
}

void op_atender_proximo(Fila *fila, Lista *historico) {
    if (fila_vazia(fila)) {
        printf("\n  Fila vazia. Nenhum atendimento a realizar.\n");
        return;
    }
    Atendimento a = fila_dequeue(fila);
    lista_atualizar_status(historico, a.id, "atendido");
    printf("\n  Atendimento realizado:\n");
    a.prioridade = a.prioridade; // sem mudança
    strncpy(a.status, "atendido", sizeof(a.status) - 1);
    atendimento_imprimir(&a);
}

void op_cancelar(Fila *fila, Lista *historico) {
    int id;
    printf("\n  ID do atendimento a cancelar: ");
    scanf("%d", &id);
    limpar_buffer();

    if (lista_atualizar_status(historico, id, "cancelado"))
        printf("  Atendimento %d marcado como cancelado no historico.\n", id);
    else
        printf("  ID %d nao encontrado no historico.\n", id);

    // Remove da fila se ainda estiver lá
    // (percorre e reconstrói a fila sem o elemento cancelado)
    Fila nova_fila;
    fila_inicializar(&nova_fila);
    int removido = 0;
    while (!fila_vazia(fila)) {
        Atendimento a = fila_dequeue(fila);
        if (a.id == id) { removido = 1; continue; }
        fila_enqueue(&nova_fila, a);
    }
    *fila = nova_fila;
    if (removido) printf("  Atendimento %d removido da fila de espera.\n", id);
}

void op_buscar_id(NoArvore *raiz) {
    int id;
    printf("\n  ID a buscar: ");
    scanf("%d", &id);
    limpar_buffer();

    NoArvore *resultado = arvore_buscar(raiz, id);
    if (resultado) {
        printf("\n  Atendimento encontrado:\n");
        atendimento_imprimir(&resultado->dado);
    } else {
        printf("  ID %d nao encontrado na arvore.\n", id);
    }
}

void op_buscar_categoria(TabelaHash *hash) {
    char categoria[30];
    printf("\n  Categoria a buscar: ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';
    hash_buscar_por_categoria(hash, categoria);
}

// ============================================================
//  main
// ============================================================

int main() {
    Fila        fila;
    Lista       historico;
    NoArvore   *arvore = NULL;
    TabelaHash  hash;

    fila_inicializar(&fila);
    lista_inicializar(&historico);
    hash_inicializar(&hash);

    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                op_cadastrar(&fila, &historico, &arvore, &hash);
                break;
            case 2:
                op_atender_proximo(&fila, &historico);
                break;
            case 3:
                op_cancelar(&fila, &historico);
                break;
            case 4:
                printf("\n");
                fila_listar(&fila);
                break;
            case 5:
                printf("\n");
                lista_listar(&historico);
                break;
            case 6: {
                char nome[50];
                printf("\n  Nome (ou parte do nome): ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                lista_buscar_por_cliente(&historico, nome);
                break;
            }
            case 7: {
                int p;
                printf("\n  Prioridade (1=Baixa / 2=Media / 3=Alta): ");
                scanf("%d", &p);
                limpar_buffer();
                lista_buscar_por_prioridade(&historico, p);
                break;
            }
            case 8:
                op_buscar_id(arvore);
                break;
            case 9:
                op_buscar_categoria(&hash);
                break;
            case 10:
                ordenar_por_prioridade(&historico);
                printf("\n  Historico ordenado por prioridade.\n");
                lista_listar(&historico);
                break;
            case 11:
                ordenar_por_tempo(&historico);
                printf("\n  Historico ordenado por tempo estimado.\n");
                lista_listar(&historico);
                break;
            case 12:
                printf("\n");
                estatisticas_exibir(&historico);
                estatisticas_categoria_top(&historico);
                break;
            case 0:
                printf("\n  Encerrando sistema...\n");
                break;
            default:
                printf("\n  Opcao invalida.\n");
        }

        if (opcao != 0) pausar();

    } while (opcao != 0);

    // Libera toda a memória antes de encerrar
    fila_destruir(&fila);
    lista_destruir(&historico);
    arvore_destruir(arvore);
    hash_destruir(&hash);

    return 0;
}
