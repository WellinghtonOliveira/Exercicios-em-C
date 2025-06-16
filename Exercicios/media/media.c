#include <stdio.h>
#include <stdlib.h>

char gradeFuncao(double str) {
	if (str >= 90) return 'A';
	else if (str >= 80) return 'B';
	else if (str >= 70) return 'C';
	else if (str >= 60) return 'D';
	else return 'F';
}

int main() {
	
	char continuar;
	int cont = 0;

	do {
		int materia;
		double sum = 0, nota, media;
		
		printf("\nDigite a quantia de materias: ");
		scanf("%d", &materia);
	
		for (int i = 0; i < materia; i++) {
			printf("\nNota - Materia %d => ", i + 1);
			scanf("%lf", &nota);
			sum += nota;
		}
		
		// system("cls"); usado para limpar o console
	
		media = sum / materia;
		printf("\nSua media e => %.2lf", media);
		printf("\nVoce tirou um => %c", gradeFuncao(media));
		
		printf("\nVoce deseja refazer o calculo, [S|N] => ");
		scanf(" %c", &continuar);
		
		char loading[30] = { ".", "..", "..." };
		if (continuar == 's' || continuar == 'S') {
			printf("---------------------------");
			printf("\n[%d] - Repetindo...", cont);
			cont += 1;
		}else if (continuar == 'n' || continuar == 'N') {
			system("cls");
			for (int i = 0; i < 3; i++) {
				printf("\nFinalizando%c", loading[0][i] );
			}
		}else {
			printf("\nLetra invalida.");
			return 1;
		}
	
	} while (continuar == 'S' || continuar == 's');
	
	return 0;
}