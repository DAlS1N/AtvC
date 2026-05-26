# Tarefa 8 — Árvores Binárias de Busca

## Aluno
[Seu nome aqui]

## Descrição
Implementação de uma Árvore Binária de Busca (ABB) em linguagem C, com as operações de
inserção, busca, remoção e liberação de memória. A atividade também inclui as respostas
conceituais dos exercícios 1 a 9.

---

## Respostas Conceituais

### Exercício 1 — Identificando partes da árvore
```
        10
       /  \
      5    20
     / \     \
    3   7     30
```
- **Raiz:** 10
- **Folhas:** 3, 7 e 30 (nós sem filhos)
- **Filhos do nó 5:** 3 (esquerda) e 7 (direita)
- **Pai do nó 30:** 20
- **É binária?** Sim. Cada nó possui no máximo dois filhos, o que é exatamente a
  definição de árvore binária.

---

### Exercício 2 — Árvore Binária de Busca: 8, 4, 12, 2, 6, 10, 14
```
        8
       / \
      4   12
     / \  / \
    2   6 10  14
```
Regra aplicada: valores menores à esquerda, maiores à direita.

---

### Exercício 3 — Struct do nó
```c
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;
```

---

### Exercício 4 — Função criarNo
Implementada em `arvore.c`. Aloca um `No` com `malloc`, armazena o valor e
inicializa `esquerda` e `direita` com `NULL`.

---

### Exercício 5 — Inserção: 50, 30, 70, 20, 40, 60, 80
```
        50
       /  \
     30    70
    / \    / \
  20  40  60  80
```
- À esquerda do 50: **30**
- À direita do 50: **70**
- O 40 fica à **direita** do 30 (40 > 30)
- O 80 fica à **direita** do 70 (80 > 70)

---

### Exercício 6 — Completando a função de inserção
```c
No* inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita  = inserir(raiz->direita,  valor);
    }
    return raiz;
}
```

---

### Exercício 7 — Caminhos de busca
Árvore usada:
```
        50
       /  \
     30    70
    / \    / \
  20  40  60  80
```
- **Buscar 40:** começa em 50 → vai para 30 (40 < 50) → vai para 40 (40 > 30). **Encontrado.**
- **Buscar 80:** começa em 50 → vai para 70 (80 > 50) → vai para 80 (80 > 70). **Encontrado.**
- **Buscar 25:** começa em 50 → vai para 30 (25 < 50) → vai para 20 (25 < 30) → filho direito de 20 é NULL. **Não encontrado.**
- **Buscar 60:** começa em 50 → vai para 70 (60 > 50) → vai para 60 (60 < 70). **Encontrado.**

---

### Exercício 8 — Função buscar
Implementada em `arvore.c`. Retorna `1` se encontrado, `0` caso contrário.

---

### Exercício 9 — Percurso em ordem
Percurso **esquerda → raiz → direita** na árvore:
```
        50
       /  \
     30    70
    / \    / \
  20  40  60  80
```
**Resultado:** `20 30 40 50 60 70 80`

Implementação em `arvore.c`:
```c
void emOrdem(No* raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->valor);
    emOrdem(raiz->direita);
}
```

---

## Estrutura dos Arquivos
```
tarefa-8-arvores/
├── arvore.h   → declarações da struct e dos protótipos
├── arvore.c   → implementação de todas as funções
├── main.c     → programa principal (exercícios 10 e 11)
└── README.md  → este arquivo
```

---

## Como Compilar e Executar

```bash
# Compilar
gcc main.c arvore.c -o arvore

# Executar
./arvore
```

> **Atenção:** compile `main.c` junto com `arvore.c`. O `main.c` inclui o
> cabeçalho `arvore.h`; não inclua `arvore.c` diretamente em outro `.c`.

---

## Funcionamento da Árvore Binária de Busca

Uma **Árvore Binária de Busca (ABB)** é uma estrutura de dados em que cada nó
armazena um valor e possui até dois filhos:

- **Filho esquerdo:** sempre menor que o nó pai.
- **Filho direito:** sempre maior que o nó pai.

Essa propriedade torna a busca eficiente: a cada comparação, metade da árvore
é descartada, resultando em complexidade **O(log n)** em árvores balanceadas.

### Operações implementadas

| Operação        | Descrição                                                     |
|-----------------|---------------------------------------------------------------|
| `criarNo`       | Aloca e inicializa um novo nó com `malloc`.                   |
| `inserir`       | Percorre a árvore recursivamente e insere no lugar correto.   |
| `buscar`        | Retorna `1` se o valor existe, `0` caso contrário.            |
| `emOrdem`       | Percurso esquerda→raiz→direita; imprime em ordem crescente.   |
| `remover`       | Remove um nó tratando os 3 casos (folha, 1 filho, 2 filhos).  |
| `liberarArvore` | Percurso pós-ordem liberando toda a memória com `free`.       |

### Remoção — os três casos

1. **Nó folha** (sem filhos): o nó é simplesmente removido com `free`.
2. **Nó com um filho**: o filho sobe e ocupa o lugar do nó removido.
3. **Nó com dois filhos**: o nó é substituído pelo seu **sucessor em ordem**
   (o menor valor da subárvore direita), que é então removido recursivamente.