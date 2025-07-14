#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char *reverseVowels(char *s)
{
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        // Avança até encontrar uma vogal
        while (left < right && !is_vowel(s[left])) left++;
        // Regride até encontrar uma vogal
        while (left < right && !is_vowel(s[right])) right--;

        // Troca as vogais
        if (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
}

int main()
{

    char str[] = "AaeiouA";

    reverseVowels(str);

    return 0;
}

/*

1 - coletar a string 's'
2 - identificar a posição das primeiras vogais
3 - inverter a ordem das vogais
4 - adicionar as vagais invertidas nas posições corretas

*/