# Sistema de Atendimento Inteligente

Projeto da disciplina de **Estruturas de Dados** — ADS.  
Desenvolvido em linguagem C utilizando estruturas de dados implementadas pela própria equipe.

---

## Integrantes e Responsabilidades

| Integrante | Responsabilidades |
|---|---|
| **Integrante A** | `atendimento.h/.c`, `fila.h/.c`, `main.c`, menu principal e integração |
| **Integrante B** | `lista.h/.c`, `ordenacao.h/.c`, busca sequencial por cliente e prioridade |
| **Integrante C** | `arvore.h/.c`, `hash.h/.c`, `estatisticas.h/.c`, busca avançada |

**Nota:** Todos os integrantes compreendem o sistema completo e podem explicar qualquer estrutura.

---

## Estruturas de Dados Utilizadas

| Estrutura | Arquivo | Finalidade | Complexidade |
|---|---|---|---|
| **Fila Dinâmica** | `fila.h/.c` | Controla a ordem de atendimento (FIFO) | Enqueue/Dequeue: O(1) |
| **Lista Encadeada** | `lista.h/.c` | Mantém histórico de todos os atendimentos | Inserção/Busca: O(n) |
| **Árvore BST** | `arvore.h/.c` | Busca eficiente por ID | Melhor: O(log n), Pior: O(n) |
| **Tabela Hash** | `hash.h/.c` | Agrupamento e busca por categoria | Melhor: O(1), Pior: O(n) |

---

## Justificativa Técnica das Estruturas

### 1. **Fila (FIFO - First In, First Out)**
   - **Por quê:** Garante atendimento na ordem de chegada (princípio de justiça)
   - **Vantagem:** Operações de inserção e remoção em O(1)
   - **Desvantagem:** Não permite acesso aleatório
   - **Implementação:** Lista encadeada com ponteiros de frente e cauda

### 2. **Lista Encadeada (Histórico)**
   - **Por quê:** Flexível para inserção/remoção sem reorganização de memória
   - **Vantagem:** Alocação dinâmica, sem necessidade de pré-alocar tamanho
   - **Desvantagem:** Busca O(n), sem acesso aleatório
   - **Uso:** Armazena todos os atendimentos (abertos, atendidos, cancelados)

### 3. **Árvore Binária de Busca (BST)**
   - **Por quê:** Busca por ID é muito mais rápida que lista linear
   - **Vantagem:** Busca O(log n) em árvore balanceada
   - **Desvantagem:** Pior caso O(n) se desbalanceada; remoção é complexa
   - **Implementação:** Inserção recursiva, busca por comparação de chaves

### 4. **Tabela Hash com Encadeamento**
   - **Por quê:** Buscar todos os atendimentos de uma categoria é instantâneo
   - **Vantagem:** Busca O(1) no caso médio, agrupamento natural por categoria
   - **Desvantagem:** Colisões podem degradar a performance; 10 buckets é adequado
   - **Função hash:** djb2 simplificada (hash = hash * 31 + char)

---

## Compilação

### Versão Completa (com todas as estruturas avançadas):
```bash
gcc main.c atendimento.c fila.c lista.c ordenacao.c arvore.c hash.c estatisticas.c -o sistema
```

### Versão Mínima (sem Árvore BST e Hash):
Caso a equipe tenha implementado apenas os requisitos obrigatórios:
```bash
gcc main.c atendimento.c fila.c lista.c ordenacao.c -o sistema
```

**Nota:** Se não houver `arvore.h`, `hash.h` e `estatisticas.h`, remova os includes do `main.c`.

---

## Execução

**Linux / macOS:**
```bash
./sistema
```

**Windows:**
```
sistema.exe
```

---

## Histórico de Commits Git

Exemplo de commits realizados durante o desenvolvimento:

```
feat: cria estrutura base do atendimento
feat: implementa fila dinâmica com O(1)
feat: implementa lista encadeada para histórico
feat: adiciona ordenação por prioridade e tempo
feat: implementa árvore binária de busca para ID
feat: implementa tabela hash por categoria
feat: adiciona estatísticas do sistema
fix: melhora validação de entrada (prioridade, tempo)
docs: finaliza README com explicação técnica
```

**Como visualizar:**
```bash
git log --oneline --graph
```

---

## Funcionalidades

### Obrigatórias ✅
- [x] Cadastrar atendimento
- [x] Atender próximo da fila
- [x] Cancelar atendimento
- [x] Listar fila de espera
- [x] Listar histórico
- [x] Busca sequencial por nome do cliente (parcial)
- [x] Busca sequencial por prioridade
- [x] Ordenação do histórico por prioridade
- [x] Ordenação do histórico por tempo estimado

### Avançadas ✅
- [x] Busca por ID via Árvore BST — O(log n)
- [x] Busca por categoria via Tabela Hash — O(1) médio
- [x] Estatísticas do sistema (totais, status, prioridade, top categoria)
- [x] Liberação correta de memória com `free()` e destructores
- [x] Separação clara de responsabilidades entre TADs
- [x] Validação de entrada

---

## Estrutura do Projeto

```
projeto-estruturas-dados/
├── README.md                          
├── main.c                             
│
├── atendimento.h / atendimento.c      
├── fila.h        / fila.c             
├── lista.h       / lista.c            
├── ordenacao.h   / ordenacao.c        
├── arvore.h      / arvore.c           
├── hash.h        / hash.c             
└── estatisticas.h / estatisticas.c    
```

---

## Menu do Sistema

```
========================================
      SISTEMA DE ATENDIMENTOS
========================================
  1  - Cadastrar atendimento
  2  - Atender proximo da fila
  3  - Cancelar atendimento
  4  - Listar fila de espera
  5  - Listar historico
  6  - Buscar por nome do cliente
  7  - Buscar por prioridade
  8  - Buscar por ID (arvore BST)
  9  - Buscar por categoria (hash)
  10 - Ordenar historico por prioridade
  11 - Ordenar historico por tempo
  12 - Exibir estatisticas
  0  - Sair
----------------------------------------
```

---

## Observações Importantes

- Validação de entrada: prioridade (1-3), tempo (> 0)
- IDs são auto-incrementados e únicos
- Status: "aberto", "atendido" ou "cancelado"
- Busca por cliente é case-sensitive e parcial
- Cancelamento remove da fila e marca no histórico
- Toda memória é liberada corretamente ao encerrar
