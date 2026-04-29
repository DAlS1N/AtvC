#include <stdio.h>
#include <string.h>

#define TOTAL_CLIENTES 6

typedef struct {
    int codigo;
    char nome[50];
    char telefone[20];
} Cliente;

/* Busca cliente pelo codigo. Retorna a posicao no vetor ou -1 se nao encontrar. */
int buscar_cliente_por_codigo(Cliente clientes[], int tamanho, int codigo) {
    for (int i = 0; i < tamanho; i++) {
        if (clientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* Busca cliente pelo nome. Retorna a posicao no vetor ou -1 se nao encontrar. */
int buscar_cliente_por_nome(Cliente clientes[], int tamanho, char nome[]) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(clientes[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/* Busca cliente pelo telefone. Retorna a posicao no vetor ou -1 se nao encontrar. */
int buscar_cliente_por_telefone(Cliente clientes[], int tamanho, char telefone[]) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(clientes[i].telefone, telefone) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    Cliente clientes[TOTAL_CLIENTES] = {
        {101, "Ana",     "(11) 91111-1111"},
        {205, "Bruno",   "(11) 92222-2222"},
        {310, "Carla",   "(11) 93333-3333"},
        {412, "Diego",   "(11) 94444-4444"},
        {578, "Eduarda", "(11) 95555-5555"},
        {699, "Felipe",  "(11) 96666-6666"}
    };

    int pos;

    /* ---- Busca por codigo ---- */
    int codigoBuscado = 412;
    pos = buscar_cliente_por_codigo(clientes, TOTAL_CLIENTES, codigoBuscado);
    if (pos != -1) {
        printf("Cliente encontrado por codigo: %s\n", clientes[pos].nome);
    } else {
        printf("Cliente nao encontrado pelo codigo informado.\n");
    }

    /* ---- Busca por nome ---- */
    char nomeBuscado[] = "Carla";
    pos = buscar_cliente_por_nome(clientes, TOTAL_CLIENTES, nomeBuscado);
    if (pos != -1) {
        printf("Cliente encontrado por nome: codigo %d\n", clientes[pos].codigo);
    } else {
        printf("Cliente nao encontrado pelo nome informado.\n");
    }

    /* ---- Busca por nome inexistente (teste de nao encontrado) ---- */
    char nomeInexistente[] = "Zé";
    pos = buscar_cliente_por_nome(clientes, TOTAL_CLIENTES, nomeInexistente);
    if (pos != -1) {
        printf("Cliente encontrado por nome: codigo %d\n", clientes[pos].codigo);
    } else {
        printf("Cliente nao encontrado pelo nome informado.\n");
    }

    /* ---- Desafio extra: busca por telefone ---- */
    char telefoneBuscado[] = "(11) 95555-5555";
    pos = buscar_cliente_por_telefone(clientes, TOTAL_CLIENTES, telefoneBuscado);
    if (pos != -1) {
        printf("Cliente encontrado por telefone: %s (codigo %d)\n",
               clientes[pos].nome, clientes[pos].codigo);
    } else {
        printf("Cliente nao encontrado pelo telefone informado.\n");
    }

    return 0;
}
