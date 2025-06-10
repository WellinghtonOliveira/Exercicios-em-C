#include <stdio.h>

int main() {
	
	FILE *ftpr;
	
	ftpr = fopen("arquivoTeste.txt", "w");
	
	fclose(ftpr);
	
	return 0;
}