#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <math.h>

unsigned __stdcall stress_thread(void* arg) {
    volatile double x = 0;

    while (1) {
        // Cálculos pesados
        for (int i = 0; i < 1000000; i++) {
            x += sin(i) * cos(i) * tan(1.2345);
            x = sqrt(fabs(x)) * 1.000001;
        }
    } 

    return 0;
}

int main() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    int cpuCount = sysInfo.dwNumberOfProcessors;
    printf("Iniciando %d threads de stress...\n", cpuCount);

    for (int i = 0; i < cpuCount; i++) { 
        _beginthreadex(NULL, 0, stress_thread, NULL, 0, NULL);
    }

    Sleep(INFINITE);
    return 0;
}





/*

Manipulação da CPU forçando ela ao maximo

*/