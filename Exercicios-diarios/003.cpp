#include <stdio.h>

int main() {
	
	float a, b;
	
	printf("------- Media de numeros decimais --------------");
	printf("\n | Digite um numero: ");
	scanf("%f", &a);
	
	printf("\n | Digite outro numero: ");
	scanf("%f", &b);
	
	printf("\n | A media dos numeros sao ==> %.2f", (a + b) / 2);
	
	return 0;
}


/*
Peça ao usuário dois números decimais (pode ter vírgula, tipo 7.5).

Calcule a média deles.

Mostre o resultado na tela com uma mensagem clara.
*/