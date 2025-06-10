#include <stdio.h>

int main() {
	
	FILE *ftpr;
	
	ftpr = fopen("arquivoTeste.txt", "w");
	
	//Escrevendo em um arquivo
	fprintf(ftpr, "escrevendo em um arquivo de texto");
	
	fclose(ftpr);
	
	return 0;
}