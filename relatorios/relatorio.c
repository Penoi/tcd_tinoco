#include "relatorio.h"
#include "../ordenar/ordena.h"
#include "../buscar/buscas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define REPETICOES 100

static double tempoAtualMs(void) {
    return ((double)clock() / CLOCKS_PER_SEC) * 1000.0;
}

static int *copiarVetor(const int *vetOriginal,int tam) {
    int *copia = malloc((size_t)tam * sizeof(int));

    if(copia == NULL) {
        return NULL;
    }

    memcpy(copia,vetOriginal,(size_t)tam * sizeof(int));

    return copia;
}

static void executarSelection(int *vet,int tam) {
    selectionSort(vet,tam);
}

static void executarQuick(int *vet,int tam) {
    quickSort(vet,0,tam - 1);
}

static void executarMerge(int *vet,int tam) {
    mergeSort(vet,0,tam - 1);
}

static void executarInsertion(int *vet,int tam) {
    insertionSort(vet,tam);
}

static void executarBubble(int *vet,int tam) {
    bubbleSort(vet,tam);
}

static double medirOrdenacao(void (*algoritmo)(int *,int),const int *vetOriginal,int tam) {
    double tempoTotal = 0.0;

    for(int i = 0; i < REPETICOES; i++) {
        int *copia = copiarVetor(vetOriginal,tam);

        if(copia == NULL) {
            return -1.0;
        }

        double inicio = tempoAtualMs();

        algoritmo(copia,tam);

        double fim = tempoAtualMs();

        tempoTotal += fim - inicio;

        free(copia);
    }

    return tempoTotal / REPETICOES;
}

static double medirBuscaLinear(const int *vet,int valorProcurado) {
    volatile int resultado = -1;

    double inicio = tempoAtualMs();

    for(int i = 0; i < REPETICOES; i++) {
        resultado = buscaLinear((int *)vet,valorProcurado);
    }

    double fim = tempoAtualMs();

    (void)resultado;

    return (fim - inicio) / REPETICOES;
}

static double medirBuscaBinaria(const int *vetOriginal,int tam,int valorProcurado) {
    double tempoTotal = 0.0;
    volatile int resultado = -1;

    for(int i = 0; i < REPETICOES; i++) {
        int *copia = copiarVetor(vetOriginal,tam);

        if(copia == NULL) {
            return -1.0;
        }

        double inicio = tempoAtualMs();

        resultado = buscaBinaria(copia,tam,valorProcurado);

        double fim = tempoAtualMs();

        tempoTotal += fim - inicio;

        free(copia);
    }

    (void)resultado;

    return tempoTotal / REPETICOES;
}

static void registrarTempo(FILE *arquivo,const char *nomeAlgoritmo,double media) {
    if(media < 0.0) {
        fprintf(arquivo,"%-24s ERRO AO EXECUTAR\n",nomeAlgoritmo);
        return;
    }

    fprintf(arquivo,"%-24s %.9f ms\n",nomeAlgoritmo,media);
}

int gerarRelatorio(const int *vetOriginal,int tam,const char *nomeArquivo) {
    if(vetOriginal == NULL || tam <= 0 || nomeArquivo == NULL) {
        return 0;
    }

    FILE *arquivo = fopen(nomeArquivo,"w");

    if(arquivo == NULL) {
        return 0;
    }

    int valorProcurado = vetOriginal[tam - 1];

    fprintf(
        arquivo,
        "RELATORIO DE DESEMPENHO\n"
        "=======================\n"
        "Quantidade de elementos: %d\n"
        "Repeticoes por algoritmo: %d\n"
        "Valor utilizado nas buscas: %d\n\n",
        tam,
        REPETICOES,
        valorProcurado
    );

    fprintf(
        arquivo,
        "ALGORITMOS DE ORDENACAO\n"
        "-----------------------\n"
    );

    registrarTempo(
        arquivo,
        "Selection Sort:",
        medirOrdenacao(executarSelection,vetOriginal,tam)
    );

    registrarTempo(
        arquivo,
        "Quick Sort:",
        medirOrdenacao(executarQuick,vetOriginal,tam)
    );

    registrarTempo(
        arquivo,
        "Merge Sort:",
        medirOrdenacao(executarMerge,vetOriginal,tam)
    );

    registrarTempo(
        arquivo,
        "Insertion Sort:",
        medirOrdenacao(executarInsertion,vetOriginal,tam)
    );

    registrarTempo(
        arquivo,
        "Bubble Sort:",
        medirOrdenacao(executarBubble,vetOriginal,tam)
    );

    fprintf(
        arquivo,
        "\nALGORITMOS DE BUSCA\n"
        "--------------------\n"
    );

    registrarTempo(
        arquivo,
        "Busca Linear:",
        medirBuscaLinear(vetOriginal,valorProcurado)
    );

    registrarTempo(
        arquivo,
        "Busca Binaria + Sort:",
        medirBuscaBinaria(vetOriginal,tam,valorProcurado)
    );

    fprintf(
        arquivo,
        "\nObservacao: a funcao buscaBinaria do projeto "
        "executa Quick Sort internamente.\n"
    );

    fclose(arquivo);

    return 1;
}