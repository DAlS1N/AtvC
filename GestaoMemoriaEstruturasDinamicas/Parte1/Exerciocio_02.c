#include <stdio.h>
#include <stdlib.h>

int main()
{
//Gestão Segura: Desenvolva um código que tente alocar 1GB de memória. O programa deve 
//verificar se o ponteiro é NULL, exibir uma mensagem de erro caso falhe e, se tiver sucesso, liberar a memória imediatamente 

    float *ponteiro = (float *)malloc(1024 * 1024 * 1024);

    if(ponteiro == NULL) {
        printf("Erro: alocação vazia\n");
    }else {
        printf("ponteiro liberado");
        free(ponteiro);
    }

}