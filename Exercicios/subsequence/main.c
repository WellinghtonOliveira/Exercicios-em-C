#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isSubsequence(char *s, char *t)
{
    int tam_s = strlen(s);
    int tam_t = strlen(t);
    int i, k = 0, j = 0;

    if (tam_s == 0) return true;
    char tempCopy[tam_s];

    for (i = 0; i < tam_t; i++)
    {
        if (s[j] == t[i])
        {
            tempCopy[j] = s[j];
            j++;
        }
    }

    for (i = 0; i < tam_s; i++)
    {
        if (tempCopy[i] == s[i])
        {
            k++;
        }
    }

    return k == tam_s ? printf("%s", "true") : printf("%s", "false");
}

int main()
{

    char s[] = "", p[] = "ahbgdc";

    isSubsequence(s, p);

    return 0;
}