#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
   PILHA DE STRINGS  (Exercicios 1-5, 9)
   ============================================================ */

typedef struct No {
    char texto[100];
    struct No *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

void iniciar(Pilha *p) {
    p->topo = NULL;
}

/* Ex01 - push */
void push(Pilha *p, const char *texto) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) { printf("Erro: falha de alocacao.\n"); return; }
    strncpy(novo->texto, texto, 99);
    novo->texto[99] = '\0';
    novo->prox = p->topo;
    p->topo = novo;
}

/* Ex01 - pop */
int pop(Pilha *p, char *dest) {
    if (!p->topo) {
        printf("Erro: Nao ha acoes para desfazer.\n");
        return 0;
    }
    No *tmp = p->topo;
    if (dest) strncpy(dest, tmp->texto, 99);
    p->topo = tmp->prox;
    free(tmp);
    return 1;
}

/* Ex02 - peek */
const char *peek(Pilha *p) {
    if (!p->topo) { printf("Erro: Pilha vazia.\n"); return NULL; }
    return p->topo->texto;
}

/* Ex03 - limpar_pilha */
void limpar_pilha(Pilha *p) {
    int count = 0;
    while (p->topo) {
        No *tmp = p->topo;
        p->topo = tmp->prox;
        free(tmp);
        count++;
    }
    printf("Memoria liberada: %zu bytes\n", count * sizeof(No));
}

/* Ex04 - contar */
int contar(Pilha *p) {
    int c = 0;
    No *atual = p->topo;
    while (atual) { c++; atual = atual->prox; }
    return c;
}

/* Ex05 - comparar (pilhas nao sao modificadas) */
int comparar(Pilha *p1, Pilha *p2) {
    No *a = p1->topo, *b = p2->topo;
    while (a && b) {
        if (strcmp(a->texto, b->texto) != 0) return 0;
        a = a->prox;
        b = b->prox;
    }
    return (a == NULL && b == NULL);
}

/* Ex09 - ordenar pilha com menor no topo, usando so uma pilha auxiliar */
void ordenarPilha(Pilha *p) {
    Pilha aux;
    iniciar(&aux);
    char tmp[100];

    while (p->topo) {
        pop(p, tmp);
        while (aux.topo && strcmp(aux.topo->texto, tmp) > 0) {
            char t[100];
            pop(&aux, t);
            push(p, t);
        }
        push(&aux, tmp);
    }
    /* aux esta com maior no topo; mover de volta inverte, ficando menor no topo */
    while (aux.topo) {
        char t[100];
        pop(&aux, t);
        push(p, t);
    }
}

/* ============================================================
   PILHA DE CHAR  (Exercicios 6, 7, 8)
   ============================================================ */

typedef struct NoChar {
    char c;
    struct NoChar *prox;
} NoChar;

typedef struct {
    NoChar *topo;
} PilhaChar;

void iniciarChar(PilhaChar *p) { p->topo = NULL; }

void pushChar(PilhaChar *p, char c) {
    NoChar *novo = (NoChar *)malloc(sizeof(NoChar));
    if (!novo) { printf("Erro: falha de alocacao.\n"); return; }
    novo->c = c;
    novo->prox = p->topo;
    p->topo = novo;
}

char popChar(PilhaChar *p) {
    if (!p->topo) return '\0';
    NoChar *tmp = p->topo;
    char c = tmp->c;
    p->topo = tmp->prox;
    free(tmp);
    return c;
}

void limparChar(PilhaChar *p) {
    while (p->topo) popChar(p);
}

/* Ex06 - inverte cada palavra da string usando pilha de char */
static void inverterPalavra(const char *palavra, char *dest) {
    PilhaChar p;
    iniciarChar(&p);
    for (int i = 0; palavra[i]; i++) pushChar(&p, palavra[i]);
    int i = 0;
    while (p.topo) dest[i++] = popChar(&p);
    dest[i] = '\0';
}

