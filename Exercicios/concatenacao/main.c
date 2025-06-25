#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char strF[100];
char* divWord(char* str1, char* str2) {
    strcpy(strF, "\0");
    int tam1 = strlen(str1);// Tamnho da string 1
    int tam2 = strlen(str2);// Tamanho da string 2
    int i;

    for (i = 0; i < tam2; i++ ){
        if (strF[0] == str2[i]) break;
        if (str1[i] == str2[i]) {
            strF[i] = str2[i];
        }else {
            if (strlen(strF) == 0) {

                strcpy(strF, "");
            }
        }
    }

    strF[i] = '\0';
    return strF;
}

int main() {

    printf("%s\n", divWord("abcabcabc", "abcabc"));
    printf("%s\n", divWord("ababababa", "ababab"));
    printf("%s\n", divWord("xvidiu", "python"));
    return 0;
}