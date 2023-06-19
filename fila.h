#ifndef FILA_H
#define FILA_H

typedef struct {
    char id[10];
    int tempoChegada;
    int tempoExecucao;
    char tipo[10];
} Processo;

typedef struct No {
    Processo processo;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

void inicializarFila(Fila* fila);
void enfileirar(Fila* fila, Processo processo);
Processo desenfileirar(Fila* fila);
int filaVazia(Fila* fila);

#endif
