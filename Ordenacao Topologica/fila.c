 #include <stdio.h>
#include <stdlib.h>
#include "fila.h"


// ALOCA MEMORIA E SETA OS PONTEIROS PARA NULL
fila_t* CriarFila()
{
	fila_t* f = (fila_t*) malloc(sizeof(fila_t));
	f->inicio = NULL;
	f->fim = NULL;

	return f;
}

void InserirFila(fila_t* f, int x)
{
	// CRIA O NOVO NO
	no_t* p = (no_t*) malloc(sizeof(no_t));
	p->info = x;
	p->prox = NULL;
	
	if(f->inicio == NULL) // PRIMEIRO ELEMENTO NA FILA
	{
		f->inicio = p;
		f->fim = p;
	}else{ // JA TEM UM ELEMENTO NA FILA
		f->fim->prox = p;
		f->fim = p;
	}
}
// REMOVENDO O PRIMEIRO ELEMENTO DA FILA
void RemoverFila(fila_t* f)
{
	no_t* aux = f->inicio;
	f->inicio = aux->prox;
	if(aux != NULL)
		free(aux);

}
// DESALOCANDO TODA A MEMÓRIA DA FILA
void DestruirFila(fila_t* f)
{
	no_t* p;
	while(f->inicio != NULL)
	{
		p = f->inicio;
		f->inicio = f->inicio->prox;
		free(p);
	}
	free(f);
}

void ImprimirFila(fila_t* f)
{

	no_t* aux = f->inicio;

	while(aux != NULL)
	{
		printf("%d ", aux->info);
		aux = aux->prox;
	}


}