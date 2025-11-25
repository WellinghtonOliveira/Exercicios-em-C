#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int pontosAle(int tamanhoQuadrado) {
	srand(time(NULL));
	return rand() % tamanhoQuadrado;
}

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
	int pointX = pontosAle(tamanhoQuadrado);
	int pointY = pontosAle(tamanhoQuadrado);
	int dirX = 0, dirY = 0, v = 0, p = 0;	
	
	char areaMatriz[tamanhoQuadrado][tamanhoQuadrado];
	char tecla;
	char wall = '#';
	char head = 'O';
	char body = 'o';
	char point = '+';
	
	while (true) {
		printf("\n\n");
		// Escreve na matriz
		for (int a = 0; a < tamanhoQuadrado; a++) {
			for (int b = 0; b < tamanhoQuadrado; b++) {
							
				if (a == tamanhoQuadrado - tamanhoQuadrado || a == tamanhoQuadrado - 1 || 
					b == tamanhoQuadrado - tamanhoQuadrado || b == tamanhoQuadrado - 1 ) {
					areaMatriz[a][b] = wall;
					continue;
				}
				
				areaMatriz[a][b] = '-';
			}
		}
		

		// Personagem		
		int novaPosX = posX + dirX;
		int novaPosY = posY + dirY;
		
		if (v == 1) {
			posX = novaPosX;
			posY = novaPosY;
			
			// Verifica colisão com a parede
			if (posY == tamanhoQuadrado - tamanhoQuadrado || posY == tamanhoQuadrado - 1 || 
				posX == tamanhoQuadrado - tamanhoQuadrado || posX == tamanhoQuadrado - 1 ) {
				
				system("pause");
				system("cls");
				return 0;
			}

			
			
			// Pontos
			if (novaPosY == pointY && novaPosX == pointX) {
				
				pointX = pontosAle(tamanhoQuadrado);
				pointY = pontosAle(tamanhoQuadrado);
				while (pointX <= 0 || pointY <= 0 ||
					pointX >= tamanhoQuadrado - 1 || pointY >= tamanhoQuadrado - 1) {
				
					pointX = pontosAle(tamanhoQuadrado);
					pointY = pontosAle(tamanhoQuadrado);
				}
				
			}
			
//			if (p > 0) {
//				int nY = novaPosY;
//				int nX = novaPosX;
//				
//				areaMatriz[novaPosY][novaPosX] = head;
//				areaMatriz[nY - 1][nX - 1] = body;
//				
//				nY = novaPosY;
//				nX = novaPosX;
//			}else {
//			}
		
			areaMatriz[pointY][pointX] = point;
			areaMatriz[novaPosY][novaPosX] = head;
		
		}else {
			
			areaMatriz[posY][posX] = head;
		}

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
                
                	dirX = 0;
					dirY = -1;
                    printf("Mover para Cima");
                    break;
                
				case 's':
                case 'S':
                
                	dirX = 0;
					dirY = 1;
                    printf("Mover para Baixo");
                    break;
                
				case 'a':
                case 'A':
                
                	dirY = 0;
					dirX = -1;
                    printf("Mover para Esquerda");
                    break;
                
				case 'd':
                case 'D':
                
                	dirY = 0;
					dirX = 1;
                    printf("Mover para Direita");
                    break;
                
				case 'q':
                case 'Q':
                    printf("Saindo...");
                    return 0; // Sai do programa
			}
			
			tecla = '\0';
            v = 1;
		}
		
		printf("\n\n");
		Sleep(200);
		limparTela();
	}
	
}