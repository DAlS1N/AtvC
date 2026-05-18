# 🏁 Corrida dos Algoritmos — Ordenação de Produtos em C

## Tema Escolhido

Comparação de algoritmos clássicos de ordenação aplicados a um cadastro de **produtos de uma loja de informática**. O objetivo é observar, de forma prática e mensurável, como cada algoritmo se comporta em três cenários distintos: dados aleatórios, dados já ordenados e dados em ordem inversa.

---

## Struct Utilizada

```c
typedef struct {
    int   codigo;     // chave de ordenação
    char  nome[50];   // nome do produto
    float valor;      // preço em reais
} Produto;
```

A ordenação é realizada pelo campo `codigo` (inteiro), que representa o identificador único de cada produto.

---

## Algoritmos Implementados

### 🫧 Bubble Sort — Ordenação por Bolha
Percorre o vetor repetidas vezes comparando elementos adjacentes e trocando-os se estiverem fora de ordem. A cada passagem, o maior elemento "borbulha" para o final. É o algoritmo mais simples, porém o menos eficiente: realiza muitas comparações e trocas desnecessárias, mesmo quando os dados estão quase ordenados.

- **Complexidade:** O(n²) no pior e médio caso; O(n²) comparações mesmo no melhor caso (nesta implementação sem flag de parada antecipada).

### 🎯 Selection Sort — Ordenação por Seleção
A cada iteração, localiza o menor elemento no subvetor restante e o posiciona na sua posição definitiva. Realiza sempre o mesmo número de comparações independente do cenário, mas o número de **trocas é sempre no máximo N−1**, tornando-o vantajoso quando operações de escrita/troca são custosas.

- **Complexidade:** O(n²) comparações em todos os casos; O(n) trocas no pior caso.

### 🃏 Insertion Sort — Ordenação por Inserção
Funciona como organizar cartas na mão: pega um elemento e o "encaixa" na posição correta entre os que já foram processados, deslocando os maiores para a direita. Extremamente eficiente quando os dados já estão quase ordenados, pois o laço interno encerra cedo.

- **Complexidade:** O(n) no melhor caso (já ordenado); O(n²) no pior caso (ordem inversa).

---

## Tabela Comparativa de Resultados (N = 10)

### Dados Aleatórios
| Algoritmo      | Comparações | Trocas |
|----------------|:-----------:|:------:|
| Bubble Sort    | 45          | 18     |
| Selection Sort | 45          | 8      |
| **Insertion Sort** | **24**  | 18     |

### Dados Já Ordenados (Melhor Caso)
| Algoritmo      | Comparações | Trocas |
|----------------|:-----------:|:------:|
| Bubble Sort    | 45          | 0      |
| Selection Sort | 45          | 0      |
| **Insertion Sort** | **9**   | **0**  |

### Dados em Ordem Inversa (Pior Caso)
| Algoritmo      | Comparações | Trocas |
|----------------|:-----------:|:------:|
| Bubble Sort    | 45          | 45     |
| **Selection Sort** | 45      | **5**  |
| Insertion Sort | 45          | 45     |

---

## Conclusão por Cenário

| Cenário         | Melhor Algoritmo  | Motivo                                                                 |
|-----------------|-------------------|------------------------------------------------------------------------|
| Já ordenado     | **Insertion Sort** | Apenas N−1 comparações e zero trocas — encerra o laço interno imediatamente |
| Aleatório       | **Insertion Sort** | Significativamente menos comparações (24 vs 45), aproveitando a ordem parcial |
| Ordem inversa   | **Selection Sort** | Apenas 5 trocas contra 45 do Bubble e do Insertion — minimiza escritas |

**Bubble Sort** foi o pior ou empatou em todos os cenários analisados.

---

## Justificativa Técnica

**Por que o Insertion Sort vence em dados ordenados ou quase ordenados?**
O laço interno (`while`) interrompe sua execução assim que encontra um elemento menor ou igual ao elemento sendo inserido. Em um vetor já ordenado, isso ocorre na primeira comparação de cada iteração, resultando em exatamente **N−1 comparações** no total — o mínimo teórico possível para confirmar que um vetor já está ordenado.

**Por que o Selection Sort minimiza trocas no pior caso?**
O algoritmo realiza no máximo **uma troca por iteração** (ao colocar o mínimo encontrado na posição correta), totalizando no máximo N−1 trocas independente da disposição inicial dos dados. Quando operações de troca envolvem objetos grandes ou escrita em memória lenta, isso representa uma vantagem real.

**Por que o Bubble Sort é o pior?**
Mesmo com dados já ordenados, esta implementação **não possui flag de parada antecipada**, forçando todas as N(N−1)/2 comparações em todos os cenários. Além disso, troca elementos vizinhos repetidamente em vez de posicioná-los diretamente, resultando em muitas operações de escrita desnecessárias.

---

## Como Compilar e Executar

```bash
gcc -o corrida corrida.c
./corrida
```

> Requer compilador GCC com suporte ao padrão C99 ou superior.