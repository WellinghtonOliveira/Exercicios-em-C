// client_windows_token.c
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5001
#define BUFFER_SIZE 2048

// mesmo token do servidor
#define MY_TOKEN "MINHA_CHAVE_SECRETA_123"

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("Erro ao iniciar Winsock\n");
        return 1;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Erro ao criar socket\n");
        WSACleanup();
        return 1;
    }

    BOOL broadcastEnable = TRUE;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcastEnable, sizeof(broadcastEnable));

    struct sockaddr_in broadcast_addr;
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    char buffer[BUFFER_SIZE];

    // planejamento: tentar descoberta em loop até receber resposta válida do servidor
    struct sockaddr_in srv_addr;
    int srv_addr_len = sizeof(srv_addr);
    int found = 0;

    // timeout no recv
    int timeout_ms = 3000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout_ms, sizeof(timeout_ms));

    while (!found) {
        // enviar broadcast com token: "quem_esta_ai:MY_TOKEN"
        char msg[512];
        snprintf(msg, sizeof(msg), "quem_esta_ai:%s", MY_TOKEN);
        sendto(sockfd, msg, (int)strlen(msg), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        printf("Broadcast enviado (com token). Aguardando resposta...\n");

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&srv_addr, &srv_addr_len);
        if (n == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAETIMEDOUT) {
                printf("Sem resposta (timeout). Tentando de novo em 2s...\n");
                Sleep(2000);
                continue;
            } else {
                printf("Erro no recvfrom: %d\n", err);
                Sleep(2000);
                continue;
            }
        }
        buffer[n] = '\0';
        if (strcmp(buffer, "eu_sou_o_destino") == 0) {
            printf("Servidor autenticado encontrado em %s\n", inet_ntoa(srv_addr.sin_addr));
            found = 1;
            break;
        } else {
            printf("Resposta inesperada: %s\n", buffer);
            Sleep(2000);
        }
    }

    // agora enviar mensagem direta com token prefixando: "MY_TOKEN:conteudo"
    if (found) {
        char direct[BUFFER_SIZE];
        snprintf(direct, sizeof(direct), "%s:%s", MY_TOKEN, "Mensagem secreta do cliente para o destino");
        sendto(sockfd, direct, (int)strlen(direct), 0, (struct sockaddr*)&srv_addr, srv_addr_len);
        printf("Mensagem direta enviada para %s\n", inet_ntoa(srv_addr.sin_addr));

        // opcional: aguardar ack
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&srv_addr, &srv_addr_len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Resposta do servidor: %s\n", buffer);
        } else {
            printf("Sem ack ou erro: %d\n", WSAGetLastError());
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
