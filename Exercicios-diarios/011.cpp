#include <stdio.h>
#include <windows.h>

int main() {
	
	int a;
	
	printf("\n---------- Contagem de numeros -----------");
	
	printf("\n | Digite um numero inteiro positivo, maior que zero: ");
	scanf("%d", &a);
	
	if (a <= 0) return 0;
	
	system("cls");
	
	for (int i = 1; i <= a; i++) {
		printf(" %d", i);
	}

	return 0;

}


/*

Peça ao usuário um número inteiro positivo.

Mostre na tela todos os números de 1 até esse número.

*/