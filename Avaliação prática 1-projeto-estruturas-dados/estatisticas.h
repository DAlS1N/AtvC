#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "lista.h"

// ============================================================
//  Estatísticas do sistema
// ============================================================

// Exibe: total de atendimentos, total atendido, total cancelado,
// total aberto e quantidade por prioridade.
void estatisticas_exibir(const Lista *historico);

// Exibe a categoria com maior número de atendimentos.
void estatisticas_categoria_top(const Lista *historico);

#endif // ESTATISTICAS_H
