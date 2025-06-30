#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool *canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    bool *flowerValue = malloc(flowerbedSize * sizeof(bool));
    
    int i, j = 0, k = 0, cont = 0;

    for (i = 0; i < flowerbedSize; i++)
    {
        if (flowerbed[i] == )
        {
            /* code */
        }
        
        j = flowerbed[i];
        if (flowerbed[i] == j)
        {
            cont++;
        }
        
    }


    printf("cont ==> %d k ==> %d \n", cont, k);
    return flowerValue;
}

int main() {

    int flowerbed[5] = {1,1,0,0,1};
    int flowerbedSize = sizeof(flowerbed) / sizeof(flowerbed[0]);
    int n = 1;

    bool *value = canPlaceFlowers(flowerbed, flowerbedSize, n);

    printf("%s", value[0] ? "true" : "false");
    free(value);

    return 0;
}