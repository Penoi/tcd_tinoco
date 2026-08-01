#include "relatorio.h"
#include "../ordenar/ordena.h"
#include "../buscar/buscas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define REPETICOES 100

/*
 * Retorna o tempo de CPU utilizado pelo programa
 * convertido para milissegundos.
 *
 * clock() retorna a quantidade de unidades de tempo
 * de processamento consumidas pelo programa.
 *
 * CLOCKS_PER_SEC informa quantas dessas unidades
 * correspondem a um segundo.
 *
 * A divisão converte para segundos e a multiplicação
 * por 1000 converte para milissegundos.
 */
static double tempoAtualMs(void) {
    return ((double)clock() / CLOCKS_PER_SEC) * 1000.0;
}

/*
 * Cria uma cópia do vetor original.
 *
 * Essa cópia é necessária porque os algoritmos de
 * ordenação modificam o vetor recebido.
 */
static int *copiarVetor(
    const int *vetOriginal,
    int tam
) {
    /*
     * Reserva memória suficiente para armazenar
     * todos os elementos do vetor.
     */
    int *copia = malloc(
        (size_t)tam * sizeof(int)
    );

    /*
     * Se malloc retornar NULL, não foi possível
     * reservar a memória.
     */
    if (copia == NULL) {
        return NULL;
    }

    /*
     * Copia todos os elementos do vetor original
     * para o novo vetor.
     */
    memcpy(
        copia,
        vetOriginal,
        (size_t)tam * sizeof(int)
    );

    return copia;
}

/*
 * Adaptadores dos algoritmos de ordenação.
 *
 * Eles fazem todos os algoritmos possuírem
 * o mesmo formato:
 *
 * algoritmo(vetor, tamanho);
 *
 * Isso permite enviar qualquer um deles para
 * a função medirOrdenacao().
 */

static void executarSelection(
    int *vet,
    int tam
) {
    selectionSort(vet, tam);
}

static void executarQuick(
    int *vet,
    int tam
) {
    quickSort(vet, 0, tam - 1);
}

static void executarMerge(
    int *vet,
    int tam
) {
    mergeSort(vet, 0, tam - 1);
}

static void executarInsertion(
    int *vet,
    int tam
) {
    insertionSort(vet, tam);
}

static void executarBubble(
    int *vet,
    int tam
) {
    /*
     * O Bubble Sort do projeto retorna um inteiro.
     *
     * Como precisamos apenas medir seu tempo,
     * ignoramos propositalmente esse retorno.
     */
    (void)bubbleSort(vet, tam);
}

/*
 * Executa um algoritmo de ordenação 100 vezes
 * e retorna a média aritmética dos tempos.
 *
 * O primeiro parâmetro é um ponteiro para função.
 * Ele permite receber diferentes algoritmos.
 */
static double medirOrdenacao(
    void (*algoritmo)(int *, int),
    const int *vetOriginal,
    int tam
) {
    /*
     * Armazena a soma dos tempos das
     * 100 execuções.
     */
    double tempoTotal = 0.0;

    for (int i = 0; i < REPETICOES; i++) {

        /*
         * Cria uma cópia antes de cada execução.
         *
         * Assim, todas as execuções recebem
         * exatamente o mesmo vetor inicial.
         */
        int *copia = copiarVetor(
            vetOriginal,
            tam
        );

        if (copia == NULL) {
            return -1.0;
        }

        /*
         * Registra o tempo antes de executar
         * o algoritmo.
         */
        double inicio = tempoAtualMs();

        /*
         * Executa o algoritmo que foi recebido
         * como parâmetro.
         */
        algoritmo(copia, tam);

        /*
         * Registra o tempo após a execução.
         */
        double fim = tempoAtualMs();

        /*
         * Calcula o tempo desta execução
         * e adiciona ao total.
         */
        tempoTotal += fim - inicio;

        /*
         * Libera a memória utilizada pela cópia.
         */
        free(copia);
    }

    /*
     * Calcula a média aritmética:
     *
     * soma dos tempos / 100
     */
    return tempoTotal / REPETICOES;
}

/*
 * Executa a Busca Linear 100 vezes e retorna
 * a média do tempo de execução.
 *
 * A função buscaLinear do projeto recebe apenas:
 *
 * - o vetor;
 * - o elemento procurado.
 */
static double medirBuscaLinear(
    const int *vet,
    int valorProcurado
) {
    /*
     * Guarda o resultado retornado pela busca.
     *
     * volatile ajuda a evitar que o compilador
     * remova a chamada da busca por otimização.
     */
    volatile int resultado = -1;

    /*
     * Para buscas muito rápidas, medir uma execução
     * separadamente pode resultar em 0 ms.
     *
     * Por isso, medimos as 100 execuções juntas.
     */
    double inicio = tempoAtualMs();

    for (int i = 0; i < REPETICOES; i++) {

        /*
         * A função original recebe int *.
         *
         * Como gerarRelatorio recebe const int *,
         * utilizamos o cast apenas para chamar a
         * função original sem alterar sua assinatura.
         */
        resultado = buscaLinear(
            (int *)vet,
            valorProcurado
        );
    }

    double fim = tempoAtualMs();

    /*
     * Informa que o resultado foi propositalmente
     * mantido, mesmo não sendo exibido.
     */
    (void)resultado;

    /*
     * Divide o tempo total das 100 execuções
     * pela quantidade de repetições.
     */
    return (fim - inicio) / REPETICOES;
}

