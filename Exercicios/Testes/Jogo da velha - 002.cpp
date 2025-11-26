#include <stdio.h>
#include <iostream>
#include <windows.h>

void desenhaTela(int);
void conf_tela(); // Configuração inicial da tela

int main() {
	conf_tela();
	desenhaTela(42); // 42 tamanho padrao
	
	system("pause");
	return 0;
}

void desenhaTela(int tamanho) {
	char tela[tamanho][tamanho] = {};
	
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
			
			if (b == div + 1 && a >= div + 1 && a <= (div * 2) - 1 ||
			    b == (div * 2) - 1 && a >= div + 1 && a <= (div * 2) - 1 ||
				a == div + 1 && b >= div + 1 && b <= (div * 2) - 1 ||
				a == (div * 2) - 1 && b >= div + 1 && b <= (div * 2) - 1) {
				
				tela[a][b] = 'Z';
			}
		
			
		}
	}

	// Desenha na tela
	printf("\n\n\n\n\n\n");
	for (int a = 0; a < tamanho; a++) {
		printf("				");
		for(int b = 0; b < tamanho; b++) {
			
			printf("%c ", tela[a][b]);	
		}
		printf("\n");
	}
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