#include <stdio.h>


int main() {
	
	float a;
	
	printf("\n--------- Verificando notas------------");
	
	printf("\n | Digite sua nota: ");
	scanf("%f", &a);
	
	if (a >= 7) {
		printf("\n || Aprovado ");
	}else if (a < 5) {
		printf("\n || Reprovado ");
	}else {
		printf("\n || Recuperacao");
	}
	
	return 0;
}



/*

Peça ao usuário a nota de um aluno (de 0 a 10).

Se a nota for maior ou igual a 7, mostre: "Aprovado!"

Se for entre 5 e 6.9, mostre: "Recuperação."

Se for menor que 5, mostre: "Reprovado."
*/