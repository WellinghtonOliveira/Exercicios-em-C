#include <stdio.h>

int main() {
	
	int n;
	
	printf("Digite um numero correspondente ao tamanho do desenho ");
	scanf("%d", &n);
	
	if (n < 3) {
		printf("O tamanho deve ser maior ou igual a 3");
		return 0;
	}
	
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			if (a == 0 || a == n - 1 ||
				b == 0 || b == n - 1) {
				printf(" #");
			}else {
				printf("  ");
			}
		}
		printf("\n");
	}
	
	return 0;
}