void criptografiaReversa(const char *msg) {
    char palavra[100];
    int j = 0;
    printf("Resultado: ");
    for (int i = 0; ; i++) {
        if (msg[i] == ' ' || msg[i] == '\0') {
            if (j > 0) {
                palavra[j] = '\0';
                char inv[100];
                inverterPalavra(palavra, inv);
                printf("%s", inv);
                if (msg[i] == ' ') printf(" ");
                j = 0;
            }
            if (msg[i] == '\0') break;
        } else {
            palavra[j++] = msg[i];
        }
    }
    printf("\n");
}

/* Ex07 - conversor decimal para binario */
void decimalParaBinario(int n) {
    PilhaChar p;
    iniciarChar(&p);
    if (n == 0) { printf("Binario de 0: 0\n"); return; }
    int orig = n;
    while (n > 0) {
        pushChar(&p, '0' + (n % 2));
        n /= 2;
    }
    printf("Binario de %d: ", orig);
    while (p.topo) printf("%c", popChar(&p));
    printf("\n");
}

/* Ex08 - validador de parenteses/colchetes/chaves */
int validarSintaxe(const char *expr) {
    PilhaChar p;
    iniciarChar(&p);
    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{') {
            pushChar(&p, c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (!p.topo) { limparChar(&p); return 0; }
            char t = popChar(&p);
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{')) {
                limparChar(&p);
                return 0;
            }
        }
    }
    int valido = (p.topo == NULL);
    limparChar(&p);
    return valido;
}

/* ============================================================
   PILHA DE CHAMADOS  (Exercicio 10)
   ============================================================ */

typedef struct NoChamado {
    int id;
    int urgencia;
    char tecnico[50];
    struct NoChamado *prox;
} NoChamado;

typedef struct {
    NoChamado *topo;
} PilhaChamado;

void iniciarChamado(PilhaChamado *p) { p->topo = NULL; }

void pushChamado(PilhaChamado *p, int id, int urgencia, const char *tecnico) {
    NoChamado *novo = (NoChamado *)malloc(sizeof(NoChamado));
    if (!novo) { printf("Erro: falha de alocacao.\n"); return; }
    novo->id = id;
    novo->urgencia = urgencia;
    strncpy(novo->tecnico, tecnico, 49);
    novo->tecnico[49] = '\0';
    novo->prox = p->topo;
    p->topo = novo;
}

int popChamado(PilhaChamado *p, int *id, int *urgencia, char *tecnico) {
    if (!p->topo) return 0;
    NoChamado *tmp = p->topo;
    *id = tmp->id;
    *urgencia = tmp->urgencia;
    if (tecnico) strncpy(tecnico, tmp->tecnico, 49);
    p->topo = tmp->prox;
    free(tmp);
    return 1;
}

/* Ex10 - move urgencia 5 para prioridade, preservando ordem dos restantes */
void triagemChamados(PilhaChamado *original, PilhaChamado *prioridade) {
    PilhaChamado aux;
    iniciarChamado(&aux);
    int id, urg;
    char tec[50];

    while (original->topo) {
        popChamado(original, &id, &urg, tec);
        pushChamado(&aux, id, urg, tec);
    }
    while (aux.topo) {
        popChamado(&aux, &id, &urg, tec);
        if (urg == 5)
            pushChamado(prioridade, id, urg, tec);
        else
            pushChamado(original, id, urg, tec);
    }
}

void imprimirChamados(PilhaChamado *p) {
    NoChamado *atual = p->topo;
    if (!atual) { printf("  (vazia)\n"); return; }
    while (atual) {
        printf("  [ID:%d | Urgencia:%d | Tecnico:%s]\n",
               atual->id, atual->urgencia, atual->tecnico);
        atual = atual->prox;
    }
}

/* ============================================================
   MAIN
   ============================================================ */

