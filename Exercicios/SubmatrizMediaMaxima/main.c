#include <stdio.h>
#include <stdlib.h>

double findMaxAverage(int *nums, int numsSize, int k)
{
    int tam = numsSize - 1;
    int i, a = 1, c = 1, j = 0;
    int *numeros = NULL;
    int quantia = 0;

    float q = 0;

    for (i = 0; i < tam + 1; i++)
    {
        q += nums[j];
        
        printf("%.2f  ", q);

        if (c == k)
        {
            float media = q / k;

            quantia++;
            numeros = realloc(numeros, quantia * sizeof(int));

            // numeros[quantia - 1] = algum valor
            q = 0;
            c = 1;
            j = a;
            a++;
        }

        c++;
        j++;
    }

    free(numeros);
    return 0;
}

int main()
{
    int nums[6] = {1, 12, -5, -6, 50, 3}, k = 4;

    findMaxAverage(nums, 6, k);

    return 0;
}