#include "ordenar/ordena.h"
#include "buscar/buscas.h"
#include "arquivos/arquivos.h"
#include <unistd.h>

void menuPrincipal();
void menuOrdenacao();
void choise_2(int *vet, int tam);
void choise_3(int *vet, int tam);
void choise_4(int *vet, int tam);

int main(){
    int choise = -1;
    /*
        1. Carregar arquivo de dados
        2. Buscar elemento (linear ou binária)
        3. Ordenar dados (Insert., Bubble, Selection, Merge, Quick, EXTRA)
        4. Gerar relatório (Log)
        5. Sair
    */
    int tam = -1;
    int *vet = NULL;
    while (choise != 6) {
        printf("\n\n\n");
        menuPrincipal();

        scanf("%d", &choise);

        if (choise == 1) {
            char arquivo[256];

            printf("\nDigite o caminho do arquivo:\n> ");
            scanf("%255s", arquivo);

            lerArquivo(&vet, arquivo, &tam);

            if (vet == NULL) printf("\n[ERRO] Falha ao carregar o arquivo.\n");
            else printf("\n[OK] %d elementos carregados.\n", tam);

        }
        else if (choise == 2) {
            if (tam == -1){
                printf("\n[ERRO] Nenhum vetor carregado...\n");
                printf("Aguarde");
                fflush(stdout);

                for (int i = 0; i < 4; i++) {
                    sleep(1);
                    printf(".");
                    fflush(stdout);
                }
            }
            else choise_2(vet, tam);

        }
        else if (choise == 3) {
            choise_3(vet, tam);

        }
        else if (choise == 4) {
            choise_4(vet, tam);

        }
        else if(choise == 5){
            break;
        }
        
        else {
            printf("\nOpcao invalida.\n");

        }
    }
    printf("Bye Bye...\n");
    return 0;
}

void choise_2(int *vet, int tam){
    int target;

    printf("Entre com um valor para buscar\n");
    printf("Valor: ");
    scanf("%d", &target);

    int find = buscaBinaria(vet, tam, target);

    if(find == -1) printf("\nNao encontrado\n");
    else printf("\nEncontrado na posicao: %d\n", find);

}
void choise_3(int *vet, int tam){
    int opc;
    if(tam == -1){
        printf("Vetor esta vazio...\n");
        return;
    }
    menuOrdenacao();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
        bogoSort(vet, tam);
        break;

    case 2:
        bubbleSort(vet, tam);
        break;

    case 3:
        insertionSort(vet, tam);
        break;
    
    case 4:
        mergeSort(vet, 0, tam-1);
        break;

    case 5:
        quickSort(vet, 0, tam-1);
        break;
    default:
        printf("Saindo...\n");
        return;
        break;
    }
    printf("Ordenado...\n");
}
void choise_4(int *vet, int tam){
}

void menuPrincipal() {
    printf("\n");
    printf("=============================================\n");
    printf("           SISTEMA DE ORDENACAO              \n");
    printf("=============================================\n");
    printf(" 1 - Carregar arquivo\n");
    printf(" 2 - Buscar elemento\n");
    printf(" 3 - Ordenar vetor\n");
    printf(" 4 - Gerar relatório (Log)\n");
    printf(" 5 - Sair\n");
    printf("=============================================\n");
    printf("Escolha >");
}
void menuOrdenacao() {
    printf("\n");
    printf("=============================================\n");
    printf("          ALGORITMOS DE ORDENACAO            \n");
    printf("=============================================\n");
    printf(" 1 - Bogo Sort\n");
    printf(" 2 - Bubble Sort\n");
    printf(" 3 - Insertion Sort\n");
    printf(" 4 - Merge Sort\n");
    printf(" 5 - Quick Sort\n");
    printf(" 6 - Selection Sort\n");
    printf(" 0 - Voltar\n");
    printf("=============================================\n");
    printf("Escolha >");
}