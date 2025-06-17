#include <stdio.h>

int main() {
	
	char vetor[3][10] = { "cafe", "arroz", "feijao" };
	
	for (int i = 0; i < 3; i++) {
		printf("%s\n", vetor[i]);
	}
	
	return 0;
}