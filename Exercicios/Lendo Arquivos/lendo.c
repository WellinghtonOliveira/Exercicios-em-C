#include <stdio.h>

int main() {
	
	// Escreve no arquivo
	FILE *text;
	text = fopen("escrevendoLendo.txt", "a");
	fprintf(text, "\nMineca dicatibiriba");
	fclose(text);
	
	// le o arquivo
	text = fopen("escrevendoLendo.txt", "r");
	char meuTexto[100];
	while (fgets(meuTexto, 100, text)) {
		printf("%s", meuTexto);
	}
	fclose(text);
	
	return 0;
}