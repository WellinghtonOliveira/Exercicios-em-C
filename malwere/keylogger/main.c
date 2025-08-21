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
                if (count <= 0  ) continue;
                palavra[count--] = '\0';
                system("cls");
                printf("%s", palavra);
                continue;
            }

            // TODO quando a palavra for umastring vazia nao pode apagar nada

            if (tecla == 32 || tecla == 13)
            {
                if (count > 0)
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
                }
                continue;
            }

            //  Salvando as teclas e montando a palavra
            palavra[count++] = tecla;

            printf("%c", tecla);
            if (tecla == 27)
                break;
        }
    }

    return 0;
}