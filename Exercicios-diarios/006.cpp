#include <stdio.h>

int main() {

	float a, b, res;
	int op;

	printf("\n--------- calculadora simples ------------");
	
	printf("\n | Digite seu numero: ");
	scanf("%f", &a);
	
	printf("\n | Digite outro numero: ");
	scanf("%f", &b);	
	
	printf("\n | Qual operacao voce deseja fazer?");
	printf("\n  |");
	printf("\n   | [1] Adicao");
	printf("\n   | [2] Divisao");
	printf("\n   | [3] Subtracao");
	printf("\n   | [4] Multiplicacao");
	printf("\n  |");
	
	printf("\n | Digite o numero da opcao escolhida ==> ");
	scanf("%d", &op);
	
	switch (op) {
		case 1:
			res = a + b;
			break;
			
		case 2:
			res = a / b;
			break;
		
		case 3:
			res = a - b;
			break;
		
		case 4:
			res = a * b;
			break;
		
		default:
			printf("|\n|\n ||  Opcao Operacional Invalida -- \n\n");
			return 0;
	}
	
	printf("\n | Resultado ==> %.2f", res);
	
	return 0;
}



//
//Pedir dois números ao usuário.
//
//Pedir qual operação ele quer fazer (+, -, *, /).
//
//Mostrar o resultado.