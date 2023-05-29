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

/* Função que imprime os caracteres e suas respectivss ocorrências no  array */

void imprimeArray(int ocorrencias[], int tam){
	printf("Array:\n");
	for (int i = 0; i < tam; i++) {
		printf("'%c' - %d ocorrencias\n", i, ocorrencias[i]);
	}
	return;	
}

/* Função que insere caracteres e suas respectivas ocorrências numa lista encadeada de forma ordenada */

/* OBS: A ordenação obedece a seguinte regra:
	Caracteres com menores ocorrências tem maior prioridade, enquanto os de maior ocorrência ficam no final da lista */

No* insereLista(No* lista, char c, int quant) {
	No* novo = NULL, * p = lista, * ant = NULL;
	
	/* Criamos um novo nó da lista */
	novo = (No*)malloc(sizeof(No));
	
	if (novo == NULL) {
		printf("Erro na alocacao");
		return NULL;
	}
	
	/* inserimos suas informações */
	novo->a = c;
	novo->ocorrencia = quant;
	novo->dir = NULL;
	novo->esq = NULL;
	
	/* Caso a lista esteja vazia, esse nó será o primeiro */

	if (lista == NULL) {
		lista = novo;
		novo->prox = NULL;
		return lista;
	}
	
	/* Caso a lista tenha 1 elemento apenas e o novo tiver menos ocorrências, ele será o novo primeiro elemento */

	if (p->ocorrencia >= quant) {
		lista = novo;
	}
	
	/* Procuramos a posição certa para inserir o novo elemento, guardando os nos anteriores e próximos */

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

/* Função que insere cada elemento de um array de inteiros numa lista encadeada ordenada por prioridade */

No* formaLista(int ocorrencias[], int tam) {
	No* lista = NULL;
	for (int i = 0; i < tam; i++) {
		/* inserimos apenas os elementos que tem ocorrência no array */
		if (ocorrencias[i] > 0)
			lista = insereLista(lista, i, ocorrencias[i]);
	}
	return lista;
}

/*Função que imprime os caracteres e a ocorrência de cada no de uma lista encadeada ordenada por prioridade */
	
void imprimeLista(No* lista) {
	printf("\nLista encadeada por prioridade:\n\n");
	for (No* p = lista; p != NULL; p = p->prox) {
		printf("'%c' - %d ocorrencias\n", p->a, p->ocorrencia);
	}
	return;
}

/*Função que insere árvores binárias numa lista encadeada ordenada por prioridade */

No* montaArv(No* lista){
	No** plista = &lista, No* arv;
	
	/*Para cada nó da lista, formamos uma árvore a partir dele e o inserimos na lista*/ 
	while(lista->prox != NULL){
		arv = montaArvzinha(plista);
		if(arv == NULL)
			printf("Erro ao montar arvore");
		lista = insereArvLista(lista, arv);
	}
	
	return lista;
}

/* Função que monta uma árvore binária a partir de uma lista encadeada orndenada por prioridade */

No* montaArvzinha(No ** plista){
	No * p1 = *(plista), * p2, * p3, * arv;
	
	/* Caso de lista vazia */
	
	if(p1 == NULL){
		return NULL;
	}
	
	/*Guardando os próximos 2 nós da lista */
	p2 = p1->prox;
	p3 = p2->prox;
	
	arv = (No*)malloc(sizeof(No));
	if(arv == NULL)
		return NULL;
	
	/* Cada no será a soma das ocorrências de seus 2 filhos */
	
	arv->a = '+';
	
	arv->ocorrencia = p1->ocorrencia + p2->ocorrencia;
	
	arv->esq = p1;
	
	arv->dir = p2;
	
	arv->prox = NULL;
	
	*(plista) = p3;
	
	return arv;
}

/* Função auxiliar que insere uma árvore binária como nó de uma lista encadeada */

No * insereArvLista(No* lista, No* arv){
	No* p = lista, * ant = NULL;
	
/* Caso a lista esteja vazia, inserimos a árvore como primeiro nó */

	if (lista == NULL) {
		lista = arv;
		return lista;
	}
	
/* Caso se ser o primeiro elemento */
	
	if(p->prox == NULL){
	
	/* Ordenando por prioridade */
		
		if (p->ocorrencia >= arv->ocorrencia) {
			lista = arv;
			arv->prox = p;
		}
		else
			p->prox = arv;
		return lista;
	}
	
/* Buscamos a posição ideal para inserir o nó da árvore na lista */
	
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
	
/*arvImprime imprime a árvore binária em pré- ordem, ou seja, primeiro as informações no nó raiz,
seguido dos nós à esquerda e por fim os nós à direita*/

void arvImprime(No* a){
	/*Até o final da árvore, imprimimos suas informações*/

	if (a != NULL) {

		printf("Char:'%c' - ocorrencia:%d\n", a->a,a->ocorrencia);

		/*Imprime as informações dos nós à esquerda recursivamente*/

		arvImprime(a->esq);

		/*Imprime as informações dos nós à direita recursivamente*/

		arvImprime(a->dir);
	}
}

/* Função que percorre a árvore e gera os códigos */

void codifica(No* arv, int cod[], int ind, Cod vCodigos[], int indCod) {
	
    /* Se o nó for folha, ele tem como valor um caractere para codificar */
	
    if (arv->esq == NULL && arv->dir == NULL) {
	    
        /* Armazena os valores com o código em uma variável */
        
	Cod codificado;
        codificado.c = arv->a;
        codificado.tam = ind;

        for (int i = 0; i < ind; i++) {
            codificado.cod[i] = cod[i];
        }

        /* Coloca o valor no vetor de códigos*/
	    
        vCodigos[indCod] = codificado;
        (indCod)++;
    }

    /* Chama à esquerda e coloca 0 no código */
	
    if (arv->esq != NULL) {
        cod[ind] = 0;
        codifica(arv->esq, cod, ind + 1, vCodigos, indCod);
    }

    /* Chama à direita e coloca 1 no código */
	
    if (arv->dir != NULL) {
        cod[ind] = 1;
        codifica(arv->dir, cod, ind + 1, vCodigos, indCod);
    }
}

/* Função que percorre a árvore e gera os códigos */

int codifica(No* arv, int cod[], int ind, Cod vCodigos[], int indCod) {

	/*Se o nó for folha, e um caracter, logo o inserimos em vCodigos*/

	if (arv->esq == NULL && arv->dir == NULL) {
		Cod* codificado = (Cod*)malloc(sizeof(Cod));
		if (codificado == NULL) {
			printf("Erro na alocacao");
			exit(1);
		}
		codificado->c = arv->a;
		codificado->tam = ind;
		for (int i = 0; i < ind; i++) {
			codificado->cod[i] = cod[i];
		}
		vCodigos[indCod] = *codificado;
		indCod++;
	}

	/*Repetimos o processo para a subárvore esquerda e direita*/

	if (arv->esq != NULL) {
		cod[ind] = 0;
		indCod = codifica(arv->esq, cod, ind + 1, vCodigos, indCod);
	}
	if (arv->dir != NULL) {
		cod[ind] = 1;
		indCod = codifica(arv->dir, cod, ind + 1, vCodigos, indCod);
	}
	return indCod;
}

/* Função que imprime cada caracter codificado em binário*/

void imprimeCodifica(Cod* vCodigos, int numC) {
	printf("\nCodigos:\n");

	for (int i = 0; i < numC; i++) {
		printf("\n'%c' - ", vCodigos[i].c);

		for (int k = 0; k < vCodigos[i].tam; k++)
			printf("%d", vCodigos[i].cod[k]);
	}
}

/* Função que busca o nó correspondente ao caracter no array códigos */

Cod* buscaCod(Cod* vCodigos, char c){
	Cod* p = vCodigos;

	if (p == NULL) {
		return NULL;
	}

	while (p->c != c) {
		p++;
	}
	
	return p;
}

