#include <stdio.h>
#include <time.h>

int buscar_binaria(int vetor[], int tamanho, int valor, int *comparacoes) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;

        if (vetor[meio] == valor) {
            return meio;
        }

        if (valor < vetor[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return -1;
}

int busca_sequencial(int vetor[], int tamanho, int valor, int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;

        if (vetor[i] == valor) {
            return i;
        }
    }

    return -1;
}

void insertion_sort(int v[], int n, int *comparacoes, int *trocas) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                (*trocas)++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

int main() {
    int tamanho = 100000;
    int vetor[100000];

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
    }

    int valor = 99999;

    int comp_seq = 0;
    int comp_bin = 0;

    clock_t inicio, fim;

    int repeticoes = 10000; // aumenta precisão

    // 🔹 Busca Sequencial (tempo)
    inicio = clock();
    for (int i = 0; i < repeticoes; i++) {
        busca_sequencial(vetor, tamanho, valor, &comp_seq);
    }
    fim = clock();

    double tempo_seq = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000000 / repeticoes;

    // 🔹 Busca Binária (tempo)
    inicio = clock();
    for (int i = 0; i < repeticoes; i++) {
        buscar_binaria(vetor, tamanho, valor, &comp_bin);
    }
    fim = clock();

    double tempo_bin = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000000 / repeticoes;

    // Execução única (pra posição e comparações reais)
    comp_seq = 0;
    comp_bin = 0;

    int pos_seq = busca_sequencial(vetor, tamanho, valor, &comp_seq);
    int pos_bin = buscar_binaria(vetor, tamanho, valor, &comp_bin);

    printf("\nBusca Sequencial:\n");
    printf("Posicao: %d | Comparacoes: %d | Tempo medio: %.2f microsegundos\n", pos_seq, comp_seq, tempo_seq);

    printf("\nBusca Binaria:\n");
    printf("Posicao: %d | Comparacoes: %d | Tempo medio: %.2f microsegundos\n", pos_bin, comp_bin, tempo_bin);

    // 🔹 Insertion Sort
    int comp_ins = 0, trocas_ins = 0;
    int v[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};
    int n = 10;

    insertion_sort(v, n, &comp_ins, &trocas_ins);

    printf("\nInsertion Sort:\n");
    printf("Comparacoes: %d | Trocas: %d\n", comp_ins, trocas_ins);

    return 0;
}