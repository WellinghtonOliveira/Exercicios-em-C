#include <windows.h>
#include <stdio.h>

int main() {
    CreateDirectoryA("StressDisk", NULL);

    const int fileSizeMB = 1000; // tamanho de cada arquivo
    const int totalFiles = 30;  // quantidade de arquivos (controle)
    char fileName[256];

    for (int i = 0; i < totalFiles; i++) {
        sprintf(fileName, "StressDisk\\file_%03d.bin", i);

        HANDLE hFile = CreateFileA(
            fileName,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hFile == INVALID_HANDLE_VALUE) {
            printf("Erro ao criar arquivo %s.\n", fileName);
            break;
        }

        printf("Criando: %s (%d MB)\n", fileName, fileSizeMB);

        // Cada escrita é de 1MB
        char buffer[1024 * 1024] = { 0 };
        DWORD written;

        for (int mb = 0; mb < fileSizeMB; mb++) {
            WriteFile(hFile, buffer, sizeof(buffer), &written, NULL);
        }

        CloseHandle(hFile);
    }

    printf("\n Finalizado com seguranca.\n");
    printf("Para remover tudo, basta apagar a pasta 'StressDisk'.\n");

    return 0;
}
