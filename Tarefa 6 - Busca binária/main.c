#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 10

typedef struct
{
    int codigo;
    char nome[50];
    float valor;
} Produto;

/* ---------- utilitários ---------- */

/* Copia todos os produtos de um vetor para outro.
   Usada antes de cada algoritmo para que todos comecem com os mesmos dados. */
void copiar(Produto dest[], Produto orig[], int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = orig[i];
}

/* Mostra todos os produtos na tela. */
void imprimir(Produto v[], int n)
{
    for (int i = 0; i < n; i++)
        printf("  Cod: %3d | %-12s | R$ %.2f\n", v[i].codigo, v[i].nome, v[i].valor);
}

/* ---------- algoritmos de ordenação ---------- */



/* BUBBLE SORT (Ordenação por Bolha)
   Compara dois produtos vizinhos e troca se estiverem fora de ordem.
   Repete isso várias vezes até o vetor estar ordenado.
   O maior elemento "borbulha" para o final a cada passagem.
   Simples, mas lento: faz muitas comparações e trocas desnecessárias. */
void bubble_sort(Produto v[], int n, long *comp, long *trocas)
{
    *comp = *trocas = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            (*comp)++; /* conta a comparação */
            if (v[j].codigo > v[j + 1].codigo)
            {
                Produto tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                (*trocas)++; /* conta a troca */
            }
        }
    }
}


/* SELECTION SORT (Ordenação por Seleção)
   A cada rodada, varre o restante do vetor procurando o menor elemento
   e o coloca na posição correta.
   Faz sempre o mesmo número de comparações, mas poucas trocas (no máximo N-1).
   Vantagem: ótimo quando trocas são custosas. */
void selection_sort(Produto v[], int n, long *comp, long *trocas)
{
    *comp = *trocas = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            (*comp)++; /* conta a comparação */
            if (v[j].codigo < v[min].codigo)
                min = j;
        }
        if (min != i)
        {
            Produto tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
            (*trocas)++; /* conta a troca */
        }
    }
}


/* INSERTION SORT (Ordenação por Inserção)
   Funciona como ordenar cartas na mão: pega um elemento e o encaixa
   na posição certa entre os que já foram vistos, empurrando os maiores
   uma casa para a direita.
   Muito eficiente quando os dados já estão quase ordenados.
   Pior desempenho quando os dados estão em ordem inversa. */
void insertion_sort(Produto v[], int n, long *comp, long *trocas)
{
    *comp = *trocas = 0;
    for (int i = 1; i < n; i++)
    {
        Produto atual = v[i]; /* guarda o produto que será encaixado */
        int j = i - 1;
        while (j >= 0)
        {
            (*comp)++; /* conta a comparação (inclusive quando falha) */

            if (v[j].codigo > atual.codigo)
            {
                v[j + 1] = v[j]; /* empurra o maior uma casa para a direita */
                (*trocas)++;
                j--;
            }
            else
            {
                break;
            }
        }
        v[j + 1] = atual; /* encaixa o produto na posição correta */
    }
}

/* ---------- geração de cenários ---------- */

/* Cenário 1: dados com codigos sorteados aleatoriamente (situação real). */
void gerar_aleatorio(Produto v[], int n)
{
    const char *nomes[] = {"Teclado", "Mouse", "Monitor", "Notebook", "Headset",
                           "Webcam", "Impressora", "Roteador", "SSD", "Pendrive"};
    for (int i = 0; i < n; i++)
    {
        v[i].codigo = rand() % (n * 10);
        snprintf(v[i].nome, sizeof(v[i].nome), "%s", nomes[i % 10]);
        v[i].valor = (rand() % 50000) / 100.0f;
    }
}

/* Cenário 2: dados já em ordem crescente de codigo (melhor caso). */
void gerar_ordenado(Produto v[], int n)
{
    const char *nomes[] = {"Teclado", "Mouse", "Monitor", "Notebook", "Headset",
                           "Webcam", "Impressora", "Roteador", "SSD", "Pendrive"};
    for (int i = 0; i < n; i++)
    {
        v[i].codigo = i + 1;
        snprintf(v[i].nome, sizeof(v[i].nome), "%s", nomes[i % 10]);
        v[i].valor = (i + 1) * 10.0f;
    }
}

/* Cenário 3: dados em ordem decrescente de codigo (pior caso). */
void gerar_inverso(Produto v[], int n)
{
    const char *nomes[] = {"Teclado", "Mouse", "Monitor", "Notebook", "Headset",
                           "Webcam", "Impressora", "Roteador", "SSD", "Pendrive"};
    for (int i = 0; i < n; i++)
    {
        v[i].codigo = n - i;
        snprintf(v[i].nome, sizeof(v[i].nome), "%s", nomes[i % 10]);
        v[i].valor = (n - i) * 10.0f;
    }
}

/* ---------- execução de um cenário ---------- */

/* Roda os três algoritmos sobre o mesmo vetor original e imprime a tabela.
   Usa copiar() antes de cada um para não alterar os dados originais. */
void executar(const char *nome, Produto original[], int n)
{
    Produto copia[TAMANHO];
    long comp, trocas;

    printf("\n=== %s ===\n", nome);
    printf("%-15s | %12s | %8s\n", "Algoritmo", "Comparacoes", "Trocas");
    printf("------------------------------------------\n");

    copiar(copia, original, n);
    bubble_sort(copia, n, &comp, &trocas);
    printf("%-15s | %12ld | %8ld\n", "Bubble Sort", comp, trocas);

    copiar(copia, original, n);
    selection_sort(copia, n, &comp, &trocas);
    printf("%-15s | %12ld | %8ld\n", "Selection Sort", comp, trocas);

    copiar(copia, original, n);
    insertion_sort(copia, n, &comp, &trocas);
    printf("%-15s | %12ld | %8ld\n", "Insertion Sort", comp, trocas);
}

int main(void)
{
    srand((unsigned)time(NULL)); /* semente aleatória baseada no horário */

    Produto aleatorio[TAMANHO], ordenado[TAMANHO], inverso[TAMANHO];
    gerar_aleatorio(aleatorio, TAMANHO);
    gerar_ordenado(ordenado, TAMANHO);
    gerar_inverso(inverso, TAMANHO);

    printf("=== CORRIDA DOS ALGORITMOS | Entidade: Produto | N = %d ===\n", TAMANHO);
    printf("\nDados aleatorios (antes de ordenar):\n");
    imprimir(aleatorio, TAMANHO);

    executar("Dados Aleatorios", aleatorio, TAMANHO);
    executar("Dados ja Ordenados", ordenado, TAMANHO);
    executar("Dados em Ordem Inversa", inverso, TAMANHO);

    printf("\n=== CONCLUSAO ===\n");
    printf("Ordenado  -> Insertion Sort e o melhor (minimo de comparacoes e trocas)\n");
    printf("Aleatorio -> Insertion Sort tende a ter menos comparacoes\n");
    printf("Inverso   -> Selection Sort minimiza trocas (no maximo N-1)\n");
    printf("Bubble Sort e o pior ou igual nos tres cenarios\n");

    return 0;
}