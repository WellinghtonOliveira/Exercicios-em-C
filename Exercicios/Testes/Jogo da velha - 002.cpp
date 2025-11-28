#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>

void desenhaTela(char);
void conf_tela(); // Configuração inicial da tela
void attInputs();
void attPosPlayer(char);

const int tamanho = 42; // 42 tamanho padrão

int posPlayer[3][3] = {};
int coordenadasPlayer[2] = {};

char tela[tamanho][tamanho] = {};



int main() {
	attPosPlayer('i');
	
	conf_tela();
	
	attInputs();
	
	system("pause");
	return 0;
}


void desenhaTela(char input = 'p') {	
	char tecla = input;
	
	int div = tamanho / 3;
	
	// Muda a matriz
	for (int a = 0; a < tamanho; a++) {
		for(int b = 0; b < tamanho; b++) {
			// Logica da tela
			
			if (b >= div - 1 && b <= div + 1 || b >= (div * 2) - 1 && b <= (div * 2) + 1 ||
			    a >= div - 1 && a <= div + 1 || a >= (div * 2) - 1 && a <= (div * 2) + 1) {
				tela[a][b] = '#';
			}else {
				tela[a][b] = ' ';
			}
		}
	}

	// Desenha na tela
	printf("\n\n\n\n\n\n");
	for (int a = 0; a < tamanho; a++) {
		printf("				");
		for(int b = 0; b < tamanho; b++) {
			
			
			if (tecla == 'w' || tecla == 'W') {
				if (b == div + 1 && a >= 0 && a <= div - 1 ||
					b == (div * 2) - 1 && a >= 0 && a <= div - 1 ||
					a == 0 && b >= div + 1 && b <= (div * 2) - 1 ||
					a == div - 1 && b >= div + 1 && b <= (div * 2) - 1) {
					
					printf("- ");
					//tela[a][b] = '-';
					continue;	
				}
			}
				
			// meio
			if (b == div + 1 && a >= div + 1 && a <= (div * 2) - 1 ||
			    b == (div * 2) - 1 && a >= div + 1 && a <= (div * 2) - 1 ||
				a == div + 1 && b >= div + 1 && b <= (div * 2) - 1 ||
				a == (div * 2) - 1 && b >= div + 1 && b <= (div * 2) - 1) {
				
				printf("- ");
				//tela[a][b] = '-';
				continue;
			}
		
			printf("%c ", tela[a][b]);	
		}
		printf("\n");
	}
}

void attInputs() {
	char tecla;
	
	while (true) {
		
		if (kbhit()) {
			tecla = getch();
			
			switch (tecla) {
				case 'w': case 'W':
					attPosPlayer('w');
					break;
				case 's': case 'S':
					attPosPlayer('s');
					break;
				case 'a': case 'A':
					attPosPlayer('a');
					break;
				case 'd': case 'D':
					attPosPlayer('d');
					break;
				
				default:
					continue;
			}
		
			tecla = '\0';
		}
		
		Sleep(100);
	}
}

void attPosPlayer(char conf = 'p') {
	// configuração de inicialização
	if (conf == 'i') {
		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				posPlayer[a][b] = 0;
					
				if (a == 1 && b == 1) {
					posPlayer[a][b] = 1;	
				}
			}
		}
	}
	
	
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			
			switch (conf){
				case 'w': case 'W':
					if (posPlayer[a][b] == 1 && a > 0) {
							posPlayer[a][b] = 0;
							posPlayer[a - 1][b] = 1; 
						}
					}
					break;
				
				case 's': case 'S':
					if (posPlayer[a][b] == 1 && a < 2) {
						posPlayer[a][b] = 0;
						posPlayer[a + 1][b] = 1; 
					}
					break;
						
				default:
					break;
			}
				
//			if (posPlayer[a][b] == 1) {
//				coordenadasPlayer[0] = a;
//				coordenadasPlayer[1] = b;
//				desenhaTela();
//				return;
//			}
		}
		
	}

	
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			printf("%d ", posPlayer[a][b]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void conf_tela() {

    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_RESTORE);  // garante que pode diminuir

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Definir buffer
    COORD size;
    size.X = 200;
    size.Y = 200;
    SetConsoleScreenBufferSize(hConsole, size);

    // Definir janela
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = 150;
    rect.Bottom = 55;
    SetConsoleWindowInfo(hConsole, TRUE, &rect);

    // Estrutura para configurar fonte
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;      // largura automática
    cfi.dwFontSize.Y = 10;     // altura da fonte (o que você quer)
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;

    // Nome da fonte (Consolas é a mais estável no CMD)
    wcscpy_s(cfi.FaceName, L"Consolas");

    // Aplicar a fonte
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

}