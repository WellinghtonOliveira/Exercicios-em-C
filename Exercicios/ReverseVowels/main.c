#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *reverseVowels(char *s)
{
    int cont = 0, tam = strlen(s);

    char lower[tam];

    for (int i = 0; i < tam; i++)
    {

        switch (lower[i])
        {
        case 'a':
            break;
        case 'e':
            break;
        case 'i':
            break;
        case 'o':
            break;
        case 'u':
            break;
        default:
            lower[i] = tolower(s[i]);
            i--;
            cont = i;
            break;
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