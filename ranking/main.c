#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_JOGADORES 20
#define ARQUIVO "jogadores.txt"

typedef struct {
    int id;
    char nome[50];
    int pontos;
} Jogador;

/* ========== FUNÇÕES PRINCIPAIS ========== */

void cadastrarJogador(Jogador jogadores[], int *quantidade) {
    if (*quantidade >= MAX_JOGADORES) {
        printf("\n[!] Limite de %d jogadores atingido.\n", MAX_JOGADORES);
        return;
    }

    Jogador novo;

    printf("\n--- Cadastrar Jogador ---\n");
    printf("ID: ");
    scanf("%d", &novo.id);
    getchar();

    /* Verificar ID duplicado */
    for (int i = 0; i < *quantidade; i++) {
        if (jogadores[i].id == novo.id) {
            printf("[!] ID %d ja esta em uso. Escolha outro.\n", novo.id);
            return;
        }
    }

    printf("Nome: ");
    fgets(novo.nome, 50, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Pontos: ");
    scanf("%d", &novo.pontos);

    jogadores[*quantidade] = novo;
    (*quantidade)++;

    printf("[OK] Jogador \"%s\" cadastrado com sucesso!\n", novo.nome);
}

void listarJogadores(Jogador jogadores[], int quantidade) {
    printf("\n--- Lista de Jogadores (%d/%d) ---\n", quantidade, MAX_JOGADORES);

    if (quantidade == 0) {
        printf("Nenhum jogador cadastrado.\n");
        return;
    }

    printf("%-5s %-30s %s\n", "ID", "Nome", "Pontos");
    printf("%-5s %-30s %s\n", "---", "------------------------------", "------");

    for (int i = 0; i < quantidade; i++) {
        printf("%-5d %-30s %d\n",
               jogadores[i].id,
               jogadores[i].nome,
               jogadores[i].pontos);
    }
}

int buscarPorId(Jogador jogadores[], int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (jogadores[i].id == id)
            return i;
    }
    return -1;
}

void ordenarPorPontuacao(Jogador jogadores[], int quantidade) {
    /* Bubble sort decrescente */
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (jogadores[j].pontos < jogadores[j + 1].pontos) {
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
    printf("[OK] Jogadores ordenados por pontuacao (decrescente).\n");
}

void exibirCampeao(Jogador jogadores[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhum jogador cadastrado.\n");
        return;
    }

    int idx = 0;
    for (int i = 1; i < quantidade; i++) {
        if (jogadores[i].pontos > jogadores[idx].pontos)
            idx = i;
    }

    printf("\n========== CAMPEAO ==========\n");
    printf("  ID    : %d\n", jogadores[idx].id);
    printf("  Nome  : %s\n", jogadores[idx].nome);
    printf("  Pontos: %d\n", jogadores[idx].pontos);
    printf("==============================\n");
}

/* ========== EXTRAS ========== */

void exibirMedia(Jogador jogadores[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhum jogador para calcular media.\n");
        return;
    }

    double soma = 0;
    for (int i = 0; i < quantidade; i++)
        soma += jogadores[i].pontos;

    double media = soma / quantidade;
    printf("\nMedia de pontuacao: %.2f\n", media);

    printf("\nJogadores acima da media:\n");
    int encontrou = 0;
    for (int i = 0; i < quantidade; i++) {
        if (jogadores[i].pontos > media) {
            printf("  [%d] %s - %d pts\n",
                   jogadores[i].id,
                   jogadores[i].nome,
                   jogadores[i].pontos);
            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("  Nenhum jogador acima da media.\n");
}

void salvarArquivo(Jogador jogadores[], int quantidade) {
    FILE *arq = fopen(ARQUIVO, "w");
    if (!arq) {
        printf("[!] Erro ao abrir arquivo para escrita.\n");
        return;
    }

    fprintf(arq, "%d\n", quantidade);
    for (int i = 0; i < quantidade; i++) {
        fprintf(arq, "%d;%s;%d\n",
                jogadores[i].id,
                jogadores[i].nome,
                jogadores[i].pontos);
    }

    fclose(arq);
    printf("[OK] Dados salvos em \"%s\".\n", ARQUIVO);
}

int carregarArquivo(Jogador jogadores[], int *quantidade) {
    FILE *arq = fopen(ARQUIVO, "r");
    if (!arq)
        return 0; /* arquivo ainda não existe */

    int total;
    fscanf(arq, "%d\n", &total);

    for (int i = 0; i < total; i++) {
        fscanf(arq, "%d;%49[^;];%d\n",
               &jogadores[i].id,
               jogadores[i].nome,
               &jogadores[i].pontos);
    }

    *quantidade = total;
    fclose(arq);
    return 1;
}

/* ========== MENU ========== */

void exibirMenu() {
    printf("\n============================\n");
    printf("  RANKING DE JOGADORES\n");
    printf("============================\n");
    printf("1 - Cadastrar jogador\n");
    printf("2 - Listar jogadores\n");
    printf("3 - Buscar jogador por ID\n");
    printf("4 - Ordenar ranking por pontuacao\n");
    printf("5 - Exibir campeao\n");
    printf("6 - Media e jogadores acima da media\n");
    printf("7 - Salvar dados em arquivo\n");
    printf("0 - Sair\n");
    printf("----------------------------\n");
    printf("Opcao: ");
}

int main() {
    Jogador jogadores[MAX_JOGADORES];
    int quantidade = 0;
    int opcao;

    /* Tenta carregar dados salvos */
    if (carregarArquivo(jogadores, &quantidade))
        printf("[INFO] %d jogador(es) carregado(s) de \"%s\".\n", quantidade, ARQUIVO);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarJogador(jogadores, &quantidade);
                break;

            case 2:
                listarJogadores(jogadores, quantidade);
                break;

            case 3: {
                int id;
                printf("Digite o ID a buscar: ");
                scanf("%d", &id);
                int idx = buscarPorId(jogadores, quantidade, id);
                if (idx == -1) {
                    printf("Jogador com ID %d nao encontrado.\n", id);
                } else {
                    printf("\nJogador encontrado:\n");
                    printf("  ID    : %d\n", jogadores[idx].id);
                    printf("  Nome  : %s\n", jogadores[idx].nome);
                    printf("  Pontos: %d\n", jogadores[idx].pontos);
                }
                break;
            }

            case 4:
                ordenarPorPontuacao(jogadores, quantidade);
                listarJogadores(jogadores, quantidade);
                break;

            case 5:
                exibirCampeao(jogadores, quantidade);
                break;

            case 6:
                exibirMedia(jogadores, quantidade);
                break;

            case 7:
                salvarArquivo(jogadores, quantidade);
                break;

            case 0:
                printf("\nSaindo... Ate mais!\n");
                break;

            default:
                printf("[!] Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
