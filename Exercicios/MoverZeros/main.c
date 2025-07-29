#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] == 0) 
        {
            printf("\naqui\n");
        }
        
        printf("%d", nums[i]);
    }
    

    printf("\n%d", numsSize);
}

int main() {
    int nums[5] = { 0, 1, 2, 0, 3 };
    
    moveZeroes(nums, 5);
    return 0;
}