#include <stdio.h>

int main() {
	FILE *text;
	
	text = fopen("escrevendoLendo.txt", "w");
	fprintf(text, "Escrito em 'C'");
	fclose(text);
	
	return 0;
}