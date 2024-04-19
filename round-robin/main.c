#include <stdio.h>

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
}EstadoProcesso;

typedef struct {
    int id;
    int tempo_restante;
    EstadoProcesso estado;
}Processo;
    
void remover_processo(Processo processos[], int tamanho, int indice) {
    if (indice < 0 || indice >= tamanho) {
        printf("Erro: índice fora dos limites\n");
    }

    // Desloca os elementos à esquerda para preencher o espaço do elemento removido
    for (int i = indice; i < tamanho - 1; i++) {
        processos[i] = processos[i + 1];
    }
}

void roundRobin(Processo processos[], int num_processos) {
    int tmpo_atual = 0;
    int QUANTUM = 10;

    while(num_processos > 0) {

        for(int i = 0; i < num_processos; i++) {
            processos[i].estado = EM_EXECUCAO;
            printf("Tempo %d: Processo %d em execução \n", tmpo_atual, processos[i].id);

            while(QUANTUM <= 10 && QUANTUM >= 0 && processos[i].tempo_restante > 0) {
                processos[i].tempo_restante --;
                printf("QUANTUM %d: Processo %d - Tempo restante: %d \n", QUANTUM, processos[i].id, processos[i].tempo_restante);
                QUANTUM--;
            }

            QUANTUM = 10;

            if(processos[i].tempo_restante > 0) {
                processos[i].estado = PRONTO;
                printf("processo %d nao concluido - processo em estado de pronto \n", processos[i].id);
                tmpo_atual++;
            } else {
                processos[i].estado = CONCLUIDO;
                printf("Processo %d concluido \n", processos[i].id);
                remover_processo(processos, num_processos, i);
                num_processos--;
                i--;
                tmpo_atual++;
            }
        }               
    }
}

int main() {
    Processo processos[] = {
        {1, 6, PRONTO},
        {2, 17, PRONTO},
        {3, 15, PRONTO},
    };
    
    
    int num_processos = sizeof(processos) / sizeof(processos[0]);
    roundRobin(processos, num_processos);
    
    return 0;
}    