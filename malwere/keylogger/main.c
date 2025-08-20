#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main()
{
    FILE *fptr;

    char tecla, palavra[100];
    int count = 0;

    printf("Precione ESC para sair:\n");

    while (1)
    {
        if (_kbhit())
        {
            tecla = _getch();

            if (tecla == 8)
            {
                printf("\n%d\n", count);
                palavra[count - 1] = '\0';
                printf("\n%d\n", count);
            }

            if (tecla == 32 || tecla == 13)
            {
                if (palavra[0] != '\0')
                {
                    system("cls");

                    // Finalizando o arquivo log txt
                    palavra[count] = '\0';

                    // Salavando arquivo
                    fptr = fopen("logs.txt", "a");
                    fprintf(fptr, "%s\n", palavra);
                    fclose(fptr);

                    palavra[0] = '\0';
                    count = 0;
                    continue;
                }
            }

            printf("%c  ", tecla);
            palavra[count++] = tecla;

            if (tecla == 27)
                break;
        }
    }

    return 0;
}