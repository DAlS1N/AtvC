# SA2 – Análise Visual e Comparativa de Buscas e Árvores

## Integrantes
> Preencha com os nomes do grupo.

## Como compilar e executar

```bash
# Compilar
make

# Executar
make run

# (Opcional) Habilitar experimento com 1 bilhão de elementos (exige ~8 GB RAM)
make billion && ./busca_arvore
```

Requisitos: `gcc`, `make`, sistema Linux/macOS.

---

## Estrutura do repositório

```
atividade-arvores-busca/
├── src/
│   ├── main.c        # Experimentos e ponto de entrada
│   ├── arvore.c/.h   # BST: inserção, busca, altura, DOT
│   └── buscas.c/.h   # Busca sequencial e binária
├── resultados/
│   ├── resultados.csv
│   ├── grafico_comparacoes.png
│   └── grafico_altura_arvore.png
├── README.md
└── Makefile
```

---

## Resultados obtidos (dados reais)

### n = 100

| Tipo         | Valor buscado | Seq (comp.) | Binária (comp.) | Árvore (comp.) | Altura |
|--------------|---------------|-------------|-----------------|----------------|--------|
| Ordenado     | 2             | 2           | 13              | 2              | 100    |
| Ordenado     | 50            | 50          | 1               | 50             | 100    |
| Ordenado     | 99            | 99          | 11              | 99             | 100    |
| Ordenado     | 1099 (inex.)  | 100         | 14              | 101            | 100    |
| Embaralhado  | 2             | 5           | 13              | 4              | 14     |
| Embaralhado  | 50            | 83          | 1               | 12             | 14     |
| Embaralhado  | 99            | 34          | 11              | 6              | 14     |
| Embaralhado  | 1099 (inex.)  | 100         | 14              | 6              | 14     |

### n = 1.000

| Tipo         | Valor buscado | Seq (comp.) | Binária (comp.) | Árvore (comp.) | Altura |
|--------------|---------------|-------------|-----------------|----------------|--------|
| Ordenado     | 11            | 11          | 15              | 11             | 1000   |
| Ordenado     | 500           | 500         | 1               | 500            | 1000   |
| Ordenado     | 990           | 990         | 19              | 990            | 1000   |
| Ordenado     | 1999 (inex.)  | 1000        | 20              | 1001           | 1000   |
| Embaralhado  | 11            | 328         | 15              | 11             | 28     |
| Embaralhado  | 500           | 854         | 1               | 15             | 28     |
| Embaralhado  | 990           | 29          | 19              | 6              | 28     |
| Embaralhado  | 1999 (inex.)  | 1000        | 20              | 9              | 28     |

### n = 10.000

| Tipo         | Valor buscado | Seq (comp.) | Binária (comp.) | Árvore (comp.) | Altura |
|--------------|---------------|-------------|-----------------|----------------|--------|
| Ordenado     | 101           | 101         | 27              | 101            | 10000  |
| Ordenado     | 5000          | 5000        | 1               | 5000           | 10000  |
| Ordenado     | 9900          | 9900        | 25              | 9900           | 10000  |
| Ordenado     | 10999 (inex.) | 10000       | 28              | 10001          | 10000  |
| Embaralhado  | 101           | 3360        | 27              | 14             | 32     |
| Embaralhado  | 5000          | 2288        | 1               | 16             | 32     |
| Embaralhado  | 9900          | 2010        | 25              | 11             | 32     |
| Embaralhado  | 10999 (inex.) | 10000       | 28              | 14             | 32     |

### n = 1.000.000 e n = 1.000.000.000 — Estimativas analíticas

Para n = 1.000.000:
- **Busca sequencial**: até 1.000.000 comparações (pior caso).
- **Busca binária**: ⌈log₂(1.000.000)⌉ = **20 comparações** (pior caso).
- **Árvore ordenada**: altura = 1.000.000 → até 1.000.000 comparações (lista ligada).
- **Árvore embaralhada**: altura ≈ 2·log₂(1.000.000) ≈ **40 comparações** (caso médio).

Para n = 1.000.000.000:
- **Busca binária**: ⌈log₂(10⁹)⌉ = **30 comparações**.
- **Árvore ordenada**: degenera em lista de 10⁹ nós — inviável na prática.
- **Árvore embaralhada**: altura ≈ **60 comparações**.

> Nota: o experimento com 10⁹ elementos exigiria ~4 GB só para o vetor de inteiros e, na versão ordenada, a BST degenerada consumiria memória equivalente a uma lista ligada de 10⁹ nós. Por isso, este experimento é estimado analiticamente. Para executá-lo, compile com `make billion`.

---

## Análise crítica

### 1. Qual algoritmo teve menos comparações na maioria dos testes?

A **busca binária** foi a mais eficiente em número de comparações na esmagadora maioria dos testes. Com O(log n) comparações independente da distribuição dos dados (desde que o vetor esteja ordenado), ela realizou no máximo 28 comparações para n = 10.000, enquanto a busca sequencial chegou a 10.000.

