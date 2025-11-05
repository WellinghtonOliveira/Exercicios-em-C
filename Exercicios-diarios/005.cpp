#include <stdio.h>


int main() {
	
	int a;
	
	printf("\n-------- Numero par ou impar--------------");
	
	printf("\n | Digite o numero: ");
	scanf("%d", &a);
	
	if (a % 2 == 0) {
		printf("O numero %d, e um numero par.", a);
	}else {
		printf("O numero %d, e um numero impar.", a);
	}
	
	return 0; 
}


//
//Peça um número inteiro ao usuário.
//
//Verifique se ele é par ou ímpar.
//
//Mostre o resultado na tela.