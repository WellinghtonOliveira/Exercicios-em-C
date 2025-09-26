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

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum eDirection dir;

void draw();
void input();
void logic();

void setup()
{
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

int main()
{
    srand(time(0));
    setup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }
    return 0;
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
}

void draw()
{
    system("cls");
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
            {
                printf("O");
            }
            else if (i == fruitY && j == fruitX)
            {
                printf("F");
            }
            else
            {
                int print = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        print = 1;
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
    printf("\nScore: %d\n", score);
}

void input()
{
    if (_getch())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

// FUNCAO PARA DESENHAR
// FUNCAO PARA APAGAR
// FUNCAO PARA GERAR AS FRUTAS
// FUNCAO PARA GERAR O MAPA
