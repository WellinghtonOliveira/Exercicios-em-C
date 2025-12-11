#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <stdbool.h>

void desenhaTela(char);
void conf_tela(); // Configuração inicial da tela
void attInputs();
bool isWindowsTerminal();
void attPosPlayer(char);

const int tamanho = 42; // 42 tamanho padrão

int posPlayer[3][3] = {};
int coordenadasPlayer[2] = {};

char tela[tamanho][tamanho] = {};



int main() {
	attPosPlayer('i');
	
	conf_tela();
	desenhaTela('i');
	
	attInputs();
	return 0;
}


void desenhaTela(char input = 'p') {
	system("cls");
	char tecla = input;
	
	int controleA = 0, controleB = 3;
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
			
			for (int y = 0; y < 3; y++) { // Verifica coodernadas do player
				for (int x = 0; x < 3; x++) {
					if (posPlayer[y][x] == 1) {
						coordenadasPlayer[0] = y;
						coordenadasPlayer[1] = x; 
					}
				}
			}
			
			if (coordenadasPlayer[0] == 0 && coordenadasPlayer[1] == 0) {
				
				// Canto superior esquerdo
				if (b == 0 && a >= 0 && a <= div - 1 ||
					b == div - 1 && a >= 0 && a <= div - 1 ||
					a == 0 && b <= div - 1 ||
					a == div - 1 && b <= div - 1) {
					
					printf("- "); 
					continue;	
				}
			
			}else if (coordenadasPlayer[0] == 0 && coordenadasPlayer[1] == 1) {
				
				// meio superior
				if (b == div + 1 && a >= 0 && a <= div - 1 ||
					b == (div * 2) - 1 && a >= 0 && a <= div - 1 ||
					a == 0 && b >= div + 1 && b <= (div * 2) - 1 ||
					a == div - 1 && b >= div + 1 && b <= (div * 2) - 1) {
					
					printf("- ");
					continue;	
				}
				
			}else if (coordenadasPlayer[0] == 0 && coordenadasPlayer[1] == 2) {
				
				// Canto superior direito
				if (b == (div * 2) + 1 && a <= div - 1 ||
					b == (div * 3) - 1 && a <= div - 1 ||
					a == 0 && b >= (div * 2) + 1 ||
					a == div - 1 && b >= (div * 2) + 1) {
					
					printf("- ");
					continue;	
				}
			
			}else if (coordenadasPlayer[0] == 1 && coordenadasPlayer[1] == 0) {
				
				// Meio esquerdo
				if (b == 0 && a <= (div * 2) - 1 && a >= div + 1 ||
					b == div - 1 && a <= (div * 2) - 1 && a >= div + 1 ||
					a == div + 1 && b <= div - 1 ||
					a == (div * 2) - 1 && b <= div - 1) {
					
					printf("- ");
					continue;
				}
			
			}else if (coordenadasPlayer[0] == 1 && coordenadasPlayer[1] == 1) {
				
				// Meio
				if (b == div + 1 && a >= div + 1 && a <= (div * 2) - 1 ||
				    b == (div * 2) - 1 && a >= div + 1 && a <= (div * 2) - 1 ||
					a == div + 1 && b >= div + 1 && b <= (div * 2) - 1 ||
					a == (div * 2) - 1 && b >= div + 1 && b <= (div * 2) - 1) {
					
					printf("- ");
					continue;
				}
				
			}else if (coordenadasPlayer[0] == 1 && coordenadasPlayer[1] == 2) {
			  
				// Meio direito 
				if (b == (div * 2) + 1 && a <= (div * 2) - 1 && a >= div + 1 ||
					b == (div * 3) - 1 && a <= (div * 2) - 1 && a >= div + 1 || 
					a == div + 1 && b >= (div * 2) + 1 ||
					a == (div * 2) - 1 && b >= (div * 2) + 1) {
					
					printf("- ");
					continue;
				}
			
			}else if (coordenadasPlayer[0] == 2 && coordenadasPlayer[1] == 0) {
			 
				// Canto inferior esquerdo
				if (b == 0 && a >= (div * 2) + 1 ||
					b == div - 1 && a >= (div * 2) + 1 ||
					a == (div * 2) + 1 && b <= div - 1 ||
					a == (div * 3) - 1 && b <= div - 1) {
					
					printf("- ");
					continue;	
				}
			
			}else if (coordenadasPlayer[0] == 2 && coordenadasPlayer[1] == 1) {
			
				// Meio Inferior
				if (b == div + 1 && a >= (div * 2) + 1 ||
					b == (div * 2) - 1 && a >= (div * 2) + 1 ||
					a == (div * 2) + 1 && b >= div + 1 && b <= (div * 2) - 1 ||
					a == (div * 3) - 1 && b >= div + 1 && b <= (div * 2) - 1) {
					
					printf("- ");
					continue;	
				}
			
			}else if (coordenadasPlayer[0] == 2 && coordenadasPlayer[1] == 2) {
			
				// Canto inferior direito
				if (b == (div * 2) + 1 && a >= (div * 2) + 1 ||
					b == (div * 3) - 1 && a >= (div * 2) + 1 ||
					a == (div * 2) + 1 && b >= (div * 2) + 1 ||
					a == (div * 3) - 1 && b >= (div * 2) + 1) {
					
					printf("- ");
					continue;	
				}
			
			}
			
			
			if (input == 'i') {
				// meio
				if (b == div + 1 && a >= div + 1 && a <= (div * 2) - 1 ||
				    b == (div * 2) - 1 && a >= div + 1 && a <= (div * 2) - 1 ||
					a == div + 1 && b >= div + 1 && b <= (div * 2) - 1 ||
					a == (div * 2) - 1 && b >= div + 1 && b <= (div * 2) - 1) {
					
					printf("- ");
					continue;
				}

				if (a >= 1 && a <= 11 && b <= 11 && b >= 1) {
					
					if (b == a || b == (11 - a + 1) ||
						b == a - 1 || b == (11 - a + 2) || 
						b == a + 1 || b == (11 - a)) {
						
						printf("O ");
						continue;
					}
					
					controleA++;
					controleB++;
					printf("  ");
					continue;
				}
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
				
				case 'w':
					if (posPlayer[a][b] == 1 && a > 0) {
						posPlayer[a][b] = 0;
						posPlayer[a -= 1][b] = 1;
						desenhaTela('w');
					}
					break;
				
				case 's':
					if (posPlayer[a][b] == 1 && a < 2) {
						posPlayer[a][b] = 0;
						posPlayer[a += 1][b] = 1;
						desenhaTela('s');
					}
					break;
						
				case 'd':
					if (posPlayer[a][b] == 1 && b < 2) {
						posPlayer[a][b] = 0;
						posPlayer[a][b += 1] = 1;
						desenhaTela('d');
					}
					break;
				
				case 'a':
					if (posPlayer[a][b] == 1 && b > 0) {
						posPlayer[a][b] = 0;
						posPlayer[a][b -= 1] = 1;
						desenhaTela('a');
					}
					break;
				
				default:
					break;
			}
		}
	}
		
}

