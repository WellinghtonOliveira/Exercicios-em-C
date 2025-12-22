#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

/* ================= CONFIG ================= */
#define TAB 3
#define BLOCO 8              // tamanho quadrado de cada célula
#define TAM (TAB * BLOCO)    // tamanho total do tabuleiro

/* ================= VARIÁVEIS ================= */
char tabuleiro[TAB][TAB];
int cursorX = 1;
int cursorY = 1;
char jogador = 'X';

/* ================= PROTÓTIPOS ================= */
void conf_tela();
void resetarJogo();
void desenharTela();
void desenharCelula(int ty, int tx, int offY, int offX);
void desenharX(int y, int x);
void desenharO(int y, int x);
void inputLoop();
bool checarVitoria(char p);

/* ================= MAIN ================= */
int main() {
    conf_tela();
    resetarJogo();
    desenharTela();
    inputLoop();
    return 0;
}

/* ================= CONFIG TELA ================= */
void conf_tela() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT r = {0, 0, 1, 1};
    SetConsoleWindowInfo(h, TRUE, &r);

    COORD size = {120, 40};
    SetConsoleScreenBufferSize(h, size);

    SMALL_RECT rect = {0, 0, 119, 39};
    SetConsoleWindowInfo(h, TRUE, &rect);

    CONSOLE_FONT_INFOEX f = { sizeof(f) };
    f.dwFontSize.Y = 16;
    wcscpy(f.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(h, FALSE, &f);
}

/* ================= RESET ================= */
void resetarJogo() {
    for (int y = 0; y < TAB; y++)
        for (int x = 0; x < TAB; x++)
            tabuleiro[y][x] = ' ';

    cursorX = 1;
    cursorY = 1;
    jogador = 'X';
}

/* ================= DESENHO ================= */
void desenharTela() {
    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int largura = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int altura  = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int offX = (largura - TAM) / 2;
    int offY = (altura  - TAM) / 2;

    for (int y = 0; y < TAM + offY; y++) printf("\n");

    for (int y = 0; y < TAM; y++) {
        for (int i = 0; i < offX; i++) printf(" ");

        for (int x = 0; x < TAM; x++) {

            if (x % BLOCO == 0 && x != 0) { printf("|"); continue; }
            if (y % BLOCO == 0 && y != 0) { printf("-"); continue; }

            desenharCelula(y, x, offY, offX);
        }
        printf("\n");
    }

    printf("\n");
    for (int i = 0; i < offX; i++) printf(" ");
    printf("Jogador atual: %c\n", jogador);
}

/* ================= CÉLULA ================= */
void desenharCelula(int ty, int tx, int offY, int offX) {
    int cx = tx / BLOCO;
    int cy = ty / BLOCO;
    int lx = tx % BLOCO;
    int ly = ty % BLOCO;

    if (cx == cursorX && cy == cursorY) {
        if (lx == 0 || lx == BLOCO - 1 ||
            ly == 0 || ly == BLOCO - 1) {
            printf("#");
            return;
        }
    }

    if (tabuleiro[cy][cx] == 'X') {
        desenharX(ly, lx);
        return;
    }

    if (tabuleiro[cy][cx] == 'O') {
        desenharO(ly, lx);
        return;
    }

    printf(" ");
}

/* ================= X ================= */
void desenharX(int y, int x) {
    if (x == y || x == BLOCO - y - 1)
        printf("X");
    else
        printf(" ");
}

/* ================= O ================= */
void desenharO(int y, int x) {
    int c = BLOCO / 2;
    int r = c - 1;

    int dx = x - c;
    int dy = y - c;
    int d = dx * dx + dy * dy;

    if (d >= r * r - 2 && d <= r * r + 2)
        printf("O");
    else
        printf(" ");
}

/* ================= VITÓRIA ================= */
bool checarVitoria(char p) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == p && tabuleiro[i][1] == p && tabuleiro[i][2] == p) return true;
        if (tabuleiro[0][i] == p && tabuleiro[1][i] == p && tabuleiro[2][i] == p) return true;
    }

    if (tabuleiro[0][0] == p && tabuleiro[1][1] == p && tabuleiro[2][2] == p) return true;
    if (tabuleiro[0][2] == p && tabuleiro[1][1] == p && tabuleiro[2][0] == p) return true;

    return false;
}

/* ================= INPUT ================= */
void inputLoop() {
    char t;

    while (1) {
        if (kbhit()) {
            t = getch();

            switch (t) {
                case 'w': case 'W': if (cursorY > 0) cursorY--; break;
                case 's': case 'S': if (cursorY < 2) cursorY++; break;
                case 'a': case 'A': if (cursorX > 0) cursorX--; break;
                case 'd': case 'D': if (cursorX < 2) cursorX++; break;

                case ' ':
                    if (tabuleiro[cursorY][cursorX] == ' ') {
                        tabuleiro[cursorY][cursorX] = jogador;

                        if (checarVitoria(jogador)) {
                            desenharTela();
                            Sleep(1000);
                            resetarJogo();
                        } else {
                            jogador = (jogador == 'X') ? 'O' : 'X';
                        }
                    }
                    break;
            }
            desenharTela();
        }
        Sleep(60);
    }
}
