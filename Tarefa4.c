/* Lívia Lutz dos Santos - 2211055 
Luiza Marcondes Paes Leme - 2210275
*/

#include <stdio.h>
#include "t4.h"


int main(void) {
	FILE* f,*m;
	unsigned char c;
	No* lista,*arvore;

	//Array que contém o número de ocorrências de cada char no arquivo

	int ocorrencias[128];

	//Inicializa o array com 0

	for (int i = 0; i < 128; i++) {
		ocorrencias[i] = 0;
	}

	//Abre o arquivo

	f = fopen("frase.txt", "r");

	if (f == NULL) {
		printf("erro ao abrir arquivo\n");
		return NULL;
	}

	/*Lê os caracteres do arquivo e de acordo com seu valor ASCII(indice no array)
	* e incrementa 1 toda vez q esse caracter for encontrado */

	while (!feof(f)) {
		fread(&c, sizeof(unsigned char), 1, f);
		ocorrencias[c]++;
	}
	
	/* Fechando o arquivo */

	fclose(f);
	
	//Imprimindo o array de caracteres resultante

	imprimeArray(ocorrencias, 128);

	/*Criando a lista encadeada ordenada por prioridade(menos->mais ocorrências)
	* para os caracteres do array */

	lista = formaLista(ocorrencias, 128);

	//Imprimindo a lista resultante

	imprimeLista(lista);
	
	/*Montando a árvore binária */
	
	arvore = montaArv(lista);
	
	/* Imprimindo a árvore binária usando o percurso pre-ordem */

	printf("\nArvore em pre-ordem:\n\n");

	arvImprime(arvore);

	/* Abrindo o arquivo onde a mensagem codificada será gravada */
	
	m = fopen("mensagem.txt", "w");

	if (m == NULL) {
		printf("Erro ao abrir o arquivo\n");
		return -1;
	}
	
	/* Percorrendo a árvore binária em percurso pré-ordem para escrever a mensagem codificada no arquivo */

	comprime(arvore, m);
	
	/*Fechando o arquivo */

	fclose(m);
	
	return 0;
}
