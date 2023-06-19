#ifndef PILHA_H
#define PILHA_H
#include "fila.h"
typedef struct {
    No* topo;
} Pilha;

void inicializarPilha(Pilha* pilha);
void empilhar(Pilha* pilha, Processo processo);
Processo desempilhar(Pilha* pilha);
int pilhaVazia(Pilha* pilha);

#endif
