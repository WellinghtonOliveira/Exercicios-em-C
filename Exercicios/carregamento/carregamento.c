#include <stdio.h>
#include <windows.h>

int main() {

	int tempoCarregamento;
	char carregamento[3][10] = { "[", "=", "]" };
	char carregarNovamente;

	printf("Digite o tempo de carregamento: ");
	scanf(" %d", &tempoCarregamento);

	do {
		 system("cls");
		if (tempoCarregamento >= 3) {
			for (int j = 0; j <= tempoCarregamento; j++) {
				if (j == 0) {
					printf("%s", carregamento[0]);
				} else if (j < tempoCarregamento) {
					printf("%s", carregamento[1]);
				} else {
					printf("%s", carregamento[2]);
				}
			}
		} else {
			printf("\nDigite um numero maior ou igual a 3");
			return 1;
		}
		printf("\nCarregar Novamente [S|N] => ");
		scanf(" %c", &carregarNovamente);
		system("cls");
	} while (carregarNovamente == 'S' || carregarNovamente == 's');

	printf("%c", carregarNovamente);
	printf("Saindo...");
	return 0;
}