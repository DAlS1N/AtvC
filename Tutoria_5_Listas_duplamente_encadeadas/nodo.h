#ifndef nodo_H
#define nodo_H


typedef struct Nodo {
    int  valor;   
    struct Nodo  *prev;   /* Elo com o passado  (no anterior)          */
    struct Nodo  *next;   /* Elo com o futuro   (proximo no)           */
} Nodo;

Nodo* criar_nodo(int valor);

int obter_valor(Nodo *nodo);

void definir_valor(Nodo *nodo, int valor);

Nodo* obter_anterior(Nodo *nodo);

Nodo* obter_proximo(Nodo *nodo);

void definir_anterior(Nodo *nodo, Nodo *anterior);

void definir_proximo(Nodo *nodo, Nodo *proximo);

void destruir_nodo(Nodo *nodo);


#endif