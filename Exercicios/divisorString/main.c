#include <stdio.h>
#include <string.h>

// Função para calcular o MDC (máximo divisor comum)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// Função principal que retorna o GCD das strings
char* gcdOfStrings(char* str1, char* str2) {
    static char result[100]; // Resultado final

    // Verifica se str1 + str2 == str2 + str1
    char temp1[200], temp2[200];
    strcpy(temp1, str1);
    strcat(temp1, str2);
    strcpy(temp2, str2);
    strcat(temp2, str1);

    if (strcmp(temp1, temp2) != 0) {
        return "";
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int gcdLen = gcd(len1, len2);

    strncpy(result, str1, gcdLen);
    result[gcdLen] = '\0';

    return result;
}

int main() {
    char str1[] = "ABCDEFG";
    char str2[] = "ABC";

    printf("Saida: \"%s\"\n", gcdOfStrings(str1, str2));

    return 0;
}


