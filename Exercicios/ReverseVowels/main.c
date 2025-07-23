#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para verificar se o caractere é uma vogal
int is_vowel(char c) {
    c = tolower(c); // Normaliza para minúsculo
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Função para inverter as vogais da string
char *reverseVowels(char *s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        // Avança até encontrar uma vogal do lado esquerdo
        while (left < right && !is_vowel(s[left])) left++;
        // Regride até encontrar uma vogal do lado direito
        while (left < right && !is_vowel(s[right])) right--;

        // Troca as vogais encontradas
        if (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
    return s; // Retorna a string modificada
}

int main() {
    char str[] = "IceCreAm";
    printf("%s\n", reverseVowels(str)); // Saída esperada: "AceCreIm"

    char str2[] = "leetcode";
    printf("%s\n", reverseVowels(str2)); // Saída esperada: "leotcede"

    return 0;
}