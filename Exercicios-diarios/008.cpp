#include <stdio.h>

int main() {
	
	int a, b, c, maior;
	
	printf("\n--------- Maior numero inteiro ---------");
	
	printf("\n | Digite o primeiro numero: ");
	scanf("%d", &a);
	
	printf("\n | Digite o segundo numero: ");
	scanf("%d", &b);
	
	printf("\n | Digite o terceiro numero: ");
	scanf("%d", &c);
	
	if (a > maior) {
		maior = a;
	}
	if (b > a) {
		maior = b;
	}
	if (c > b) {
		maior = c;
	}
	
	printf("\n | O maio numero e: %d", maior);
	
	return 0;
}




/*

Peça três números inteiros ao usuário.

Descubra qual é o maior deles.

Mostre o resultado na tela

*/