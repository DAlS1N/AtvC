#include <stdio.h>
#include <string.h>

void bubble_sort(int vetor[], int tamanho, int *comparacoes, int *trocas)
{
    int houve_troca = 1;

    while (houve_troca)
    {
        houve_troca = 0;

        for (int i = 0; i < tamanho - 1; i++)
        {
            (*comparacoes)++;
            if (vetor[i] > vetor[i + 1])
            {
                int auxiliar = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = auxiliar;
                houve_troca = 1;
                (*trocas)++;
            }
        }
    }
}

//--------------------------------------------------------

void selection_Sort(int *vetor, int tamanho, int *comparacoes, int *trocas)
{

    for (int posicao_atual = 0; posicao_atual < tamanho - 1; posicao_atual++)
    {
        int posicao_menor = posicao_atual;
        for (int i = posicao_atual + 1; i < tamanho; i++)
        {
            (*comparacoes)++;
            if (vetor[i] < vetor[posicao_menor])
            {
                posicao_menor = i;
            }
        }

        if (posicao_menor != posicao_atual)
        {
            int aux = vetor[posicao_atual];
            vetor[posicao_atual] = vetor[posicao_menor];
            vetor[posicao_menor] = aux;
            (*trocas)++;
        }
    }
}

//--------------------------------------------------------

void insertonShort(int *vetor, int tamanho, int *comparacoes, int *trocas)
{
    for (int i = 1; i < tamanho; i++)
    {
        int valor_atual = vetor[i];
        int j = i - 1;

        while (j >= 0)
        {
            (*comparacoes)++;
            if (vetor[j] > valor_atual)
            {
                vetor[j + 1] = vetor[j];
                j--;
                (*trocas)++;
            }
            else
            {
                break;
            }
        }
        vetor[j + 1] = valor_atual;
    }
}

//--------------------------------------------------------

int main()
{
    int original[] = {6, 8, 15, 28, 3};
    int vetor[5];
    int tamanho = sizeof(original) / sizeof(original[0]);

    // Bubble Sort
    memcpy(vetor, original, sizeof(original));
    int comparacoes = 0, trocas = 0;
    bubble_sort(vetor, tamanho, &comparacoes, &trocas);
    printf("bubble_sort: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("comparacoes: %d, trocas: %d\n", comparacoes, trocas);

    // Selection Sort
    memcpy(vetor, original, sizeof(original));
    comparacoes = 0, trocas = 0;
    selection_Sort(vetor, tamanho, &comparacoes, &trocas);
    printf("selection_Sort: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("comparacoes: %d, trocas: %d\n", comparacoes, trocas);

    // Insertion Sort
    memcpy(vetor, original, sizeof(original));
    comparacoes = 0, trocas = 0;
    insertonShort(vetor, tamanho, &comparacoes, &trocas);
    printf("insertonShort: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("comparacoes: %d, trocas: %d\n", comparacoes, trocas);

    return 0;
}