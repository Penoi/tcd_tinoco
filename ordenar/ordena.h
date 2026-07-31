#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ============================================================
 *                    FUNÇÕES AUXILIARES
 * ============================================================ */

/*
 * Troca os elementos das posições i e j do vetor.
 *
 * Parâmetros:
 *  vet - vetor de inteiros.
 *  i   - índice do primeiro elemento.
 *  j   - índice do segundo elemento.
 */
int troca(int *vet, int i, int j);

/*
 * Embaralha aleatoriamente os elementos do vetor.
 * Útil para evitar casos desfavoráveis em algoritmos como Quick Sort.
 *
 * Exemplo:
 *  embaralhar(vet, tamanho);
 */
void embaralhar(int *vet, int tam);

/*
 * Verifica se o vetor está ordenado em ordem crescente.
 *
 * Retorno:
 *  1 - vetor ordenado.
 *  0 - vetor não ordenado.
 */
int confere(int *vet, int tam);


/* ============================================================
 *              ALGORITMOS DE ORDENAÇÃO
 * ============================================================ */

/*
 * Selection Sort
 *
 * Ordena o vetor em ordem crescente.
 */
void selectionSort(int *vet, int tam);

//====================================================== QUICK SORT E AUXILIARES
/* QUICK SORT
 * @param vet - ALVO A SER ORDENADO
 * @param ini - INIDICE DE INICIO
 * @param fim - INIDICE DE FIM
*/
void quickSort(int *vet, int ini, int fim);

/* PARTITION
* @param vet - ALVO A SER ARTICIONADO
* @param ini - INIDICE DE INICIO
* @param fim - INDICE DE FIM
*/
int partition(int *vet, int ini, int fim);

/* SWAP
* @param pos1 - POSICAO 1 A SER ALTERADA PELA 2
* @param pos2 - POSICAO 2 A SER ALTERADA PELA 1
*/
void swap(int *pos1, int *pos2);
//======================================================


/*
 * Merge Sort
 *
 * Ordena o vetor recursivamente utilizando o algoritmo Merge Sort.
 *
 * Parâmetros:
 *  vet - vetor de inteiros.
 *  l   - índice inicial.
 *  r   - índice final.
 */
void mergeSort(int *vet, int l, int r);

/*
 * Merge
 *
 * Intercala dois subvetores ordenados em um único vetor ordenado.
 * Esta função é utilizada internamente pelo Merge Sort.
 */
void merge(int *vet, int l, int mid, int r);

/*
 * Insertion Sort
 *
 * Ordena o vetor em ordem crescente utilizando o algoritmo
 * de inserção (Insertion Sort).
 */
void insertionSort(int *vet, int tam);

/*
 * Bubble Sort
 *
 * Ordena o vetor em ordem crescente.
 *
 * Retorno:
 *  Quantidade de trocas realizadas durante a execução.
 */
int bubbleSort(int *vet, int tam);

/*
 * Bogo Sort
 *
 * Embaralha o vetor repetidamente até que ele esteja ordenado.
 * Utilizado apenas para fins didáticos, pois possui desempenho extremamente ruim.
 *
 * Retorno:
 *  Quantidade de embaralhamentos realizados até a ordenação.
 */
int bogoSort(int *vet, int tam);




