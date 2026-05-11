#include <stdio.h>
#include <time.h>

int buscar_binaria(int vetor[], int tamanho, int valor, int *comparacoes)
{
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;

        if (vetor[meio] == valor)
        {
            return meio;
        }

        if (valor < vetor[meio])
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    return -1;
}

int busca_sequencial(int vetor[], int tamanho, int valor, int *comparacoes)
{
    for (int i = 0; i < tamanho; i++)
    {
        (*comparacoes)++;

        if (vetor[i] == valor)
        {
            return i;
        }
    }

    return -1;
}

void classificar_insercao(int *vetor, int tamanho, int *comparacoes)
{
    int i, j, atual;

    for (i = 1; i < tamanho; i++)
    {
        atual = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > atual)
        {
            vetor[j + 1] = vetor[j];
            j--;
            (*comparacoes)++;
        }

        vetor[j + 1] = atual;
    }
}

int main()
{
    int tamanho = 100000;

    int vetor[100000];
    int vetor_insercao[100000];

    // Vetor ordenado para buscas
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = i;
    }

    // Vetor invertido para pior caso do insertion sort
    for (int i = 0; i < tamanho; i++)
    {
        vetor_insercao[i] = tamanho - i;
    }

    int valor = 99999;

    int comp_seq = 0;
    int comp_bin = 0;
    int comp_ins = 0;

    clock_t inicio, fim;

    int repeticoes = 10000;

    // 🔹 Busca Sequencial
    inicio = clock();

    for (int i = 0; i < repeticoes; i++)
    {
        busca_sequencial(vetor, tamanho, valor, &comp_seq);
    }

    fim = clock();

    double tempo_seq =
        (double)(fim - inicio) / CLOCKS_PER_SEC * 1000000 / repeticoes;

    // 🔹 Busca Binária
    inicio = clock();

    for (int i = 0; i < repeticoes; i++)
    {
        buscar_binaria(vetor, tamanho, valor, &comp_bin);
    }

    fim = clock();

    double tempo_bin =
        (double)(fim - inicio) / CLOCKS_PER_SEC * 1000000 / repeticoes;

    // 🔹 Insertion Sort
    inicio = clock();

    classificar_insercao(vetor_insercao, tamanho, &comp_ins);

    fim = clock();

    double tempo_ins =
        (double)(fim - inicio) / CLOCKS_PER_SEC * 1000000;

    // Execução única para obter posição e comparações reais
    comp_seq = 0;
    comp_bin = 0;

    int pos_seq = busca_sequencial(vetor, tamanho, valor, &comp_seq);
    int pos_bin = buscar_binaria(vetor, tamanho, valor, &comp_bin);

    printf("\nBusca Sequencial:\n");
    printf("Posicao: %d | Comparacoes: %d | Tempo medio: %.2f microsegundos\n",
           pos_seq, comp_seq, tempo_seq);

    printf("\nBusca Binaria:\n");
    printf("Posicao: %d | Comparacoes: %d | Tempo medio: %.2f microsegundos\n",
           pos_bin, comp_bin, tempo_bin);

    printf("\nClassificacao por Insercao:\n");
    printf("Posicao: %d | Comparacoes: %d | Tempo medio: %.2f microsegundos\n",
           -1, comp_ins, tempo_ins);

    return 0;
}