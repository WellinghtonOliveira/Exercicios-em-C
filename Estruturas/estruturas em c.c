#include <stdio.h>

struct myStruct {
	int num;
	char letter;
};

int main() {
	
	struct myStruct s1;
	
	s1.num = 15 + 2;
	s1.letter = 'G';
	
	printf("O numero: %d\n", s1.num);
	printf("A letra: %c\n", s1.letter);
	
	return 0;
}