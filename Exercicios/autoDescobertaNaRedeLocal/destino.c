// server_combined.c
// Compilar: gcc server_combined.c -o server_combined.exe -lws2_32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT_UDP 5001
#define PORT_TCP 6000
#define BUFFER_SIZE 4096

// token compartilhado (configurar aqui)
#define EXPECTED_TOKEN "256dc29b97c147d8769a61df36bfc67f52ed4fba4e4523bef7730df01c10c8a1828ea877826e889112bf6a14da88555bc552ec60e510ff3233b2f54774e41445"

// helper: recebe exatamente to_read bytes (bloqueante)
int recv_all(SOCKET s, char *buf, int to_read) {
    int total = 0;
    while (total < to_read) {
        int r = recv(s, buf + total, to_read - total, 0);
        if (r <= 0) return r; // erro ou fechado
        total += r;
    }
    return total;
}

// thread TCP: aceita conexões e recebe arquivos
DWORD WINAPI tcp_thread(LPVOID param) {
    (void)param;
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) {
        printf("[TCP] Erro ao criar socket: %d\n", WSAGetLastError());
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_TCP);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("[TCP] Bind falhou: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        return 1;
    }

    if (listen(listen_sock, 5) == SOCKET_ERROR) {
        printf("[TCP] Listen falhou: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        return 1;
    }

    printf("[TCP] File server ouvindo em %d\n", PORT_TCP);

    while (1) {
        SOCKET client = accept(listen_sock, NULL, NULL);
        if (client == INVALID_SOCKET) {
            printf("[TCP] Accept erro: %d\n", WSAGetLastError());
            Sleep(1000);
            continue;
        }
        printf("[TCP] Cliente conectado. Lendo header...\n");

        // ler header até '\n'
        char header[1024];
        int hlen = 0;
        while (hlen < (int)sizeof(header)-1) {
            char c;
            int r = recv(client, &c, 1, 0);
            if (r <= 0) break;
            header[hlen++] = c;
            if (c == '\n') break;
        }
        if (hlen == 0) { closesocket(client); continue; }
        header[hlen] = '\0';

        // header: TOKEN:filename:size\n
        char *tok = strtok(header, ":");
        char *fname = strtok(NULL, ":");
        char *size_str = strtok(NULL, "\n");
        if (!tok || !fname || !size_str) {
            printf("[TCP] Header mal formatado: %s\n", header);
            closesocket(client);
            continue;
        }

        if (strcmp(tok, EXPECTED_TOKEN) != 0) {
            printf("[TCP] Token inválido recebido: %s\n", tok);
            closesocket(client);
            continue;
        }

        long long filesize = atoll(size_str);
        if (filesize <= 0) {
            printf("[TCP] Tamanho inválido: %s\n", size_str);
            closesocket(client);
            continue;
        }

        printf("[TCP] Recebendo arquivo '%s' (%lld bytes)...\n", fname, filesize);

        FILE *fp = fopen(fname, "wb");
        if (!fp) {
            printf("[TCP] Erro ao criar arquivo %s\n", fname);
            closesocket(client);
            continue;
        }

        char buf[BUFFER_SIZE];
        long long remaining = filesize;
        while (remaining > 0) {
            int toread = (remaining > BUFFER_SIZE) ? BUFFER_SIZE : (int)remaining;
            int r = recv_all(client, buf, toread);
            if (r <= 0) {
                printf("[TCP] Erro/EOF durante recv. Recebidos até agora: %lld\n", filesize - remaining);
                break;
            }
            fwrite(buf, 1, r, fp);
            remaining -= r;
        }
        fclose(fp);

        if (remaining == 0) {
            printf("[TCP] Arquivo %s salvo com sucesso.\n", fname);
            const char *ack = "FILE_RECEIVED\n";
            send(client, ack, (int)strlen(ack), 0);
        } else {
            printf("[TCP] Recepção incompleta de %s\n", fname);
            // remove(fname); // opcional
        }

        closesocket(client);
    }

    // nunca chega aqui
    closesocket(listen_sock);
    return 0;
}

// thread UDP: responde discovery se token correto; também aceita mensagens diretas opcionais
DWORD WINAPI udp_thread(LPVOID param) {
    (void)param;
    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("[UDP] Erro ao criar socket: %d\n", WSAGetLastError());
        return 1;
    }

    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_UDP);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("[UDP] Bind falhou: %d\n", WSAGetLastError());
        closesocket(sockfd);
        return 1;
    }

    printf("[UDP] Discovery ouvindo em %d\n", PORT_UDP);

    char buffer[BUFFER_SIZE];
    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (n == SOCKET_ERROR) {
            printf("[UDP] recvfrom erro: %d\n", WSAGetLastError());
            continue;
        }
        buffer[n] = '\0';
        // formato: "quem_esta_ai:TOKEN" ou "TOKEN:mensagem..."
        char *sep = strchr(buffer, ':');
        if (!sep) {
            printf("[UDP] Mensagem sem formato de %s: %s\n", inet_ntoa(client_addr.sin_addr), buffer);
            continue;
        }
        size_t prefix_len = sep - buffer;
        char prefix[512];
        if (prefix_len >= sizeof(prefix)) prefix_len = sizeof(prefix)-1;
        strncpy(prefix, buffer, prefix_len);
        prefix[prefix_len] = '\0';
        char *rest = sep + 1;

        if (strcmp(prefix, "quem_esta_ai") == 0) {
            if (strcmp(rest, EXPECTED_TOKEN) == 0) {
                char reply[] = "eu_sou_o_destino";
                sendto(sockfd, reply, (int)strlen(reply), 0, (struct sockaddr*)&client_addr, addr_len);
                printf("[UDP] Discovery autorizado para %s. Respondi.\n", inet_ntoa(client_addr.sin_addr));
            } else {
                printf("[UDP] Discovery com token inválido de %s\n", inet_ntoa(client_addr.sin_addr));
            }
        } else {
            // possiveis mensagens diretas no formato "TOKEN:mensagem"
            if (strcmp(prefix, EXPECTED_TOKEN) == 0) {
                printf("[UDP] Mensagem autorizada de %s: %s\n", inet_ntoa(client_addr.sin_addr), rest);
                // opcional: responder ack
                char ack[] = "ack";
                sendto(sockfd, ack, (int)strlen(ack), 0, (struct sockaddr*)&client_addr, addr_len);
            } else {
                printf("[UDP] Mensagem com token inválido de %s. Ignorando.\n", inet_ntoa(client_addr.sin_addr));
            }
        }
    }

    closesocket(sockfd);
    return 0;
}

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup falhou\n");
        return 1;
    }

    // criar threads UDP e TCP
    HANDLE hUdp = CreateThread(NULL, 0, udp_thread, NULL, 0, NULL);
    HANDLE hTcp = CreateThread(NULL, 0, tcp_thread, NULL, 0, NULL);

    if (!hUdp || !hTcp) {
        printf("Erro ao criar threads\n");
        WSACleanup();
        return 1;
    }

    printf("Servidor combinado rodando. UDP=%d TCP=%d\n", PORT_UDP, PORT_TCP);
    // manter o processo vivo aguardando threads (infinito)
    WaitForSingleObject(hUdp, INFINITE);
    WaitForSingleObject(hTcp, INFINITE);

    WSACleanup();
    return 0;
}
