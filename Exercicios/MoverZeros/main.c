#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    int j = 0, array[numsSize];

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] == 0) 
        {
            array[j++] = nums[i];
        }else
        {
            array[i] = nums[i];
        }
        
        printf("\n%d", array[i]);
    }    

}

int main() {
    int nums[5] = { 0, 1, 2, 0, 0 };
    
    moveZeroes(nums, 5);
    return 0;
}