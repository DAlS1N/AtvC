#include <stdio.h>

int main()
{
    int x = 10;
    int *p;

    p = &x;

    printf("Valor de x: %d\n", x);
    printf("Endereco de x: %p\n", &x);
    printf("Valor do ponteiro p: %p\n", p);
    printf("Valor apontado por p: %d\n", *p);

    // Modificar o valor de x usando o ponteiro
    *p = 20;
    printf("Novo valor de x: %d\n", x);

    int soma = 0;

    soma = somar(soma, 5);
    printf("Soma de soma e 5: %d\n", soma);
    soma = somar(soma, 5);

    printf("Soma de soma e 5: %d\n", soma);

    alterarValor(&soma);

    return 0;
}

    void alterarValor(int *p)
    {
        printf("Valor apontado por p antes: %d\n", *p);
        printf("Valor apontado por p end antes: %d\n", p);
        *p = 30;
        printf("Valor apontado por p depois: %d\n", *p);
        printf("Valor apontado por p end depois: %d\n", p);
    }

    int somar(int soma, int b)
    {
        return soma + b;
    }