A árvore com dados embaralhados também foi muito eficiente — O(log n) na prática — mas depende criticamente da ordem de inserção.

### 2. A busca em árvore foi sempre melhor que a busca sequencial? Explique.

**Não.** Quando os dados são inseridos em ordem crescente, a BST se degenera em uma lista ligada (cada nó tem apenas filho direito). Nessa situação, a busca na árvore realiza tantas comparações quanto a busca sequencial — ambas O(n). Nos experimentos, com n = 100 ordenado, a busca do valor 50 exigiu exatamente 50 comparações na árvore, igual à sequencial. Portanto, a árvore só supera a busca sequencial quando está equilibrada, o que ocorre com dados embaralhados.

### 3. O que aconteceu com a árvore quando os valores foram inseridos em ordem crescente?

A árvore se tornou uma **lista ligada degenerada**: cada elemento inserido é sempre maior que o anterior, indo sempre para a subárvore direita. O resultado é uma árvore de altura n (100 para n=100, 1000 para n=1000, etc.), sem nenhum nó com filho esquerdo. Isso elimina completamente a vantagem da estrutura de árvore, tornando a busca O(n) em vez de O(log n).

### 4. Por que a altura da árvore influencia diretamente a quantidade de comparações?

A busca em BST percorre um caminho da raiz até o nó desejado (ou até um nó nulo). O comprimento máximo desse caminho é exatamente a **altura** da árvore. Portanto, quanto maior a altura, mais comparações são necessárias no pior caso. Uma árvore balanceada tem altura O(log n), enquanto uma árvore degenerada tem altura O(n) — a diferença entre log₂(10.000) = 13 e 10.000 comparações é brutal.

### 5. Por que a busca binária exige dados ordenados?

A busca binária funciona eliminando metade dos candidatos a cada comparação. Para isso, ela assume que, se o valor buscado é menor que o elemento do meio, ele só pode estar na metade esquerda. Essa premissa só é válida se os dados estiverem **ordenados**. Em um vetor desordenado, eliminar a metade direita seria incorreto — o valor procurado poderia estar em qualquer posição.

### 6. Qual estrutura você escolheria para um sistema que precisa buscar dados com frequência? Justifique.

Para buscas frequentes, a escolha depende do contexto:

- **Se os dados são estáticos** (raramente inseridos/removidos): **vetor ordenado com busca binária**. É a estrutura mais simples, com excelente localidade de cache e O(log n) garantido.
- **Se os dados são dinâmicos** (inserções e remoções frequentes): **árvore balanceada (AVL ou Red-Black)**. Mantém O(log n) para busca, inserção e remoção, mesmo com qualquer ordem de entrada. Bancos de dados como PostgreSQL e MySQL usam variantes de B-Trees por exatamente esse motivo.

A BST simples não é adequada para produção por causa do risco de degeneração.

### 7. Qual é a relação entre esta atividade e o uso de índices em bancos de dados?

Os índices de banco de dados são, essencialmente, estruturas de busca eficientes aplicadas sobre os dados de uma tabela. Um índice B-Tree (padrão em PostgreSQL, MySQL) funciona como uma árvore balanceada que permite localizar registros em O(log n) em vez de fazer um *full table scan* (busca sequencial, O(n)). Assim como vimos que a árvore embaralhada superou em muito a busca sequencial, um índice bem estruturado pode transformar uma consulta de segundos em microssegundos em tabelas com milhões de linhas. A ausência de índice em uma coluna muito consultada é análoga a usar busca sequencial em vez de BST.

### 8. O que uma árvore balanceada resolveria neste experimento?

Uma **árvore AVL ou Red-Black** garantiria que a altura nunca ultrapasse O(log n), independentemente da ordem de inserção. No experimento com dados ordenados, onde a BST simples atingiu altura 10.000 para n=10.000, uma AVL teria altura máxima de apenas ≈14. Isso transformaria um O(n) em O(log n) garantido, eliminando o pior caso observado. O custo é uma lógica de rotação mais complexa na inserção e remoção.

---

## Gráficos

Os gráficos `grafico_comparacoes.png` e `grafico_altura_arvore.png` estão na pasta `resultados/`.

---

## Resumo dos principais resultados

1. **Busca binária** é a campeã em comparações: O(log n) garantido, nunca mais que 30 comparações mesmo para n=10⁹.
2. **BST com dados ordenados** é a pior estrutura: degenera em O(n), igual à busca sequencial.
3. **BST com dados embaralhados** é O(log n) na prática e é mais versátil que o vetor ordenado por suportar inserções dinâmicas.
4. A **ordem de inserção** é o fator determinante para a eficiência da BST.
5. Para sistemas reais, **estruturas balanceadas** (AVL, Red-Black, B-Tree) são indispensáveis.
