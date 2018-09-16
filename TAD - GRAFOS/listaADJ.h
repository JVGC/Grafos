#ifndef _LISTAADJ_H_
#define _LISTAADJ_H_

#include "lista.h"

typedef struct 
{
	int v1;
	int v2;
	int peso;
}aresta_no;

typedef struct 
{
	int v1;
	lista_t* VerticesAdjacentes; // lista com os vertices adjacentes a v1
}vertices;

typedef struct
{
	vertices* adj; // VETOS DE VERTICES (VETOR DE LISTAS)
	int nVertices; // NUMERO DE VERTICES
	char direcionado; // 1 SE O GRAFO EH DIRECIONADO, 0 SE NAO
	aresta_no menor; // ARESTA DE MENOR PESO
	
}Lista_Adj;

Lista_Adj* CriarLista(int nVertices); // CRIA A LISTA ADJACENTE
void AdicionarAresta2(Lista_Adj* adj, int v1, int v2, int peso); // INSERE A ARESTA NA LISTA
void RemoverAresta2(Lista_Adj* adj, int v1, int v2); // REMOVE A ARESTA DA LISTA
void ImprimirGrafo2(Lista_Adj* adj); // IMPRIME O GRAFO
void MenorAresta2(Lista_Adj* adj); // IMPRIME A ARESTA DE MENOR PESO DO GRAFO
void VerticesAdjacentes2(Lista_Adj* adj, int vertice); // IMPRIME OS VERTICES ADJACENTES A DETERMINADO VERTICE
void ImprimirGrafoTransposto2(Lista_Adj* adj); // IMPRIME O TRANSPOSTO DO GRAFO
void DestroiLista(Lista_Adj* a); // DESALOCA A MEMORIA DA LISTA


#endif