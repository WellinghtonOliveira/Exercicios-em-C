#include <stdio.h>

int main() {
	
	int myArray[5] = {12, 34, 211, 35, 87};
	
	printf("Aqui esta o ponteiro do meu array ==> %p", &myArray);
	printf("\n\nAqui esta os ponteiros de todos os numeors no meu array ==> ");
	
	for (int i = 0; i < 5; i++) {
		printf("\n%p", &myArray[i]);
	}
	
	printf("\n\nE aqui esta os valores do meu array ==> ");
	
	for (int i = 0; i < 5; i++) {
		printf("\n%d", *(myArray + i));
	}
	
	return 0;
}