#include <stdio.h>

int main() {
	
	int n;
	
	printf("Digite um numero correspondente ao tamanho do desenho ");
	scanf("%d", &n);
	
	if (n < 0 || n == NULL) return 0;
	
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