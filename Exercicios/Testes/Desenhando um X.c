#include <stdio.h>

int main() {
	
	int n;
	
	printf("Digite um numero impar maior ou igual a 3: ");
	scanf("%d", &n);
	
	if (n < 3 || n % 2 == 0) {
		printf("Digite um numero impar maior ou igual a 3 ");
		return 0;
	}
	
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
				
			if 	(x == y || y == n - x - 1) {
				printf("# ");
			}else {
				printf("  ");
			}
		}
		printf("\n");
	}
	
	return 0;
}