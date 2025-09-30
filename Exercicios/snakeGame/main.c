#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;
int gameOver;

// velocidade da cobra
int snakeDelay = 120; // ms entre movimentos

// controle do FPS
double lastTime;
int frames = 0;
double fps = 0;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum eDirection dir;

// reposiciona cursor no terminal (sem piscar)
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setup()
{
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
    lastTime = (double)clock() / CLOCKS_PER_SEC;
}

void draw()
{
    gotoxy(0, 0); // volta pro canto superior
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O"); // cabeça
            else if (i == fruitY && j == fruitX)
                printf("+"); // fruta
            else
            {
                int print = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        print = 1;
                        break;
                    }
                }
                if (!print)
                    printf(" ");
            }
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\nScore: %d   FPS: %.2f\n", score, fps);
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

void updateFPS()
{
    frames++;
    double currentTime = (double)clock() / CLOCKS_PER_SEC;
    if (currentTime - lastTime >= 1.0)
    {
        fps = frames / (currentTime - lastTime);
        frames = 0;
        lastTime = currentTime;
    }
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE; // FALSE = esconde o cursor
    SetConsoleCursorInfo(consoleHandle, &info);
}


int main()
{
    srand(time(0));
    setup();
    hideCursor();

    DWORD lastUpdate = GetTickCount();

    while (!gameOver)
    {
        input();

        // cobra só anda a cada snakeDelay ms
        if (GetTickCount() - lastUpdate >= (DWORD)snakeDelay)
        {
            logic();
            lastUpdate = GetTickCount();
        }

        draw();       // sempre redesenha
        updateFPS();  // atualiza FPS
        Sleep(1);     // descanso mínimo (mantém FPS alto)
    }

    printf("\nGame Over!\n");
    return 0;
}
