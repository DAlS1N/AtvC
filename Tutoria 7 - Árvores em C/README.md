# Tutoria 7 — Árvores em Linguagem C

## Aluno
> Preencha aqui seu nome (ou da dupla).

## Descrição da atividade
Implementação de árvores binárias de busca (BST) em C, cobrindo:
cadastro de alunos, contagem de nós, busca de mínimo/máximo,
remoção com os três casos clássicos e comparação com busca sequencial.

---

## Exercícios concluídos
- [x] Exercício 1 — Cadastro de alunos
- [x] Exercício 2 — Contagem de nós, folhas, nós com dois filhos e altura
- [x] Exercício 3 — Menor e maior valor
- [x] Exercício 4 — Remoção de nó (três casos)
- [x] Exercício 5 — Comparação busca sequencial × busca em árvore

---

## Como compilar e executar

Todos os exercícios usam apenas a biblioteca padrão de C.
Substitua `<pasta>` e `<arquivo>` conforme o exercício desejado.

```bash
gcc -Wall -o exercicio-01/alunos     exercicio-01/alunos.c
gcc -Wall -o exercicio-02/contagem   exercicio-02/contagem.c
gcc -Wall -o exercicio-03/minmax     exercicio-03/minmax.c
gcc -Wall -o exercicio-04/remocao    exercicio-04/remocao.c
gcc -Wall -o exercicio-05/comparacao exercicio-05/comparacao.c

./exercicio-01/alunos
./exercicio-02/contagem
./exercicio-03/minmax
./exercicio-04/remocao
./exercicio-05/comparacao
```

---

## Respostas das perguntas dos exercícios

### Exercício 3 — Por que menor/maior não precisam percorrer a árvore toda?

A propriedade fundamental da BST garante que, para qualquer nó:
- todos os valores da **subárvore esquerda** são **menores** que ele;
- todos os valores da **subárvore direita** são **maiores** que ele.

Por isso:
- O **menor** valor está sempre no nó mais à esquerda de toda a árvore
  — basta descer continuamente pela esquerda até não ter mais filho esquerdo.
- O **maior** valor está sempre no nó mais à direita — mesma lógica, pelo lado direito.

O caminho percorrido tem comprimento igual à **altura** da árvore, que no caso
médio é O(log n), muito menor do que os n nós totais.

---

### Exercício 5 — Perguntas sobre comparação de buscas

**Qual busca fez menos comparações?**  
A busca na árvore binária de busca fez muito menos comparações.
No teste com 20 elementos e valor 75, a busca sequencial precisou de
20 comparações enquanto a árvore precisou de apenas 5.

**A árvore sempre será melhor? Justifique.**  
Não necessariamente. A árvore é mais eficiente quando está
**razoavelmente balanceada**, pois cada comparação elimina metade
dos nós restantes (O(log n)). Porém, se a árvore ficar muito desbalanceada
ela pode perder essa vantagem.

**O que pode acontecer se os valores forem inseridos já ordenados?**  
Se os valores chegarem em ordem crescente (ou decrescente), cada novo
nó é inserido sempre à direita (ou à esquerda) do anterior. A árvore
degenera em uma **lista encadeada**: fica com altura n e a busca
passa a custar O(n) — idêntico à busca sequencial, sem nenhum ganho.

**Como uma árvore balanceada ajudaria?**  
Árvores auto-balanceadas como **AVL** e **Red-Black Tree** reequilibram
a estrutura a cada inserção ou remoção, garantindo altura O(log n) mesmo
no pior caso. Isso assegura que a busca sempre seja significativamente
mais rápida do que a busca sequencial para conjuntos grandes de dados.

---

## Principais dificuldades encontradas
> Preencha após realizar a atividade.
> Exemplos: gestão de ponteiros na remoção com dois filhos,
> entender a recursão para calcular altura, etc.
