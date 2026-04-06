#include <stdio.h>

#define N 3

int main() {


    //Análise Big O: Escreva um código que percorra uma matriz N×N e identifique, em comentário, por que sua complexidade de tempo é O(n2).
    //comentário:  Cada elemento da matriz precisa ser visitado uma vez. Como existem 𝑁×𝑁 elementos, 
    //o tempo cresce proporcionalmente ao quadrado de N.

    
    int matriz[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Percorrendo a matriz
    for (int i = 0; i < N; i++) {         
        for (int j = 0; j < N; j++) {      
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}