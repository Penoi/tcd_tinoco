#define RELATORIO_H

/*
 * Gera um arquivo com a média dos tempos
 * dos algoritmos de ordenação e busca.
 *
 * vetOriginal:
 * vetor carregado pelo programa.
 *
 * tam:
 * quantidade de elementos do vetor.
 *
 * nomeArquivo:
 * nome do arquivo que será criado.
 *
 * Retorno:
 * 1 em caso de sucesso.
 * 0 em caso de erro.
 */
int gerarRelatorio(
    const int *vetOriginal,
    int tam,
    const char *nomeArquivo
);
