#include <stdio.h>

//float maior(float a, float b);

int main() {
	
	float a, b;
	
	printf("----------- Mair numero ----------");
	
	printf("\n | Digite um numero: ");
	scanf("%f", &a);
	
	printf("\n | Digite outro numero: ");
	scanf("%f", &b);
	
	if (a == b) {
		printf("\n | Os dois numeros sao iguais.");
		return 0;
	}
	
	printf("\n | O maior numero digitado foi ==> %.2f", a > b ? a : b);
	
	return 0;
}

//float maior(float a, float b) {
//	return a > b ? a : b;
//}




/*

Peça dois números inteiros ao usuário.

Compare esses números.

Mostre qual é o maior deles.

Se forem iguais, mostre uma mensagem dizendo que são iguais.

*/