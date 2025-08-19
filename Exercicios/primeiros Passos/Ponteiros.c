#include <stdio.h>

int point() {
	return 100;
}

int main() {
	
	int myNum = point();
	int* ptr = &myNum;
	
	
	printf("O enderesso do meu numero %d e ==> %p", myNum, ptr);

	return 0;
}