#include <stdlib.h>

struct Fila {
    int *dado;
    int inicio;
}

Fila* criar_fila(int capacidade) {
    Fila *f;

    if (capacidade <= 0) {
        printf("capacidade")
        return NULL;
    }
}

void destruir_fila(Fila *f);

void imprimir_fila(Fila *f);