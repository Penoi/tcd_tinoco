#include "ordena.h"

// Auxiliar - Troca
int troca(int *vet, int i, int j) {
    int temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;
    return 1;
}
// Auxiliar - Embaralha
void embaralhar(int *vet, int tam) {
    srand(time(NULL));

    for(int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        int aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
    }
}
// Auxiliar - Confere
int confere(int *vet, int tam){
    for(int i = 0; i < tam-1; i++){
        if(vet[i] > vet[i+1]) return 0;
    }
    return 1;
}


// - -- --- ----  ALGORITMOS DE ORDENAÇÃO  - -- - - -- - - --- -//


// selection Sort
void selectionSort(int *vet, int tam) {
    for(int i = 0; i < tam - 1; i++) {
        int indiceMenor = i;

        for(int j = i + 1; j < tam; j++) {
            if(vet[j] < vet[indiceMenor]) {
                indiceMenor = j;
            }
        }
        if(indiceMenor != i) {
            troca(vet, i, indiceMenor);
        }
    }
}


// Quick Sort
void quickSort(int *vet, int l, int r) {

    if(l >= r) return;

    int pivo = vet[r];
    int i = l - 1;

    for(int j = l; j < r; j++) {
        if(vet[j] <= pivo) {
            i++;
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        }
    }

    int aux = vet[i + 1];
    vet[i + 1] = vet[r];
    vet[r] = aux;

    int posPivo = i + 1;

    quickSort(vet, l, posPivo - 1);
    quickSort(vet, posPivo + 1, r);
}


// Merge Sort
void mergeSort(int *vet, int l, int r){
    int mid = (l+r)/2;

    if(l < r){
        mergeSort(vet, l, mid);
        mergeSort(vet, mid+1, r);
        merge(vet, l, mid, r);
    }

}
// Função Merge para juntar
void merge(int *vet, int l, int mid, int r){
    int sz_l = mid-l+1;
    int sz_r = r-mid;

    int *l_vet = (int*)malloc(sizeof(int)*sz_l);
    int *r_vet = (int*)malloc(sizeof(int)*sz_r);
    
    for(int i = 0; i <= mid; i++) l_vet[i] = vet[i+l];
    for(int i = 0; i <= r; i++) r_vet[i] = vet[mid+1+i];

    int i = 0, j = 0, aux = l;

    while(i < sz_l && j < sz_r){
        if(l_vet[i] < r_vet[j]){
            vet[aux] = l_vet[i];
            aux++;
            i++;
        }else{
            vet[aux] = r_vet[j];
            aux++;
            j++;
        }
    }
    while (i < sz_l){
        vet[aux] = l_vet[i];
        aux++;
        i++;
    }
    while (j < sz_r){
        vet[aux] = r_vet[j];
        aux++;
        j++;
    }    
}

// Insertion Sort
void insertionSort(int *vet, int tam) {
    for (int i = 1; i < tam; i++) {
        int atual = vet[i];
        int j = i - 1;

        while (j >= 0 && vet[j] > atual) {
            vet[j + 1] = vet[j];
            j--;
        }

        vet[j + 1] = atual;
    }
}


// Bubble Sort
void bubbleSort(int *vet, int size)
{
    for (int i = 0; i < (size - 1); i++)
    {
        int trocas = 0;

        for (int j = 0; j < (size - 1 - i); j++)
        {
            if (vet[j] > vet[j + 1])
            {
                swap(&vet[j], &vet[j + 1]);
                trocas = 1;
            }
        }
        if (!trocas)
            break;
    }
}



// Bogo Sort
int bogoSort(int *vet, int tam){
    while (!confere(vet, tam))
    return 1;
}


