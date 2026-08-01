#include "arquivos.h"

void lerArquivo(int **vet, char *nome, int *tam) {
    FILE *arq = fopen(nome, "r");

    if(arq == NULL) {
        printf("Problema ao abrir o arquivo.\n");
        return;
    }

    int capacidade = 10;

    *vet = malloc(capacidade * sizeof(int));

    *tam = 0;

    while (fscanf(arq, "%d", &((*vet)[*tam])) == 1) {

        (*tam)++;

        if (*tam == capacidade) {
            capacidade += 10;
            *vet = realloc(*vet, capacidade * sizeof(int));
        }
    }
    fclose(arq);
}

void debug(){
    printf("Acesso permitido");
}