# Mini Sistema de Ranking de Jogadores

| Campo | Informação |
|---|---|
| **Nome do aluno** | Kauã |
| **Data** | 15/06/2026 |
| **Disciplina** | Estrutura de Dados / Programação em C |
| **Instituição** | SESI SENAI |

---

## Descrição do desafio

Desenvolver em linguagem C um pequeno sistema de controle de jogadores e pontuações, contemplando:

- Cadastro de até 20 jogadores (struct com `id`, `nome` e `pontos`)
- Listagem de todos os jogadores
- Busca por ID
- Ordenação por pontuação (decrescente)
- Exibição do campeão
- Menu interativo com `switch`

### Extras implementados

| Extra | Implementado |
|---|---|
| Impedir IDs repetidos | ✅ |
| Salvar dados em arquivo `.txt` | ✅ |
| Carregar dados do arquivo na inicialização | ✅ |
| Exibir média de pontuação | ✅ |
| Listar jogadores acima da média | ✅ |

---

## Como compilar

```bash
gcc main.c -o ranking
```

---

## Como executar

```bash
./ranking
```

---

## Estrutura do projeto

```
.
├── main.c          # Código-fonte principal
├── README.md       # Este arquivo
└── jogadores.txt   # Gerado automaticamente ao salvar (opção 7)
```

---

## Menu do sistema

```
============================
  RANKING DE JOGADORES
============================
1 - Cadastrar jogador
2 - Listar jogadores
3 - Buscar jogador por ID
4 - Ordenar ranking por pontuacao
5 - Exibir campeao
6 - Media e jogadores acima da media
7 - Salvar dados em arquivo
0 - Sair
```

---

## Funções implementadas

```c
void cadastrarJogador(Jogador jogadores[], int *quantidade);
void listarJogadores(Jogador jogadores[], int quantidade);
int  buscarPorId(Jogador jogadores[], int quantidade, int id);
void ordenarPorPontuacao(Jogador jogadores[], int quantidade);
void exibirCampeao(Jogador jogadores[], int quantidade);
void exibirMedia(Jogador jogadores[], int quantidade);
void salvarArquivo(Jogador jogadores[], int quantidade);
int  carregarArquivo(Jogador jogadores[], int *quantidade);
```
