#include <stdio.h>

void moveZeroes(int *nums, int numsSize)
{
    printf("\n\n");

    int temp[numsSize];
    int i, j = 0;

    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] == 0)
        {
            temp[j++] = nums[i];
            printf("%d  ", temp[j - 1]);
        }
    }

    while (j < numsSize)
    {
        temp[j++] = 1;
    }
    
    for (i = 0; i < numsSize; i++) 
    {
        printf("%d  ", temp[i - 1]);
    }

    printf("\n\n");
}

int main()
{
    int nums[5] = {0, 1, 2, 0, 0};

    moveZeroes(nums, 5);
    return 0;
}