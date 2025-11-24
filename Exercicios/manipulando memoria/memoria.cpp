#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {
    const size_t MB = 1024 * 1024;
    const size_t BLOCO = 100 * MB; // aloca MB por loop

    while (1) {
        void* p = malloc(BLOCO);
        if (!p) {
            printf("Falha ao alocar memória.\n");
            break;
        }

        // Toca cada byte → força o Windows a realmente usar RAM
        memset(p, 0, BLOCO);

        printf("Alocado +%zu MB\n", BLOCO / MB);

        Sleep(30); // dá tempo de ver no gerenciador de tarefas
    }

    return 0;
}


/*

Sobrecarregar as momorias rams para que fiquem em uso de 100%

*/