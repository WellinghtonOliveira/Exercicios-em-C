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
    int dirX = 0, dirY = 0, v = 0, p = 0, vel = 300;

    char areaMatriz[tamanhoQuadrado][tamanhoQuadrado];
    int tamanhoCobra = 1;
    char cobraVida[tamanhoQuadrado][tamanhoQuadrado] = {};

    char tecla;
    char wall = '#';
    char head = 'O';
    char body = 'o';
    char point = '+';

    while (true) {

        // 1. Reduz vida do corpo
        for (int a = 0; a < tamanhoQuadrado; a++) {
            for (int b = 0; b < tamanhoQuadrado; b++) {
                if (cobraVida[a][b] > 0) cobraVida[a][b]--;
            }
        }

        // 2. Movimento da cobra
        int novaPosX = posX + dirX;
        int novaPosY = posY + dirY;

        if (v == 1) {

            // colisão com a parede
            if (novaPosY == 0 || novaPosY == tamanhoQuadrado - 1 ||
                novaPosX == 0 || novaPosX == tamanhoQuadrado - 1) {

                system("pause");
                system("cls");
                return 0;
            }

            // comeu ponto
            if (novaPosY == pointY && novaPosX == pointX) {
                tamanhoCobra++;
                p += 10;
                
                if (p >= 200 && vel >= 0) vel -= 5;

                // novo ponto
                do {
                	pointX = tamanhoQuadrado / 2;
                	pointY = tamanhoQuadrado / 2;
                	
                    pointX = pontosAle(tamanhoQuadrado);
                    pointY = pontosAle(tamanhoQuadrado);
                } while (pointX <= 1 || pointX >= tamanhoQuadrado - 2 || 
						 pointY <= 1 || pointY >= tamanhoQuadrado - 2 ||
            			 cobraVida[novaPosY][novaPosX] == tamanhoCobra);
			}

            // atualiza cabeça
            cobraVida[novaPosY][novaPosX] = tamanhoCobra;
            posX = novaPosX;
            posY = novaPosY;
        }

        // 3. Limpa e redesenha matriz
        for (int a = 0; a < tamanhoQuadrado; a++) {
            for (int b = 0; b < tamanhoQuadrado; b++) {

                if (a == 0 || a == tamanhoQuadrado - 1 ||
                    b == 0 || b == tamanhoQuadrado - 1) {
                    areaMatriz[a][b] = wall;
                } else {
                    areaMatriz[a][b] = ' ';
                }
            }
        }

        // 4. Desenha ponto
        areaMatriz[pointY][pointX] = point;

        // 5. Desenha a cobra baseada em cobraVida
        for (int a = 0; a < tamanhoQuadrado; a++) {
            for (int b = 0; b < tamanhoQuadrado; b++) {

                if (cobraVida[a][b] == tamanhoCobra)
                    areaMatriz[a][b] = head;

                else if (cobraVida[a][b] > 0)
                    areaMatriz[a][b] = body;
            }
        }

        // 6. Caso ainda não tenha começado, desenha a cobra parada
        if (v == 0) {
            cobraVida[posY][posX] = tamanhoCobra;
            areaMatriz[posY][posX] = head;
        }

        // 7. Desenhar na tela
        printf("\n\n");
        for (int a = 0; a < tamanhoQuadrado; a++) {
            printf("   ");
            for (int b = 0; b < tamanhoQuadrado; b++) {
                printf("%c ", areaMatriz[a][b]);
            }
            printf("\n");
        }

        // 8. Input
        if (_kbhit()) {
            tecla = _getch();

            switch (tecla) {
                case 'w': case 'W':
                    dirX = 0; dirY = -1;
                    break;

                case 's': case 'S':
                    dirX = 0; dirY = 1;
                    break;

                case 'a': case 'A':
                    dirY = 0; dirX = -1;
                    break;

                case 'd': case 'D':
                    dirY = 0; dirX = 1;
                    break;

                case 'q': case 'Q':
                    return 0;
            }

            tecla = '\0';
            v = 1;
        }
		
		printf("\n");
		printf("  | Velocidade: %d\n", vel);	
		printf("  | Seus pontos: %d\n\n", p);
        Sleep(vel);
        limparTela();
    }
}
