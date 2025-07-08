#include <stdio.h>
#include <string.h>

char *reverseVowels(char *s)
{
    int tam = strlen(s);

    for (int i = 0; i < tam; i++) 
    {
        switch (s[i])
        {
        case 'a' || 'A':
            printf("%d\n\n", i);
            break;
        case 'e':
            printf("%d\n\n", i);
            break;
        case 'i':
            printf("%d\n\n", i);
            break;
        case 'o':
            printf("%d\n\n", i);
            break;
        case 'u':
            printf("%d\n\n", i);
            break;
        default:
            printf("Nada encontrado");
            break;
        }
    }
}

int main()
{

    char str[] = "aeiouA";

    reverseVowels(str);

    return 0;
}

/*

1 - coletar a string 's'
2 - identificar a posição das primeiras vogais
3 - inverter a ordem das vogais
4 - adicionar as vagais invertidas nas posições corretas

*/