#include <stdio.h>
#include <stdlib.h>
#include "lista.h"



lista_t* cria_lista(){
	lista_t* l = (lista_t*) malloc(sizeof(lista_t));
	l->inicio = NULL;

	return l;
}

void insere(lista_t* l, int v, int peso){
	// NOVO NO DA LISTA
	no_t* p = (no_t*) malloc(sizeof(no_t));
	p->vertice = v;
	p->peso = peso;
	
	// SE NAO HOUVER NENHUM NO NA LISTA
	if(l->inicio == NULL){
		l->inicio = p;
		p->prox = NULL;
		return ; // SE O NOVO NO FOR MENOR QUE O PRIMEIRO
	}else if(p->vertice < l->inicio->vertice){
		p->prox = l->inicio;
		l->inicio = p;
		return ; // SE O VERTICE JA EXISTIR NA LISTA
	}else if(p->vertice == l->inicio->vertice){
		l->inicio->peso = peso;
		free(p);
		return ;
	}
	// NOS AUXILIARES PARA PERCORRER A LISTA
	no_t* atual = l->inicio;
	no_t* prox = atual->prox;


	while(prox != NULL){	
		// SE O PROX FOR MAIOR QUE O NOVO VERTICE
		// ENTAO p TEM QUE SER ADICIONADO ENTRE ATUAL E PROX
		if(prox->vertice > p->vertice){
			atual->prox = p;
			p->prox = prox;
			return ;

		}else if(prox->vertice == p->vertice){ // SE O VERTICE JA EXISTIR NA LISTA
			prox->peso = peso;
			free(p);
			return ;


		}
		else{ // ANDANDO NA LISTA
			atual = atual->prox;
			prox = prox->prox;
		}


	}
	// SE CHEGAR AQUI EH PORQUE O NO TEM QUE SER INSERIDO NO FINAL DA LISTA
	atual->prox = p;
	p->prox = NULL;


}
void retira(lista_t* l, int x){
	// NOS AUXILIARES PARA PERCORRER A LISTA
	no_t* atual, *prox;
	atual = l->inicio;
	prox = atual->prox;
	// SE NAO HOUVER ELEMENTO NA LISTA
	if(l->inicio == NULL)
		return ;
	// SE A ARESTA A SER EXCLUIDA EH A PRIMEIRA DA LISTA
	if(atual->vertice == x){
		l->inicio = prox;
		free(atual);
		return ;
	}


	while(prox != NULL){	
		// SE ENCONTREI O VERTICE A SER EXCLUIDO
		if(prox->vertice == x){	
			// LIGO O ANTERIOR DESSE NO, AO SEU PROXIMO, E DESALOCO O PROX
			atual->prox = prox->prox;
			free(prox);
			return ;
		}else{	// ANDANDO PELA LISTA
			atual = atual->prox;
			prox = prox->prox;
		}
	}

}

void libera_lista(lista_t* l){
	no_t* p;
	while(l->inicio != NULL){
		p = l->inicio;
		l->inicio = l->inicio->prox;
		free(p);
	}
	free(l);
}

void imprimir_lista(lista_t* l){
	no_t* atual = l->inicio;

	while(atual != NULL){
		printf("%d(%d) ", atual->vertice, atual->peso);
		atual = atual->prox;
	}

}