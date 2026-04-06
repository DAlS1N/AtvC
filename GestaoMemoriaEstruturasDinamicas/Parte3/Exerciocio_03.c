#include <stdio.h>
#include <stdlib.h>

void liberar_matriz(int **matriz, int M) {
    for(int i = 0; i < M; i++) {
        free(matriz[i]); 
    }
    free(matriz); 
}


int main() {

    //Liberação Profunda: Crie uma
    // função para liberar a matriz do exercício anterior, garantindo que cada linha seja liberada antes do ponteiro principal .

    int M = 3, N = 3;
    int **matriz;

    matriz = (int **) malloc(M * sizeof(int *));
    if (matriz == NULL) return 1;

    for(int i = 0; i < M; i++) {
        matriz[i] = (int *) malloc(N * sizeof(int));
        if (matriz[i] == NULL) return 1;
    }

    // Teste
    matriz[0][0] = 10;
    printf("%d\n", matriz[0][0]);

    liberar_matriz(matriz, M);

    return 0;
}