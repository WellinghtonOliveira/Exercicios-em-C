#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n)
{
    int c = 0;
    for (int i = 0; i < flowerbedSize; i++)
    {
        if (flowerbed[i] == 0 &&
            (i == 0 || flowerbed[i - 1] == 0) &&
            (i == flowerbedSize - 1 || flowerbed[i + 1] == 0))
        {
            c++;
            flowerbed[i] = 1;
        }
    }
    return c >= n;
}

int main()
{
    int flowerbed[5] = {0, 0, 0, 0, 1};
    int flowerbedSize = sizeof(flowerbed) / sizeof(flowerbed[0]);
    int n = 1;

    bool value = canPlaceFlowers(flowerbed, flowerbedSize, n);

    printf("%s\n", value ? "true" : "false");

    return 0;
}
