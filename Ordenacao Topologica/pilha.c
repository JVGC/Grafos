#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
// INICIALIZA A PILHA



pilha_t* cria_pilha()
{
	pilha_t* p = (pilha_t*) malloc(sizeof(pilha_t));

	p->vet = (elem*) malloc(sizeof(elem)*100);

	p->topo = 0; 

	return p;

}

// LIBERA A PPILHA
void libera_pilha(pilha_t* p)
{
	free(p->vet);
	free(p);

}
// EMPILHA
void push(pilha_t* p, elem x)
{	
	p->topo += 1;
	p->vet[p->topo] = x;
}

// DESEMPILHA
void pop(pilha_t* p, elem* x)
{
	*x = p->vet[p->topo];
	p->topo--;
}

void ImprimirPilha(pilha_t* p)
{
	while(p->topo >0)
	{
		printf("%d ",p->vet[p->topo]);
		p->topo--;
	}
}