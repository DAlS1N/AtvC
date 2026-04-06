#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Matriz Dinâmica: Aloque uma matriz M×N de inteiros usando ponteiro de ponteiros (int **matriz) .

    int M = 2, N = 2; // exemplo: 2 linhas, 2 colunas
    int **matriz;

    
    matriz = (int **)malloc(M * sizeof(int *));

  
    for (int i = 0; i < M; i++)
    {
        matriz[i] = (int *)malloc(N * sizeof(int));
    }

   
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("Digite [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }


    printf("\nMatriz:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

   
    for (int i = 0; i < M; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}