int main(void) {

    printf("===== EX01: Undo (Push/Pop) =====\n");
    Pilha editor;
    iniciar(&editor);
    push(&editor, "Digitou 'Ola'");
    push(&editor, "Digitou 'Mundo'");
    push(&editor, "Formatou negrito");
    char acao[100];
    pop(&editor, acao); printf("Desfeito: %s\n", acao);
    pop(&editor, acao); printf("Desfeito: %s\n", acao);
    pop(&editor, acao); printf("Desfeito: %s\n", acao);
    pop(&editor, acao); /* pilha vazia - exibe erro */

    printf("\n===== EX02: Peek (Navegador) =====\n");
    Pilha nav;
    iniciar(&nav);
    push(&nav, "google.com");
    push(&nav, "github.com");
    push(&nav, "anthropic.com");
    printf("Pagina atual: %s\n", peek(&nav));
    printf("Pagina atual (ainda): %s\n", peek(&nav));
    limpar_pilha(&nav);

    printf("\n===== EX03: Limpar Pilha =====\n");
    Pilha lp;
    iniciar(&lp);
    push(&lp, "item1"); push(&lp, "item2"); push(&lp, "item3");
    limpar_pilha(&lp);

    printf("\n===== EX04: Contar Elementos =====\n");
    Pilha armazem;
    iniciar(&armazem);
    push(&armazem, "Caixa A");
    push(&armazem, "Caixa B");
    push(&armazem, "Caixa C");
    printf("Total de caixas: %d\n", contar(&armazem));
    limpar_pilha(&armazem);

    printf("\n===== EX05: Comparar Pilhas =====\n");
    Pilha s1, s2, s3;
    iniciar(&s1); iniciar(&s2); iniciar(&s3);
    push(&s1, "log1"); push(&s1, "log2");
    push(&s2, "log1"); push(&s2, "log2");
    push(&s3, "log1"); push(&s3, "log_diferente");
    printf("s1 == s2: %s\n", comparar(&s1, &s2) ? "Identicas" : "Diferentes");
    printf("s1 == s3: %s\n", comparar(&s1, &s3) ? "Identicas" : "Diferentes");
    limpar_pilha(&s1); limpar_pilha(&s2); limpar_pilha(&s3);

    printf("\n===== EX06: Criptografia Reversa =====\n");
    criptografiaReversa("Hello World");
    criptografiaReversa("Pilha de dados");

    printf("\n===== EX07: Conversor Binario =====\n");
    decimalParaBinario(0);
    decimalParaBinario(10);
    decimalParaBinario(255);
    decimalParaBinario(42);

    printf("\n===== EX08: Validador de Sintaxe =====\n");
    const char *exprs[] = {
        "(a+b)*[c-{d}]",
        "([)]",
        "((())",
        "{[()]}"
    };
    for (int i = 0; i < 4; i++)
        printf("\"%s\" -> %s\n", exprs[i],
               validarSintaxe(exprs[i]) ? "Valida" : "Invalida");

    printf("\n===== EX09: Ordenacao de Pilha (Estacionamento) =====\n");
    Pilha estac;
    iniciar(&estac);
    push(&estac, "4321");
    push(&estac, "1111");
    push(&estac, "3333");
    push(&estac, "2222");
    printf("Antes (topo -> base): ");
    for (No *t = estac.topo; t; t = t->prox) printf("%s ", t->texto);
    printf("\n");
    ordenarPilha(&estac);
    printf("Depois (menor no topo): ");
    for (No *t = estac.topo; t; t = t->prox) printf("%s ", t->texto);
    printf("\n");
    limpar_pilha(&estac);

    printf("\n===== EX10: Triagem de Chamados =====\n");
    PilhaChamado central, maxPrioridade;
    iniciarChamado(&central);
    iniciarChamado(&maxPrioridade);
    pushChamado(&central, 1, 3, "Ana");
    pushChamado(&central, 2, 5, "Bruno");
    pushChamado(&central, 3, 2, "Carlos");
    pushChamado(&central, 4, 5, "Diana");
    pushChamado(&central, 5, 1, "Eduardo");
    printf("Central antes da triagem:\n");
    imprimirChamados(&central);
    triagemChamados(&central, &maxPrioridade);
    printf("Central apos triagem:\n");
    imprimirChamados(&central);
    printf("Fila de prioridade maxima (urgencia 5):\n");
    imprimirChamados(&maxPrioridade);

    return 0;
}