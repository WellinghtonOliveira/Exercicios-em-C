#include <stdio.h>
#include <windows.h>

void draw() {
    int vet[50][50] = { 0 };
    int linhas = sizeof(vet) / sizeof(vet[0]);
    int colunas = sizeof(vet[0]) / sizeof(vet[0][0]);

    printf("\n\n\n\n\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < linhas - i - 1; j++) {
            printf(" ");
        }

        for (int j = 0; j <= i; j++){
            printf("%d ", vet[i][j]);

        }
        printf("\n");
        Sleep(60);
    }
    printf("\n\n\n\n\n\n");
}

void clear() {

}

int main() {

    draw();
    return 0;
}

// vet[10][15]
// 10 e a quantidade de linhas
// 15 e a quantidade de colunas
