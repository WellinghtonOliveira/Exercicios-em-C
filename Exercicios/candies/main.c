#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool *kidsWithCandies(int *candies, int candiesSize, int extraCandies, int *returnSize)
{
    bool *arrayValores = malloc(candiesSize * sizeof(bool));
    int totalCandies;
    int i, k, cont;
    for (i = 0; i < candiesSize; i++)
    {
        totalCandies = 0;
        cont = 0;
        totalCandies = candies[i] + extraCandies;
        for (k = 0; k < candiesSize; k++)
        {
            if (totalCandies >= candies[k])
            {
                cont++;
            }
        }
        arrayValores[i] = (cont == candiesSize);
    }
    *returnSize = candiesSize;
    return  arrayValores;
}

int main()
{
    
    int tamanho;
    int candies[3] = {12, 1, 12};
    int extraCandie = 10;
    int candieSize = sizeof(candies) / sizeof(candies[0]);

    bool *resultado = kidsWithCandies(candies, candieSize, extraCandie, &tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        printf("%s\n", resultado[i] ? "true" : "false");
    }

    free(resultado);

    return 0;
}