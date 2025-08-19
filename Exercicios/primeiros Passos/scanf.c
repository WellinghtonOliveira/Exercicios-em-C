#include <stdio.h>

int main() {
	
	int myInt;
	char myChar;
	char myString[20];
	
	printf("Digite um numero de 1 a 10, uma letra e uma palavra: ");
	scanf("%d %c %s", &myInt, &myChar, myString);

	printf("\n\nO numero escolhido ==> %d ", myInt);
	printf("\n\nA letra escolhida foi ==> %c", myChar);
	printf("\n\nA palavra digitsda foi ==> %s", myString);
	
	printf("\n\nVariavel inteira armazenada em ==> %p", &myInt);
	
	return 0;
}