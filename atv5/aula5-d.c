#include <stdio.h>

int main() {

int x = 10; //variável do tipo inteiro

int *p; //ponteiro de inteiro


p = &x;  //ponteiro recebe o endereço de x


printf("Valor de x: %d\n", x);
printf("Endereco de x: %p\n", &x);
printf("Valor apontado por p: %d\n", *p);


}