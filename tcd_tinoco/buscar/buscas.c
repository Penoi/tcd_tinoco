#include "buscas.h"
#include "../ordenar/ordena.h"

int buscaLinear(int *vet, int procura){
    int tam = sizeof(vet) / sizeof(vet[0]);
    for(int i = 0; i < tam; i++) 
        if(vet[i] == procura)
            return i;
    return -1;
}

int buscaBinaria(int *vet, int tam, int procura){
    
    quickSort(vet, 0, tam - 1);
    
    int l = 0;
    int r = tam - 1;

    while (l <= r){
        int mid = (l + r) / 2;

        if (vet[mid] < procura)
            l = mid + 1;
        else if (vet[mid] > procura)
            r = mid - 1;
        else
            return mid;
    }

    return -1;
}

