#include <stdio.h>

int main() {
	FILE *text;
	
	text = fopen("escrevendo-e-lendo.txt", "w");
	fprintf("escrevendo-e-lendo.txt", "Escrito em 'C'");
	fclose(text);
	
	return 0;
}