#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // linka a biblioteca Winsock

#define PORT 5001
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Erro ao iniciar Winsock\n");
        return 1;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        printf("Erro ao criar socket\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Erro no bind\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Servidor destino esperando mensagens...\n");

    char buffer[BUFFER_SIZE];

    while (1)
    {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        if (n > 0)
        {
            buffer[n] = '\0';
            printf("Recebido de %s:%d -> %s\n",
                   inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port),
                   buffer);

            // responde se for broadcast de descoberta
            if (strcmp(buffer, "quem_esta_ai") == 0)
            {
                char reply[] = "eu_sou_o_destino";
                sendto(sockfd, reply, strlen(reply), 0,
                       (struct sockaddr *)&client_addr, addr_len);
            }
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
