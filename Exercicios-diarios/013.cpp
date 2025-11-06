#include <stdio.h>

int main() {
	
	int a = 1, b = 0;
	
	printf("\n------------- Soma dos numero -------------");
	
	while (a != 0) {

		printf("\n | Digite um numero inteiro para somar ( Digite [0] Para sair): ");
		scanf("%d", &a);

		b += a;
			
		printf("\n | Resultado da soma: %d", b);
	}
	
	return 0;
}



/*

Peça números ao usuário repetidamente.

Some todos os números digitados.

Pare quando o usuário digitar 0.

Mostre a soma total.

*/