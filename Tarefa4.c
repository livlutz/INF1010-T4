/* Lívia Lutz dos Santos - 2211055 
Luiza Marcondes Paes Leme - 2210275
*/

#include <stdio.h>
#include <stdlib.h>
#include "t4.h"

/* Struct usada para manipular o array, a lista encadeada e a árvore binária */

struct no {
	char a;
	int ocorrencia;
	No* dir;
	No* esq;
	No* prox;
};

/* Struct usada para guardar o código para compressão */

struct cod {
	char c;
	int cod[8];
	int tam;
};


int main(void) {
	FILE* f,*b;
	unsigned char c;
	No* lista,*arvore;
	int numC = 0, cod[8], indCod = 0, numL = 0;
	Cod* vCodigos,*p;
	
	
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
		return -1;
	}

	/*Lê os caracteres do arquivo e de acordo com seu valor ASCII(indice no array)
	* e incrementa 1 toda vez q esse caracter for encontrado */

	while (!feof(f)) {
		fread(&c, sizeof(unsigned char), 1, f);
		ocorrencias[c]++;
		numL++;
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
	
	for(No* p = lista; p != NULL; p = p->prox){
		numC++;
	}
	
	/*Montando a árvore binária */
	
	arvore = montaArv(lista);
	
	/* Imprimindo a árvore binária usando o percurso pre-ordem */

	printf("\nArvore em pre-ordem:\n\n");

	arvImprime(arvore);
	
	/*Array de codigos para guardar os caracteres codificados*/

	vCodigos = (Cod*)malloc(numC * sizeof(Cod));
	if (vCodigos == NULL)
		return -1;

	indCod = codifica(arvore, cod, 0, vCodigos,indCod);

	/*Imprimindo cada caractere e sua codificacao*/

	imprimeCodifica(vCodigos, numC);

	/* Lendo cada caracter do arquivo e imprimindo a mensagem comprimida*/

	f = fopen("frase.txt", "r");

	if (f == NULL) {
		printf("erro ao abrir arquivo\n");
		return -1;
	}

	vComprimido* = (char*)malloc(sizeof(char) * numL);
	if(vComprimido == NULL){
		printf("Erro na alocacao\n");
		exit(1);
	}
	
	for(int i = 0; i < numL; i++)
		vComprimido[i] = 0;
	int pos = 0, bit = 0;
	printf("\n\nMensagem comprimida:\n");

	while (!feof(f)) {
		fread(&c, sizeof(unsigned char), 1, f);
		p = buscaCod(vCodigos, c);
		for (int i = 0; i < p->tam; i++){
			printf("%d", p->cod[i]);
			vComprimido[pos] |= p->cod[i];
			if(bit == 7){
				printf("\n%x\n", vComprimido[pos]);
				pos++;
				bit = 0;
			}
			else{
				vComprimido[pos] <<= 1;
				bit++;
			}
		}
		printf(" ");
	}

	/* Fechando o arquivo */

	fclose(f);
	
	b = fopen("comprimido.dat","wb");
	
	if(b == NULL){
		printf("Erro ao abrir arquivo binario\n");
		exit(1);
	}
	
	int gravado = 0;
	gravado = fwrite(&vComprimido[0], sizeof(char), pos, b);
	printf("\nBytes gravados no arquivo: %d");
	
	fclose(b);
	
	return 0;
}
