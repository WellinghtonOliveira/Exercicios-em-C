// client_auto_send.c
// Compilar: gcc client_auto_send.c -o client_auto_send.exe -lws2_32
// Uso: client_auto_send.exe caminho_do_arquivo.txt

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

#define MY_TOKEN "256dc29b97c147d8769a61df36bfc67f52ed4fba4e4523bef7730df01c10c8a1828ea877826e889112bf6a14da88555bc552ec60e510ff3233b2f54774e41445"

// enviar tudo
int send_all(SOCKET s, const char *buf, int len) {
    int total = 0;
    while (total < len) {
        int snt = send(s, buf + total, len - total, 0);
        if (snt == SOCKET_ERROR) return SOCKET_ERROR;
        total += snt;
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s arquivo.txt\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        printf("Erro ao abrir %s\n", file_path);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup falhou\n");
        fclose(fp);
        return 1;
    }

    SOCKET udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock == INVALID_SOCKET) {
        printf("Erro criar UDP: %d\n", WSAGetLastError());
        fclose(fp);
        WSACleanup();
        return 1;
    }

    BOOL broadcastEnable = TRUE;
    setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcastEnable, sizeof(broadcastEnable));

    struct sockaddr_in baddr;
    memset(&baddr, 0, sizeof(baddr));
    baddr.sin_family = AF_INET;
    baddr.sin_port = htons(PORT_UDP);
    baddr.sin_addr.s_addr = inet_addr("255.255.255.255");

    // timeout para recv
    int timeout_ms = 3000;
    setsockopt(udp_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout_ms, sizeof(timeout_ms));

    char recvbuf[BUFFER_SIZE];
    struct sockaddr_in srv_addr_udp;
    int srv_addr_len = sizeof(srv_addr_udp);
    int found = 0;

    printf("Iniciando descoberta do servidor (broadcast com token)...\n");
    while (!found) {
        char disc[1024];
        snprintf(disc, sizeof(disc), "quem_esta_ai:%s", MY_TOKEN);
        sendto(udp_sock, disc, (int)strlen(disc), 0, (struct sockaddr*)&baddr, sizeof(baddr));
        printf("Broadcast enviado. Aguardando resposta...\n");

        int n = recvfrom(udp_sock, recvbuf, BUFFER_SIZE - 1, 0, (struct sockaddr*)&srv_addr_udp, &srv_addr_len);
        if (n == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAETIMEDOUT) {
                printf("Sem resposta (timeout). Tentando de novo em 2s...\n");
                Sleep(2000);
                continue;
            } else {
                printf("Erro recvfrom: %d\n", err);
                Sleep(2000);
                continue;
            }
        }
        recvbuf[n] = '\0';
        if (strcmp(recvbuf, "eu_sou_o_destino") == 0) {
            printf("Servidor autenticado encontrado: %s\n", inet_ntoa(srv_addr_udp.sin_addr));
            found = 1;
            break;
        } else {
            printf("Resposta inesperada: %s\n", recvbuf);
            Sleep(2000);
        }
    }

    // agora conectar por TCP e enviar o arquivo
    while (1) {
        printf("Tentando conectar TCP em %s:%d ...\n", inet_ntoa(srv_addr_udp.sin_addr), PORT_TCP);
        SOCKET tcp = socket(AF_INET, SOCK_STREAM, 0);
        if (tcp == INVALID_SOCKET) {
            printf("Erro criar TCP: %d\n", WSAGetLastError());
            break;
        }
        struct sockaddr_in tcpaddr;
        memset(&tcpaddr, 0, sizeof(tcpaddr));
        tcpaddr.sin_family = AF_INET;
        tcpaddr.sin_port = htons(PORT_TCP);
        tcpaddr.sin_addr.s_addr = srv_addr_udp.sin_addr.s_addr; // ip encontrado

        if (connect(tcp, (struct sockaddr*)&tcpaddr, sizeof(tcpaddr)) == SOCKET_ERROR) {
            printf("Connect falhou: %d. Vou tentar descoberta de novo.\n", WSAGetLastError());
            closesocket(tcp);
            // volta a descoberta (em caso de server reiniciado com novo ip)
            found = 0;
            // continuar o loop de descoberta:
            Sleep(2000);
            break;
        }

        // montar header TOKEN:filename:size\n
        const char *slash = strrchr(file_path, '\\');
        const char *fname = slash ? slash + 1 : file_path;
        char header[1024];
        snprintf(header, sizeof(header), "%s:%s:%lld\n", MY_TOKEN, fname, filesize);

        if (send_all(tcp, header, (int)strlen(header)) == SOCKET_ERROR) {
            printf("Erro enviar header: %d\n", WSAGetLastError());
            closesocket(tcp);
            break;
        }

        printf("Enviando arquivo %s (%lld bytes)...\n", fname, filesize);
        // reabrir arquivo do início (caso loop)
        fseek(fp, 0, SEEK_SET);
        char buf[BUFFER_SIZE];
        long long remaining = filesize;
        int error = 0;
        while (remaining > 0) {
            int toread = (remaining > BUFFER_SIZE) ? BUFFER_SIZE : (int)remaining;
            int r = (int)fread(buf, 1, toread, fp);
            if (r <= 0) { error = 1; break; }
            if (send_all(tcp, buf, r) == SOCKET_ERROR) {
                printf("Erro no send: %d\n", WSAGetLastError());
                error = 1; break;
            }
            remaining -= r;
        }

        if (!error && remaining == 0) {
            printf("Envio completo. Aguardando ACK...\n");
            int r = recv(tcp, recvbuf, sizeof(recvbuf)-1, 0);
            if (r > 0) {
                recvbuf[r] = '\0';
                printf("Servidor respondeu: %s\n", recvbuf);
            } else {
                printf("Nenhum ACK (recv=%d err=%d)\n", r, WSAGetLastError());
            }
            closesocket(tcp);
            break; // sucesso, sair
        } else {
            printf("Erro durante envio. Fechando socket.\n");
            closesocket(tcp);
            // opcional: tentar descoberta novamente
            found = 0;
            Sleep(2000);
            break;
        }
    }

    fclose(fp);
    closesocket(udp_sock);
    WSACleanup();
    return 0;
}
