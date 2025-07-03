#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* mergeAlternately(char* word1, char* word2) {
    int tamanhoWord1 = strlen(word1);
    int tamanhoWord2 = strlen(word2);
    int tamanhoJuntos = tamanhoWord1 + tamanhoWord2;

    // aloca espaço na heap para a nova string
    char* texto = malloc(tamanhoJuntos + 1); // +1 para o  '\0'
    if (texto == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    int i = 0, j = 0, k = 0;
 
    while (i < tamanhoWord1 || j < tamanhoWord2) {
        if (i < tamanhoWord1)
            texto[k++] = word1[i++];
        if (j < tamanhoWord2)
            texto[k++] = word2[j++];
    }

    texto[k] = '\0'; // termina a string
    return texto;
}

int main() {
    char w1[] = "aaaaa", w2[] = "bbbbb";

    char* resultado = mergeAlternately(w1, w2);
    if (resultado != NULL) {
        printf("Resultado: %s\n", resultado);
        free(resultado); // libera a memória
    }
 
    return 0;
}
  