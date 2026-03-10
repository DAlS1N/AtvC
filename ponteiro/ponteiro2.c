#include <stdio.h>

void trocarValor(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


int main()
{

    int a = 5;
    int b = 10;

    printf("Antes da troca: a = %d, b = %d\n", a, b);
    trocarValor(&a, &b);
    printf("Depois da troca: a = %d, b = %d\n", a, b);




}
