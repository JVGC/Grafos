#include <stdio.h>
#include <stdlib.h>
#include "listaADJ.h"

Lista_Adj* CriarLista(int nVertices)
{

	// ALOCA A MEMORIA DAS LISTAS DE CADA VERTICE, E INICIALIZA AS VARIAVEIS
	int i;
	Lista_Adj* a = (Lista_Adj*) malloc(sizeof(Lista_Adj));
	a->adj = (vertices*) malloc(sizeof(vertices)*nVertices);

	for(i = 0; i < nVertices; i++)
	{
		a->adj[i].VerticesAdjacentes = cria_lista();
		a->adj[i].v1 = i;
	}
	a->menor.v1 = -1;
	a->menor.v2 = -1;
	a->menor.peso = -1;
	a->nVertices = nVertices;


}

void DestroiLista(Lista_Adj* a)
{
	int i;
	for (i = 0; i < a->nVertices; i++)
	{
		libera_lista(a->adj[i].VerticesAdjacentes);
	}
	free(a->adj);
	free(a);
}

void AdicionarAresta2(Lista_Adj* a, int v1, int v2, int peso)
{
	insere(a->adj[v1].VerticesAdjacentes, v2, peso);
	
	if(a->direcionado == '0') // GRAFO NAO DIRECIONADO
		insere(a->adj[v2].VerticesAdjacentes, v1, peso);
	if(a->menor.v1 == -1) //PRIMEIRA ARESTA SENDO ADICIONADA
	{
		a->menor.v1 = v1;
		a->menor.v2 = v2;
		a->menor.peso = peso;
	}else if(a->menor.peso > peso) // SE A ARESTA NOVO TIVER PESO MENOR QUE A MENOR DO GRAFO
	{
		a->menor.v1 = v1;
		a->menor.v2 = v2;
		a->menor.peso = peso;
	}
}
void RemoverAresta2(Lista_Adj* a, int v1, int v2)
{
	retira(a->adj[v1].VerticesAdjacentes, v2);
	if(a->direcionado == '0') // GRAFO NAO DIRECIONADO
		retira(a->adj[v2].VerticesAdjacentes, v1);
}
void ImprimirGrafo2(Lista_Adj* a)
{
	// IMPRIME A LISTA DE ADJACENTE DE CADA VERTICE
	int i;
	for(i = 0; i < a->nVertices; i++)
	{
		printf("%d. ", i);
		imprimir_lista(a->adj[i].VerticesAdjacentes);
		printf("\n");
	}

}

void MenorAresta2(Lista_Adj* a)
{
	// SE FOR UM DIGRAFO, ENTAO IMPRIME NA ORDEM
	if(a->direcionado == '1')
	{
		printf("%d ", a->menor.v1);
		printf("%d", a->menor.v2);
		printf("\n");
		return ;
	}
	// SE NAO, IMPRIME NA ORDEM CRESCENTE DOS VERTICES
	if(a->menor.v1 < a->menor.v2)
	{	
		printf("%d ", a->menor.v1);
		printf("%d", a->menor.v2);
		printf("\n");
	}else
	{
		printf("%d ", a->menor.v2);
		printf("%d", a->menor.v1);
		printf("\n");
	}
}

void VerticesAdjacentes2(Lista_Adj* a, int vertice)
{
	// ATUAL EH USADO PARA PERCORRER A LISTA

	no_t* atual = a->adj[vertice].VerticesAdjacentes->inicio;

	while(atual != NULL)
	{
		printf("%d ", atual->vertice);
		atual = atual->prox;
	}
	printf("\n");
}
void ImprimirGrafoTransposto2(Lista_Adj* a)
{
	int i;

	// CRIANDO UMA LISTA ADJACENTE AUXILIAR
	Lista_Adj* t = CriarLista(a->nVertices);
	no_t* atual; // PERCORRER AS LISTAS
	for(i = 0; i < a->nVertices;i++)
	{
		// ATUAL EH INICIALIZADO NO INICIO DE CADA LISTA
		atual = a->adj[i].VerticesAdjacentes->inicio;
		do
		{
			// SE O INICIO FOR NULL
			if(atual == NULL)
				break;
			// ADICIONO A ARESTA DE FORMA CONTRARIA NA NOVA LISTA DE ADJACENCIA
			AdicionarAresta2(t, atual->vertice, i, atual->peso);
			atual = atual->prox; // ANDO COM ATUAL

		}while(atual != NULL);
	}
	// IMPRIMO O GRAFO TRANSPOSTO
	ImprimirGrafo2(t);
}