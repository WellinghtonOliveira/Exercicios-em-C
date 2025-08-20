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

            if (tecla == ' ')
            {
                system("cls");

                // Pulando uma linha no arquivo log txt
                palavra[count++] = '\n';

                // Salavando arquivo
                fptr = fopen("logs.txt", "a");
                fprintf(fptr, palavra);
                fclose(fptr);
             
                palavra[0] = '\0';
                count = 0;
                continue;
            }
            
            palavra[count++] = tecla;

            if (tecla == 27)
                {
                break;
            }
        }
    }

    return 0;
}