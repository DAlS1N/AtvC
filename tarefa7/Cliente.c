#include <stdio.h>
#include <string.h>


typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
} Cliente;

// ----------------------------------

int compararStrings(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] > str2[i]) return 1;
        if (str1[i] < str2[i]) return -1;
        i++;
    }

    if (str1[i] > str2[i]) return 1;
    if (str1[i] < str2[i]) return -1;
    
    return 0;
}

// ----------------------------------

void ordenarPorCodigo(Cliente v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].codigo > v[j+1].codigo) {
                Cliente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

// ----------------------------------

void ordenarPorNomeManual(Cliente v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Usamos nossa função manual
            if (compararStrings(v[j].nome, v[j+1].nome) > 0) {
                Cliente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

// ----------------------------------

void buscarPorTelefoneManual(Cliente v[], int n, char termo[]) {
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (compararStrings(v[i].telefone, termo) == 0) {
            printf("\n[Busca] Telefone %s pertence a: %s\n", termo, v[i].nome);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("\nTelefone %s nao encontrado.\n", termo);
}

// ----------------------------------

void imprimir(Cliente v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d \t| Nome: %-10s \t| Tel: %s\n", v[i].codigo, v[i].nome, v[i].telefone);
    }
    printf("--------------------------------------------------\n");
}

// ----------------------------------

void buscarPorTelefone(Cliente v[], int n, char termo[]) {
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(v[i].telefone, termo) == 0) {
            printf("Cliente encontrado! Nome: %s (ID: %d)\n", v[i].nome, v[i].codigo);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("Telefone %s nao encontrado.\n", termo);
}

// ----------------------------------

int main() {
 
    Cliente lista[10] = {
        {50, "Zelia", "9999-0001"}, {10, "Ana", "9999-0002"},
        {45, "Carlos", "9999-0003"}, {5, "Beto", "9999-0004"},
        {30, "Yuri", "9999-0005"}, {15, "Daniel", "9999-0006"},
        {25, "Xuxa", "9999-0007"}, {20, "Elisa", "9999-0008"},
        {60, "Fabio", "9999-0009"}, {35, "Guto", "9999-0010"}
    };

}