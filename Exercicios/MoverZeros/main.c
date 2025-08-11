#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    int arrayTemp[numsSize];
    int i, count = 0;

    for (i = 0; i < numsSize; i++) 
    {
        if (nums[i] == 0)
        {
            arrayTemp[count++] = nums[i];
        }
        printf("%d - ", arrayTemp[i]);
    }
}

int main() {
    int nums[5] = { 0, 1, 2, 0, 0 };
    
    moveZeroes(nums, 5);
    return 0;
}