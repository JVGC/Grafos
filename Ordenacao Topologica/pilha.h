#ifndef _PILHA_H
#define _PILHA_H

typedef int elem;
struct pilha{
	elem* vet;
	int topo;
};

typedef struct pilha pilha_t;



pilha_t* cria_pilha();
void push(pilha_t* p, elem x);
void pop(pilha_t* p, elem* x);
void libera(pilha_t* p);
void ImprimirPilha(pilha_t* p);

#endif
