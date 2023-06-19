#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "pilha.h"

void executarProcesso(Fila* fila, Pilha* pilha, int TP, int *cont, char ordemExecucao[][10]) {
    if (filaVazia(fila)) {
        return;
    }

    Processo processoAtual = desenfileirar(fila);
    strcpy(ordemExecucao[++*cont], processoAtual.id);
    printf("Executando processo: %s\n", processoAtual.id);
    int tempoExecucao = processoAtual.tempoExecucao - TP;

    if (tempoExecucao > 0) {
        printf("Processo %s voltara para a fila.\n", processoAtual.id);
        processoAtual.tempoExecucao = tempoExecucao;
        enfileirar(fila, processoAtual);
    } else {
        printf("Processo %s concluido.\n", processoAtual.id);
    }
}
void executarProcessos(Fila* fila, Pilha* pilha, int TP, char ordemExecucao[][10], int *cont) {
        No* noAtual = fila->inicio;
        printf("Fila atual: ");
        while (noAtual != NULL) {
            printf("%s ", noAtual->processo.id);
            noAtual = noAtual->proximo;
        }
        printf("\n");
    while (!filaVazia(fila) || !pilhaVazia(pilha)) {
        // Executa os processos de sistema na fila
        printf("\n");
        while (!filaVazia(fila) && strcmp(fila->inicio->processo.tipo, "sistema") == 0) {
            Processo processoAtual = desenfileirar(fila);
            printf("Executando processo: %s\n", processoAtual.id);
            printf("Processo de sistema.\n");
            printf("Processo %s concluido.\n", processoAtual.id);
        }

        // Move os processos de usuário para a pilha
        if (!filaVazia(fila) && strcmp(fila->inicio->processo.tipo, "usuario") == 0) {
            Processo processoAtual = desenfileirar(fila);
            printf("Executando processo: %s\n", processoAtual.id);
            printf("Processo de usuario. Movendo para a pilha.\n");
            empilhar(pilha, processoAtual); // Move o processo para a pilha
        }

        // Verifica se a fila foi percorrida e move os processos da pilha de volta para a fila
        if (filaVazia(fila) && !pilhaVazia(pilha)) {
            printf("A fila foi percorrida. Movendo processos da pilha para a fila...\n");
            while (!pilhaVazia(pilha)) {
                Processo processoAtual = desempilhar(pilha);
                enfileirar(fila, processoAtual); // Move o processo de volta para a fila
            }
        }
        
        // Exibe a pilha atual
        printf("Pilha atual: ");
        No* noPilha = pilha->topo;
        while (noPilha != NULL) {
            printf("%s ", noPilha->processo.id);
            noPilha = noPilha->proximo;
        }
        printf("\n");
        No* noAtual = fila->inicio;
        printf("Fila atual: ");
        while (noAtual != NULL) {
            printf("%s ", noAtual->processo.id);
            noAtual = noAtual->proximo;
        }
        printf("\n");
        // Executa um processo da fila
        executarProcesso(fila, pilha, TP, cont, ordemExecucao);
        printf("\n");
    }
}


int main() {
    int cont = 0;
    int quantidadeProcessos;

    printf("Digite a quantidade de processos a adicionar: ");
    scanf("%d", &quantidadeProcessos);
    char ordemExecucao[quantidadeProcessos][10];
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    int i;
    for (i = 0; i < quantidadeProcessos; i++) {
        Processo processo;
        printf("Processo %d:\n", i + 1);
        printf("Digite o ID do processo: ");
        scanf("%s", processo.id);
        printf("Digite o tempo de chegada: ");
        scanf("%d", &processo.tempoChegada);
        printf("Digite o tempo de execucao: ");
        scanf("%d", &processo.tempoExecucao);
        printf("Digite o tipo de processo (sistema ou usuario): ");
        scanf("%s", processo.tipo);

        enfileirar(&fila, processo);
    }

    int TP;
    printf("Digite o TEMPO DE PROCESSAMENTO: ");
    scanf("%d", &TP);

    printf("Executando processos...\n");

    executarProcessos(&fila, &pilha, TP, ordemExecucao, &cont);

    printf("Ordem de execucao dos processos:\n");
    for (i = 1; i <= quantidadeProcessos; i++) {
        printf("%s ", ordemExecucao[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}