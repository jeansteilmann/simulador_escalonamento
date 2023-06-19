#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileirar(Fila* fila, Processo processo) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->processo = processo;
    novoNo->proximo = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
}

Processo desenfileirar(Fila* fila) {
    if (fila->inicio == NULL) {
        Processo processoVazio;
        strcpy(processoVazio.id, "");
        processoVazio.tempoChegada = 0;
        processoVazio.tempoExecucao = 0;
        strcpy(processoVazio.tipo, "");
        return processoVazio;
    }

    No* noRemovido = fila->inicio;
    Processo processo = noRemovido->processo;

    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(noRemovido);
    return processo;
}

int filaVazia(Fila* fila) {
    return (fila->inicio == NULL);
}
