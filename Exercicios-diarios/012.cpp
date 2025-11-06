#include <stdio.h>

int main() {
	
	int a, b = 0;
	
	printf("\n-------------- Soma dos numeros em recursao --------------");
	
	printf("\n\n | Digite um numero inteiro positivo maior que zero: ");
	scanf("%d", &a);
	
	if (a <= 0) return 0;
	
	for (int i = 1; i <= a; i++) {
		b += i;
	}
	
	printf("\n | Resultado: %d", b);
	
	return 0;
}


/*

Peça um número inteiro positivo N.

Some todos os números de 1 até N.

Mostre o resultado final.

*/