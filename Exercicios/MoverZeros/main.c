#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    printf("%d", nums);
    printf("\n%d", numsSize);
}

int main() {
    int nums[5] = { 0, 1, 2, 0, 3 };
    
    moveZeroes(nums, 5);
    return 0;
}