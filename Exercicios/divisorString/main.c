#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char strF[100];
char* gcdOfStrings(char* str1, char* str2) {
    strF[0] = '\0';
    int tam1 = strlen(str1);
    int tam2 = strlen(str2);
    int i, k, cont = 0;

    k = tam1 > tam2 ? tam1 : tam2;

    for (i = 0; i < k; i++) {
        if (str1[i] == str2[i]) {
            strF[i] = str2[i];
        } else {
            if (strlen(strF) == 0) {
                strcpy(strF, "");
            }
            cont++;
        }
    }

    cont = cont / strlen(strF);
    printf("%d\n\n", cont);

    strF[i] = '\0';
    return strF;
}

int main() {

    char str1[] = "abcdef";
    char str2[] = "abc";

    printf("%s\n", gcdOfStrings(str1, str2));

    return 0;
}