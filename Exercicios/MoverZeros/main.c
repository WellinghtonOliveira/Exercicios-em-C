#include <stdio.h>

void moveZeroes(int *nums, int numsSize)
{
    int lastNonZeroFoundAt = 0;

    // Mover todos os elementos diferentes de zero para o início
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != 0)
        {
            nums[lastNonZeroFoundAt++] = nums[i];
        }
    }

    // Preencher o restante com zeros
    for (int i = lastNonZeroFoundAt; i < numsSize; i++)
    {
        nums[i] = 0;
    }

    // Imprimir resultado
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main()
{
    int nums[5] = {0, 1, 0, 3, 12};

    moveZeroes(nums, 5);
    return 0;
}
