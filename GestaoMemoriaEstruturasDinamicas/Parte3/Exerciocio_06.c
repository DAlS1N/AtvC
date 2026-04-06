#include <stdio.h>
#include <stdlib.h>

struct Produto {
    int ID;
    int preco;
};

struct Produto* buscar_por_id(struct Produto *vetor, int tamanho, int id);

int main() {

    //Busca Sequencial: Em um vetor dinâmico de 10 produtos, 
    //implemente uma função que busca um produto por ID e retorna seu endereço ou NULL.

    int tamanho = 10;

    // Alocar vetor dinâmico
    struct Produto *produtos = (struct Produto *) malloc(tamanho * sizeof(struct Produto));

    // Preencher os produtos
    for (int i = 0; i < tamanho; i++) {
        produtos[i].ID = i + 1;
        produtos[i].preco = (i + 1) * 50;
    }

    int id;
    printf("Digite o ID para buscar: ");
    scanf("%d", &id);

    // Buscar produto
    struct Produto *resultado = buscar_por_id(produtos, tamanho, id);

    // Verificar resultado
    if (resultado != NULL) {
        printf("Produto encontrado\n");
        printf("ID: %d | Preco: %d\n", resultado->ID, resultado->preco);
    } else {
        printf("Produto nao encontrado\n");
    }

    free(produtos);

    return 0;
}

struct Produto* buscar_por_id(struct Produto *vetor, int tamanho, int id) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i].ID == id) {
            return &vetor[i];
        }
    }
    return NULL;
}