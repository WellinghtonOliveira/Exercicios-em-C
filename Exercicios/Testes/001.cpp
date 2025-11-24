#include <stdio.h>
#include <windows.h>

int main() {
	int tamanhoQuadrado = 20;
	int areaMatriz[tamanhoQuadrado][tamanhoQuadrado];
	int k = 0, j = 0, v = 0;	
	
	
	while (true) {
		// Escreve na matriz
		for (int a = 0; a < tamanhoQuadrado; a++) {
			for (int b = 0; b < tamanhoQuadrado; b++) {
				if (v == 1) {
					areaMatriz[k][j] = 8;
				}
				
				areaMatriz[a][b] = 0;
			}
		}
	
		// Desenhar na tela
		for (int a = 0; a < tamanhoQuadrado; a++) {
			printf("   ");
			for (int b = 0; b < tamanhoQuadrado; b++) {			
				printf("%d ", areaMatriz[a][b]);
			}
			printf("\n");
		}
		
		
		v = 1;
		Sleep(1000);
		system("cls");
	}
	
}