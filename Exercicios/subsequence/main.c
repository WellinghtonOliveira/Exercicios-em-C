#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isSubsequence(char *s, char *t)
{
    int tam_s = strlen(s);
    int tam_t = strlen(t);
    int i, k = 0, j = 0;

    char tempCopy[tam_s];

    for (i = 0; i < tam_t; i++)
    {
        if (s[j] == t[i]) {
            tempCopy[j] = s[j];
            j++;
        }
    }

    for (i = 0; i < tam_s; i++)
    {
        printf("%c", tempCopy[i]);
        if (tempCopy[i] == s[i])
        {
            k++;
        }
    }
    
    return k == tam_s ? printf("\n\n%s", "verdadeiro") : printf("\n\n%s", "falso"); 
}

int main()
{

    char s[] = "axc", p[] = "ahbgdc";

    isSubsequence(s, p);

    return 0;
}