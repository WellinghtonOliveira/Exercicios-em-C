// client_recv_file.c
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 5001
#define BUFFER_SIZE 2048
#define TOKEN "256dc29b97c147d8769a61df36bfc67f52ed4fba4e4523bef7730df01c10c8a1828ea877826e889112bf6a14da88555bc552ec60e510ff3233b2f54774e41445"

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    int addr_len = sizeof(server_addr);

    // Broadcast
    BOOL broadcast = TRUE;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_BROADCAST;

    char msg[BUFFER_SIZE];
    sprintf(msg, "quem_esta_ai:%s", TOKEN);
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&server_addr, addr_len);

    char buffer[BUFFER_SIZE];
    FILE *fp = NULL;

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr*)&server_addr, &addr_len);
        buffer[n] = '\0';

        if (strcmp(buffer, "eu_sou_o_destino") == 0) {
            printf("Servidor encontrado em %s\n", inet_ntoa(server_addr.sin_addr));
            fp = fopen("saida.txt", "wb");
            continue;
        }

        if (fp) {
            if (strcmp(buffer, "EOF") == 0) {
                fclose(fp);
                printf("Arquivo recebido com sucesso.\n");
                break;
            } else {
                fwrite(buffer, 1, n, fp);
            }
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
