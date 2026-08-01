// Não é necessário incluir outras bibliotecas, pois "ordena.h"
// já contém todas as dependências utilizadas neste arquivo.
#include "../ordenar/ordena.h"


/* ============================================================
 *                 ALGORITMOS DE BUSCA
 * ============================================================ */

/*
 * Busca Linear
 *
 * Percorre o vetor sequencialmente até encontrar o elemento
 * procurado.
 *
 * Retorno:
 *  Índice (base 0) do elemento, caso seja encontrado.
 *  -1, caso o elemento não exista no vetor.
 * 
 *  Exemplo:
 *  int pos = buscaLinear(vet, 10);
 */

 int buscaLinear(int *vet, int procura);

/*
 * Busca Binária
 *
 * Localiza um elemento em um vetor ordenado utilizando
 * o algoritmo de Busca Binária.
 *
 * O vetor deve estar previamente ordenado em ordem crescente.
 *
 * Retorno:
 *  Índice (base 0) do elemento, caso seja encontrado.
 *  -1, caso o elemento não exista no vetor.
 *
 * Exemplo:
 *  int pos = buscaBinaria(vet, 10);
 */
int buscaBinaria(int *vet, int tam, int procura);