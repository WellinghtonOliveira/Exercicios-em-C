#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

bool *kidsWithCandies(int *candies, int candiesSize, int extraCandies, int *returnSize)
{

    char values[candiesSize];

    int i = 0, k;

    while (i < candiesSize)
    {
        int soma = candies[i] + extraCandies;

        for (int j = 0; j < candiesSize; j++)
        {
            if (soma > candies[j])
            {
                values[j] = 't';
            }else
            {
                values[j] = 'f';
            }
        }

        for (k = 0; k < candiesSize; k++) 
        {
            if (values[k] == 't')
            {
            }
        }

        i++;
    }

    printf("\n\n%s", values);
}

int main()
{

    int candies[5] = {2,3,5,1,3};
    int extraCandie = 3;
    int candieSize = sizeof(candies) / sizeof(candies[0]);

    kidsWithCandies(candies, candieSize, extraCandie, 0);

    return 0;
}