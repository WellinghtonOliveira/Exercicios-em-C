// server_windows_token.c
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5001
#define BUFFER_SIZE 2048

// configure aqui o token esperado (mesmo valor no cliente)
#define EXPECTED_TOKEN "MINHA_CHAVE_SECRETA_123"

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

    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erro no bind: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Servidor (token) esperando mensagens na porta %d...\n", PORT);

    char buffer[BUFFER_SIZE];

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr*)&client_addr, &addr_len);
        if (n == SOCKET_ERROR) {
            printf("recvfrom erro: %d\n", WSAGetLastError());
            continue;
        }
        buffer[n] = '\0';

        // Exemplo de formato para descoberta:
        // "quem_esta_ai:TOKEN_AQUI"
        // Para mensagens diretas poderíamos usar: "TOKEN_AQUI:mensagem..."

        // tenta dividir por ':' para separar comando/token/mensagem
        char *sep = strchr(buffer, ':');
        if (sep) {
            // separamos em prefix e resto
            size_t prefix_len = sep - buffer;
            char prefix[256];
            if (prefix_len >= sizeof(prefix)) prefix_len = sizeof(prefix)-1;
            strncpy(prefix, buffer, prefix_len);
            prefix[prefix_len] = '\0';
            char *rest = sep + 1;

            if (strcmp(prefix, "quem_esta_ai") == 0) {
                // rest contém o token enviado pelo cliente
                if (strcmp(rest, EXPECTED_TOKEN) == 0) {
                    // token válido: responde
                    char reply[] = "eu_sou_o_destino";
                    sendto(sockfd, reply, (int)strlen(reply), 0,
                           (struct sockaddr*)&client_addr, addr_len);
                    printf("Broadcast autorizado de %s (token válido). Respondi.\n", inet_ntoa(client_addr.sin_addr));
                } else {
                    printf("Broadcast com token inválido de %s ('%s')\n", inet_ntoa(client_addr.sin_addr), rest);
                    // opcional: não responder
                }
            } else {
                // possivelmente uma mensagem direta: formato "TOKEN:mensagem..."
                if (strcmp(prefix, EXPECTED_TOKEN) == 0) {
                    printf("Mensagem autorizada de %s: %s\n", inet_ntoa(client_addr.sin_addr), rest);
                    // opcional: responder ACK
                    char ack[] = "ack";
                    sendto(sockfd, ack, (int)strlen(ack), 0, (struct sockaddr*)&client_addr, addr_len);
                } else {
                    printf("Mensagem com token inválido de %s. Ignorando.\n", inet_ntoa(client_addr.sin_addr));
                }
            }
        } else {
            // mensagem sem ':' — ignorar
            printf("Mensagem sem formato esperado de %s: %s\n", inet_ntoa(client_addr.sin_addr), buffer);
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
