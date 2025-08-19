#include <stdio.h>
#include <conio.h>

int main()
{

    char tecla;

    printf("Precione ESC para sair:\n");

    while (1)
    {
        if (_kbhit())
        {
            tecla = _getch();
            printf("Tecla pressionada: %c\n\n", tecla);

            if (tecla == 27)
            {
                break;
            }
        }
    }

    return 0;
}