#include <stdio.h>

int main() {
	
	int a;
	
	printf("\n---------- Idade da pessoa ------------");
	
	printf("\n | Digite uma idade: ");
	scanf("%d", &a);
	
	if (a <= 12) {
		printf("\n || Crianca");
	}else if (a <= 17) {
		printf("\n || Adolecente");
	}else if (a <= 59) {
		printf("\n || Adulto");
	}else {
		printf("\n || Idoso");
	}
	
	return 0;
}



/*

Peça a idade de uma pessoa.

Mostre a categoria conforme a idade:

Menor que 12 → "Criança"

De 12 até 17 → "Adolescente"

De 18 até 59 → "Adulto"

60 ou mais → "Idoso"

*/