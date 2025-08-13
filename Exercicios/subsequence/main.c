#include <stdio.h>
#include <stdbool.h>

bool isSubsequence(char *s, char *t)
{
    for (int i = 0; i < (sizeof(s) / sizeof(s[0])); i++)
    {
        printf("%c", s[i]);
    }

    printf("%d", sizeof(s) / sizeof(s[0]));
}

int main()
{

    char s[] = "abc", p[] = "aqbtc";

    isSubsequence(s, p);

    return 0;
}