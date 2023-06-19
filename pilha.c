#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha* pilha, Processo processo) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->processo = processo;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

Processo desempilhar(Pilha* pilha) {
    if (pilha->topo == NULL) {
        Processo processoVazio;
        strcpy(processoVazio.id, "");
        processoVazio.tempoChegada = 0;
        processoVazio.tempoExecucao = 0;
        strcpy(processoVazio.tipo, "");
        return processoVazio;
    }

    No* noAtual = pilha->topo;
    No* noAnterior = NULL;

    while (noAtual->proximo != NULL) {
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if (noAnterior != NULL) {
        noAnterior->proximo = NULL;
    } else {
        pilha->topo = NULL;
    }

    Processo processo = noAtual->processo;
    free(noAtual);
    return processo;
}

int pilhaVazia(Pilha* pilha) {
    return (pilha->topo == NULL);
}
