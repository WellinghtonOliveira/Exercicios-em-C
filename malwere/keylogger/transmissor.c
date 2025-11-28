// Server
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 5001
#define BUFFER_SIZE 2048
#define EXPECTED_TOKEN "256dc29b97c147d8769a61df36bfc67f52ed4fba4e4523bef7730df01c10c8a1828ea877826e889112bf6a14da88555bc552ec60e510ff3233b2f54774e41445"
#define FILE_TO_SEND "logs.txt"

void transmissorLog();

int main() {

    transmissorLog();
    
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

// gcc transmissor.c -o transmissor.exe -lws2_32 -Wall -Wextra -O2