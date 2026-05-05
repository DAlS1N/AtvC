#include <stdio.h>
#include <string.h>


typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
} Cliente;


int main() {
 
    Cliente lista[10] = {
        {50, "Zelia", "9999-0001"}, {10, "Ana", "9999-0002"},
        {45, "Carlos", "9999-0003"}, {5, "Beto", "9999-0004"},
        {30, "Yuri", "9999-0005"}, {15, "Daniel", "9999-0006"},
        {25, "Xuxa", "9999-0007"}, {20, "Elisa", "9999-0008"},
        {60, "Fabio", "9999-0009"}, {35, "Guto", "9999-0010"}
    };

}