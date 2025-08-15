#include <stdio.h>

double findMaxAverage(int *nums, int numsSize, int k)
{

    int i, j = 0;

    for (i = 0; i < numsSize; i++)
    {
        if (i == k)
        {
            if (numsSize == j)
            {
                printf("%d  ", nums[j]);
                break;
            }

            i = 0;
        }

        j++;
    }
}

int main()
{
    int nums[6] = {1, 12, -5, -6, 50, 3}, k = 4;

    findMaxAverage(nums, 6, k);

    return 0;
}