/*
 * Executa a Busca Binária 100 vezes e retorna
 * a média dos tempos.
 *
 * A função buscaBinaria do projeto chama o
 * Quick Sort internamente.
 *
 * Por isso, cada execução deve receber uma nova
 * cópia do vetor original.
 */
static double medirBuscaBinaria(
    const int *vetOriginal,
    int tam,
    int valorProcurado
) {
    double tempoTotal = 0.0;

    volatile int resultado = -1;

    for (int i = 0; i < REPETICOES; i++) {

        /*
         * Cria uma cópia antes de cada busca.
         *
         * Isso é necessário porque buscaBinaria()
         * ordena e modifica o vetor recebido.
         */
        int *copia = copiarVetor(
            vetOriginal,
            tam
        );

        if (copia == NULL) {
            return -1.0;
        }

        /*
         * A criação da cópia não entra no tempo.
         * A medição começa somente antes da busca.
         */
        double inicio = tempoAtualMs();

        /*
         * Esta chamada mede a função original.
         *
         * Como buscaBinaria() chama quickSort(),
         * o tempo inclui:
         *
         * Quick Sort + Busca Binária.
         */
        resultado = buscaBinaria(
            copia,
            tam,
            valorProcurado
        );

        double fim = tempoAtualMs();

        tempoTotal += fim - inicio;

        free(copia);
    }

    (void)resultado;

    return tempoTotal / REPETICOES;
}

/*
 * Escreve o nome de um algoritmo e sua média
 * dentro do arquivo de relatório.
 */
static void registrarTempo(
    FILE *arquivo,
    const char *nomeAlgoritmo,
    double media
) {
    /*
     * Uma média negativa indica que ocorreu
     * algum erro durante a medição.
     */
    if (media < 0.0) {
        fprintf(
            arquivo,
            "%-24s ERRO AO EXECUTAR\n",
            nomeAlgoritmo
        );

        return;
    }

    /*
     * %-24s:
     * reserva 24 posições para o nome e
     * alinha o texto à esquerda.
     *
     * %.9f:
     * mostra nove casas decimais.
     */
    fprintf(
        arquivo,
        "%-24s %.9f ms\n",
        nomeAlgoritmo,
        media
    );
}

/*
 * Gera o arquivo com os resultados dos algoritmos.
 *
 * Retorno:
 *
 * 1 - relatório gerado com sucesso.
 * 0 - aconteceu algum erro.
 */
int gerarRelatorio(
    const int *vetOriginal,
    int tam,
    const char *nomeArquivo
) {
    /*
     * Verifica se os parâmetros recebidos
     * são válidos.
     */
    if (
        vetOriginal == NULL ||
        tam <= 0 ||
        nomeArquivo == NULL
    ) {
        return 0;
    }

    /*
     * Abre o arquivo no modo "w".
     *
     * Se não existir, o arquivo será criado.
     * Se já existir, o conteúdo anterior será apagado.
     */
    FILE *arquivo = fopen(
        nomeArquivo,
        "w"
    );

    if (arquivo == NULL) {
        return 0;
    }

    /*
     * Escolhe um valor que existe no vetor.
     *
     * Neste caso, utilizamos o último elemento.
     */
    int valorProcurado =
        vetOriginal[tam - 1];

    /*
     * Escreve o cabeçalho do arquivo.
     */
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

    /*
     * Seção dos algoritmos de ordenação.
     */
    fprintf(
        arquivo,
        "ALGORITMOS DE ORDENACAO\n"
        "-----------------------\n"
    );

    /*
     * Para cada algoritmo:
     *
     * 1. medirOrdenacao executa 100 vezes;
     * 2. calcula a média;
     * 3. registrarTempo escreve no arquivo.
     */

    registrarTempo(
        arquivo,
        "Selection Sort:",
        medirOrdenacao(
            executarSelection,
            vetOriginal,
            tam
        )
    );

    registrarTempo(
        arquivo,
        "Quick Sort:",
        medirOrdenacao(
            executarQuick,
            vetOriginal,
            tam
        )
    );

    registrarTempo(
        arquivo,
        "Merge Sort:",
        medirOrdenacao(
            executarMerge,
            vetOriginal,
            tam
        )
    );

    registrarTempo(
        arquivo,
        "Insertion Sort:",
        medirOrdenacao(
            executarInsertion,
            vetOriginal,
            tam
        )
    );

    registrarTempo(
        arquivo,
        "Bubble Sort:",
        medirOrdenacao(
            executarBubble,
            vetOriginal,
            tam
        )
    );

    /*
     * Seção dos algoritmos de busca.
     */
    fprintf(
        arquivo,
        "\nALGORITMOS DE BUSCA\n"
        "--------------------\n"
    );

    registrarTempo(
        arquivo,
        "Busca Linear:",
        medirBuscaLinear(
            vetOriginal,
            valorProcurado
        )
    );

    registrarTempo(
        arquivo,
        "Busca Binaria + Sort:",
        medirBuscaBinaria(
            vetOriginal,
            tam,
            valorProcurado
        )
    );

    /*
     * Explica por que o nome mostra
     * "Busca Binária + Sort".
     */
    fprintf(
        arquivo,
        "\nObservacao: a funcao buscaBinaria do projeto "
        "executa Quick Sort internamente.\n"
    );

    /*
     * Fecha o arquivo e garante que o conteúdo
     * seja gravado corretamente.
     */
    fclose(arquivo);

    return 1;
}