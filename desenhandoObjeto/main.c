#include <stdio.h>

void draw() {
    int vet[30][30] = { 0 };
    int count = 0;
    int linhas = sizeof(vet) / sizeof(vet[0]);
    int colunas = sizeof(vet[0]) / sizeof(vet[0][0]);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++){
            printf(" %d", vet[i][j]);
            
            if ( count % 2 == 0) {
                printf("\n");
                count++;
            }
        }
        

    } 
}

int main() {

    draw();
    return 0;
}

// vet[10][15]
// 10 e a quantidade de linhas
// 15 e a quantidade de colunas
