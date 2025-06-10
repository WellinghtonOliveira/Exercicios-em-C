#include <stdio.h>

int main() {
	
	FILE *ftpr;
	
	ftpr = fopen("arquivoTeste.txt", "a");
	
	//Escrevendo em um arquivo
	fprintf(ftpr, "\nEscrevendo em baixo do texto existente");
	
	fclose(ftpr);
	
	return 0;
}