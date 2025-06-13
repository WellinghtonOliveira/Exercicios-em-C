#include <stdio.h>

char gradeFuncao(double str) {
	if (str >= 90) return 'A';
	else if (str >= 80) return 'B';
	else if (str >= 70) return 'C';
	else if (str >= 60) return 'D';
	else return 'F';
}

int main() {
	
	char continuar = '0';

	do {
		continuar = '0';
		int materia;
		double sum = 0, nota, media;
		
		printf("\nDigite a quantia de materias: ");
		scanf("%d", &materia);
	
		for (int i = 0; i < materia; i++) {
			printf("\nNota - Materia %d => ", + 1);
			scanf("%lf", &nota);
			sum += nota;
		}
	
		media = sum / materia;
		printf("\n\nSua media e => %.2lf", media);
		printf("\nVoce tirou um => %c", gradeFuncao(media));
		
		printf("\n\nVoce deseja refazer o calculo, [S|N] => ");
		scanf("%c", &continuar);
	
		if (
		continuar != 's'||
		continuar != 'S'||
		continuar != 'n'||
		continuar != 'N'
		) {
			printf("\n\nLetra invalida");
			return 1;
		}
	
	} while (continuar != 'S' || continuar != 's');
	
	return 0;
}