bool isWindowsTerminal() {
    // Windows Terminal injeta a variável WT_SESSION
    DWORD len = GetEnvironmentVariableA("WT_SESSION", NULL, 0);
    return (len > 0);
}

void conf_tela() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_RESTORE);

    bool terminal = isWindowsTerminal();

    // -----------------------------
    //  1. Ajuste de janela
    // -----------------------------
    if (!terminal) {
        // Modo completo — funciona no Console Clássico (Win10 e Win11)
        SMALL_RECT small = {0, 0, 1, 1};
        SetConsoleWindowInfo(hConsole, TRUE, &small);

        COORD size = {200, 200};
        SetConsoleScreenBufferSize(hConsole, size);

        SMALL_RECT rect = {0, 0, 150, 60};
        SetConsoleWindowInfo(hConsole, TRUE, &rect);
    } else {
        // Fallback mínimo (Windows Terminal limita comandos)
        COORD size = {150, 60};
        SetConsoleScreenBufferSize(hConsole, size);
    }

    // -----------------------------
    //  2. Ajuste de fonte
    // -----------------------------
    // Fonte só funciona fora do Windows Terminal
    if (!terminal) {
        CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
        cfi.dwFontSize.Y = 10;
        wcscpy_s(cfi.FaceName, L"Consolas");
        SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    }

}
