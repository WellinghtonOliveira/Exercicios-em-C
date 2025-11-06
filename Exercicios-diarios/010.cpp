#include <stdio.h>


int main() {
	
	float a;
	int b;
	
	printf("\n------- Desconto de produto ------------");
	
	printf("\n | Valor do produto: ");
	scanf("%f", &a);
	
	printf("\n | Selecione a forma de pagamento \n\n  || [1] - A vista \n  || [2] - Parcelado em 2x \n  || [3] Parcelado em 3x \n\n | Opcao ==> ");
	scanf("%d", &b);
	
	switch (b) {
		case 1:
			printf("\n | A vista com 10 porcento de desconto, fica: $%.2f", a - (a * 0.1));
			break;
			
		case 2: 
			printf("\n | Parcelado em 2x, fica: $%.2f", a);
			break;
			
		case 3:
			printf("\n | Parcelado em 3x, fica $%.2f", a + (a * 0.05));
			break;
		
		default:
			printf("\n | Ate mais");
	}
	
    return 0;
}




/*

Peça o valor de um produto.

Peça a forma de pagamento (1 = à vista, 2 = parcelado em 2x, 3 = parcelado em 3x).

Calcule o preço final conforme a escolha:

1: desconto de 10%

2: preço normal

3: acréscimo de 5%

Mostre o valor final na tela.

*/