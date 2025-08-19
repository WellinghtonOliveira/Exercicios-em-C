#include <stdio.h> 

void sum(int a, int b) {
	int calc = a + b;
	printf("Numero somado foi %d + %d => %d\n", a, b, calc);
}

int main() {
	sum(2, 11);
	sum(4, 1);
	sum(6, 2);
	sum(3, 1);
	sum(33, 6);
	sum(22, 33);
	sum(1, 5);
	sum(4, 7);
	sum(7, 8);	
	return 0;
}