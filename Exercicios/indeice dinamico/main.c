#include <stdio.h>

int pivotIndex();

int main() {


    return 0;
}

int pivotIndex(int* nums, int numsSize) {
    
}
// lembretes
// Calcular a soma total dos elementos do array.
// Percorrer o array mantendo a soma da esquerda (começa em 0).
// Em cada posição i, verificamos se:
// soma_esquerda == soma_total - soma_esquerda - nums[i]
// soma_esquerda: soma dos elementos à esquerda.
// soma_total - soma_esquerda - nums[i]: soma dos elementos à direita.
// Se for igual → retornamos o índice i.
// Caso termine o loop sem encontrar → retorna -1.
