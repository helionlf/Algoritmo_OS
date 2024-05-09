#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 3 // Número de frames na memória

typedef struct {
    int pageNumber;
    int referenceBit;
    int timeReference; // Adicionando variável que representa tempo de referência da página
} PageFrame;

int main() {
    PageFrame memory[NUM_FRAMES];
    int pageReferences[] = {0, 1,1, 2, 3, 0, 4, 1, 2, 5, 3, 4, 6}; // Páginas referenciadas
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int currentTime = 2024; // Tempo atual inicializado em 2024
    int i, j, k;

    // Inicializa a memória
    for (i = 0; i < NUM_FRAMES; i++) {
        memory[i].pageNumber = -1; // -1 indica que o frame está vazio
        memory[i].referenceBit = 0;
        memory[i].timeReference = 0; // Inicializa o tempo de referência como 0
    }

    k = 0; // Inicializa o ponteiro do relógio

    // Simula as referências às páginas
    for (i = 0; i < numReferences; i++) {
        int pageReferenced = pageReferences[i];
        int pageFound = 0;

        for (j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNumber == pageReferenced) {
                memory[j].referenceBit = 1; // Define o bit de referência
                memory[j].timeReference = currentTime; // Atualiza o tempo de referência
                pageFound = 1;
                printf("Página %d já está referenciada na memória \n", pageReferenced);
                break;
            }
        }

        // Se a página não estiver na memória, substitui uma página
        if (!pageFound) {
            // Procura por uma página com bit de referência zero ou com o menor tempo de referência
            while (1) {
                if (memory[k].referenceBit == 0) {
                    // Substitui a página
                    printf("Substituiu página %d\n", memory[k].pageNumber);
                    memory[k].pageNumber = pageReferenced;
                    memory[k].referenceBit = 1;
                    memory[k].timeReference = currentTime; // Atualiza o tempo de referência
                    break;
                } else {
                    // Zera o bit de referência para a próxima verificação
                    memory[k].referenceBit = 0;
                }

                k = (k + 1) % NUM_FRAMES; // Avança para o próximo frame
            }
        }

        // Incrementa o tempo atual
        currentTime++;

        // Imprime o estado da memória após cada referência
        printf("Estado da memória após referência %d: ", pageReferenced);
        for (j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNumber == -1)
                printf("[ - ] ");
            else
                printf("[ %d (%d) ] ", memory[j].pageNumber, memory[j].timeReference);
        }
        printf("\n");
    }

    return 0;
}
