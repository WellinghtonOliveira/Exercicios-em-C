#include <stdio.h>

double findMaxAverage(int *nums, int numsSize, int k) {
    double soma = 0;
    for (int i = 0; i < k; i++) {
        soma += nums[i];
    }

    double maxSoma = soma;

    for (int i = k; i < numsSize; i++) {
        soma += nums[i] - nums[i - k];  // desliza a janela
        if (soma > maxSoma) {
            maxSoma = soma;
        }
    }

    return maxSoma / k;
}

int main() {
    int nums[6] = {1, 12, -5, -6, 50, 3};
    int k = 4;

    double resultado = findMaxAverage(nums, 6, k);
    printf("%.5f\n", resultado);

    return 0;
}
