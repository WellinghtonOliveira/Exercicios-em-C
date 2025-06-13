#include <stdio.h>

char gradeFuncao(double avg) {
	if (avg >= 90) return 'A';
	else if (avg >= 80) return 'B';
	else if (avg >= 70) return 'C';
	else if (avg >= 60) return 'D';
	else return 'F';
}

int main() {
	
	int nota;
	
	printf("Digite sua nota para calcularmaos: ");
	scanf("%d", &nota);
	
	do {
		if (nota < 1 || nota > 5) {
			printf("\nNota invalida digite um numero entre 1 a 5");
			scanf("Digite a nota valida: %d", &nota);
		}
	}while (nota > 1 || nota < 5);
	
	printf("\nSua nota media e ==> %d", nota);
	
	return 0;
}