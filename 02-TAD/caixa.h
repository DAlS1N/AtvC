#ifndef CAIXA_H
#define CAIXA_H

typedef struct {
    int valor;
} Caixa;

Caixa* criar_caixa(int valorInicial);
void destruir_caixa(Caixa* c);
void escrever_valor(Caixa* c, int valor);
int ler_valor(Caixa* c);

#endif // CAIXA_H