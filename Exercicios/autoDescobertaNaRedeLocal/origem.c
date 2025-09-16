#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // linka a biblioteca Winsock

#define PORT 5001
#define BUFFER_SIZE 1024

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

    // habilita broadcast
    BOOL broadcastEnable = TRUE;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcastEnable, sizeof(broadcastEnable));

    struct sockaddr_in broadcast_addr;
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    char buffer[BUFFER_SIZE] = "quem_esta_ai";

    // envia broadcast
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
    printf("Broadcast de descoberta enviado...\n");

    // espera resposta do destino
    struct sockaddr_in recv_addr;
    int addr_len = sizeof(recv_addr);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&recv_addr, &addr_len);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Destino encontrado: %s -> %s\n", buffer, inet_ntoa(recv_addr.sin_addr));

        // envia mensagem direta para o destino
        char mensagem[] = "Ola destino, mensagem direta!";
        sendto(sockfd, mensagem, strlen(mensagem), 0,
               (struct sockaddr*)&recv_addr, addr_len);
        printf("Mensagem enviada diretamente para o destino!\n");
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
