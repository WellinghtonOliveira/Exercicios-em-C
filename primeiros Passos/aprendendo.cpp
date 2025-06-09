#include <stdio.h>

int main() {
	
	// Atribuindo valor a variavel apos a criação dela
	int atribuindoValorAVariavelDepois;
	
	atribuindoValorAVariavelDepois = 1500;
	printf("\n\nValor recebido foi: -> %d\n\n", atribuindoValorAVariavelDepois);
	
	// Printando as variaveis
	int a = 15;
	float b = 10.5;
	char c = 'Z';
	
	a = 1;
	b = 2.1;
	c = 'P';
	
	printf("Ola mundo!\n\n");
	printf("Minha variavel inteira e: %d\n", a);
	printf("Minha variavel float e: %f\n", b);
	printf("Meu caracter e: %c\n\n", c);
	
	printf("Colocando todas as variaveis em uma linha: inteiro -> %d, float -> %f, caractere -> %c\n\n", a, b, c);
	
	// Somando Valores
	int ab, bc;
	
	ab = 5;
	bc = 5;
	
	int sum = ab + bc;
	
	printf("\n\n%d", sum);
	
	return 0;
}

// declarando multiplas variaveis:  ->  int a = 10, b = 1, c = 3;

// %d Para números inteiros
// %f Para números quebrados
// %c Para caracteres'