#include <stdio.h>
#include <windows.h>
#include <conio.h>

void habilitarANSI() {
	SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void limparTela() {
     printf("\033[H"); 
}

int main() {
	habilitarANSI();

	int tamanhoQuadrado = 20;
	int posX = tamanhoQuadrado / 2, posY = tamanhoQuadrado / 2;
	int dirX = 0, dirY = 0, v = 0;	
	
	char areaMatriz[tamanhoQuadrado][tamanhoQuadrado];
	char tecla;
	
	while (true) {
		printf("\n\n");
		
		// Escreve na matriz
		for (int a = 0; a < tamanhoQuadrado; a++) {
			for (int b = 0; b < tamanhoQuadrado; b++) {
//				if (v == 1) {
//					areaMatriz[k][j] = '0';
//					continue;
//				}
				
				if (a == tamanhoQuadrado - tamanhoQuadrado || a == tamanhoQuadrado - 1 || 
					b == tamanhoQuadrado - tamanhoQuadrado || b == tamanhoQuadrado - 1 ) {
					areaMatriz[a][b] = '#';
					continue;
				}
				
				areaMatriz[a][b] = '-';
			}
		}
		
		//personagem				
		int novaPosX = posX + dirX;
		int novaPosY = posY + dirY;
		if (v == 1) {
			posX = novaPosX;
			posY = novaPosY;
			areaMatriz[novaPosY][novaPosX] = 'O';
		}else {
			areaMatriz[posY][posX] = 'O';
		}

		// Coordenadas do desenho		
//		if (v == 1) {
//			if (k <= 19) {
//				j++;
//			}else {
//				k++;
//			}
//		}
		
		// Desenhar na tela
		for (int a = 0; a < tamanhoQuadrado; a++) {
			printf("   ");
			for (int b = 0; b < tamanhoQuadrado; b++) {			
				printf("%c ", areaMatriz[a][b]);
			}
			printf("\n");
		}
		
		if (_kbhit()) { // Verifica se uma tecla foi pressionada
            tecla = _getch(); // Coleta a tecla

            switch (tecla) {
                case 'w':
                case 'W':
                    printf("Mover para Cima\n");
                    break;
                case 's':
                case 'S':
                    printf("Mover para Baixo\n");
                    break;
                case 'a':
                case 'A':
                	dirX = -1;
                    printf("Mover para Esquerda\n");
                    break;
                case 'd':
                case 'D':
                	dirX = 1;
                    printf("Mover para Direita\n");
                    break;
                case 'q':
                case 'Q':
                    printf("Saindo...\n");
                    return 0; // Sai do programa
            }
            v = 1;
		}
		
		printf("\n\n");
		Sleep(100);
		limparTela();
	}
	
}