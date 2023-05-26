#include <stdio.h>
#include <stdlib.h>
#include "t4.h"

struct no {
	char a;
	int ocorrencia;
	No* dir;
	No* esq;
	No* prox;
};


void imprimeArray(int ocorrencias[], int tam){
	printf("Array:\n");
	for (int i = 0; i < tam; i++) {
		printf("%c - %d ocorrencias\n", i, ocorrencias[i]);
	}
	return;	
}

No* insereLista(No* lista, char c, int quant) {
	No* novo = NULL, * p = lista, * ant = NULL;

	novo = (No*)malloc(sizeof(No));
	
	if (novo == NULL) {
		printf("Erro na alocacao");
		return NULL;
	}
	
	novo->a = c;
	novo->ocorrencia = quant;
	novo->dir = NULL;
	novo->esq = NULL;

	if (lista == NULL) {
		lista = novo;
		novo->prox = NULL;
		return lista;
	}

	if (p->ocorrencia >= quant) {
		lista = novo;
	}

	else {
		for (; p != NULL; p = p->prox) {
			if (p->prox != NULL) {
				if (p->prox->ocorrencia >= quant) {
					ant = p;
					p = p->prox;
					break;
				}
			}
			ant = p;
		}
		ant->prox = novo;

	}

	novo->prox = p;
	
	return lista;
}

No* formaLista(int ocorrencias[], int tam) {
	No* lista = NULL;
	for (int i = 0; i < tam; i++) {
		if (ocorrencias[i] > 0)
			lista = insereLista(lista, i, ocorrencias[i]);
	}
	return lista;
}
	
void imprimeLista(No* lista) {
	printf("\nLista encadeada por prioridade:\n\n");
	for (No* p = lista; p != NULL; p = p->prox) {
		printf("%c - %d ocorrencias\n", p->a, p->ocorrencia);
	}
	return;
}

No* montaArv(No* lista){
	No** plista = &lista, No* arv;
	while(lista->prox != NULL){
		arv = montaArvzinha(plista);
		if(arv == NULL)
			printf("Erro ao montar arvore");
		lista = insereArvLista(lista, arv);
	}
	return lista;
}

No* montaArvzinha(No ** lista){
	No * p1 = *(lista), * p2, * p3, * arv;
	if(p1 == NULL)
		return NULL;
	p2 = p1->prox;
	p3 = p2->prox;
	arv = (No*)malloc(sizeof(No));
	if(arv == NULL)
		return NULL;
	arv->a = '+';
	arv->ocorrencia = p1->ocorrencia + p2->ocorrencia;
	arv->esq = p1;
	arv->dir = p2;
	arv->prox = NULL;
	*(lista) = p3;
	return arv;
	
}


No * insereArvLista(No* lista, No* arv){
	No* p = lista, * ant = NULL;

	if (lista == NULL) {
		lista = arv;
		return lista;
	}
	
	if(p->prox == NULL){
		if (p->ocorrencia >= arv->ocorrencia) {
			lista = arv;
			arv->prox = p;
		}
		else
			p->prox = arv;
		return lista;
	}

	else {
		for (; p != NULL; p = p->prox) {
			if (p->prox != NULL) {
				if (p->prox->ocorrencia >= arv->ocorrencia) {
					ant = p;
					p = p->prox;
					break;
				}
			}
			ant = p;
		}
		ant->prox = arv;

	}

	arv->prox = p;
	return lista;
}
	
	
}

/*arv_vazia verifica se a árvore binária passada como parâmetro está vazia, retorna 1 (True) se estiver,
senão, retorna 0 (False)*/

int arv_vazia(No* a) {
	return a == NULL;
}


/*arvImprime imprime a árvore binária em pré- ordem, ou seja, primeiro as informações no nó raiz,
seguido dos nós à esquerda e por fim os nós à direita*/

void arvImprime(No* a){
	/*Até o final da árvore, imprimimos suas informações*/

	if (!arv_vazia(a)) {
		/*Imprimindo as informações do nó raiz, incluindo seu valor inteiro e os ponteiros do
		nó à esquerda, à direita e seu próprio ponteiro*/

		printf("No:%p Esquerda:%p Char:%c Direita:%p\n", a, a->esq, a->a, a->dir);
		
		/*Imprime as informações dos nós à esquerda recursivamente*/
		
		arvImprime(a->esq); 
		
		/*Imprime as informações dos nós à direita recursivamente*/
		
		arvImprime(a->dir); 
	}
}
