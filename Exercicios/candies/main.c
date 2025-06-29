#include <stdio.h>
#include <stdbool.h>

bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {

    char values[candiesSize];
    
    int i = 0;

    while (i < candiesSize)
    {
        int soma = candies[i] + extraCandies;

        

        if (soma > candies[i])
        {
            printf(" %d\n", i);
        }
        

        i++;
    }
    
}

int main() {

    int candies[5] = { 2, 10, 3, 1, 4 };
    int extraCandie = 3;
    int candieSize = sizeof(candies) / sizeof(candies[0]);

    kidsWithCandies(candies, candieSize, extraCandie, 0 );

    return 0;
}