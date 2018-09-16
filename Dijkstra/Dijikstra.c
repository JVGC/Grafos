#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "fila.h"
#include "Dijikstra.h"


int* Dijikstra(Mat_Adj* G, int origem, int destino)
{	
	int i; 

	int* predecessor = (int*) malloc(sizeof(int) * G->nVertices);
	int* dist = (int*) malloc(sizeof(int) * G->nVertices); // Vetor de distancia
	int* adj = NULL;

	int custo;
	no_t tupla;
	fila_t* Q = CriarFila();


	// Inicializando os vetores e inserindo a origem na fila
	for(i = 0; i < G->nVertices; i++)
	{	
		predecessor[i] = -1;
		dist[i] =  INT_MAX;
	}

	dist[origem] = 0;

	InserirFila(Q, origem, dist[origem]);
	
	// Enquanto a fila nao estiver vazia, o algoritmo continua
	while(Q->inicio != NULL)
	{
		// pego a primeira posicao da fila de prioridade, e removo o no
		tupla = Front(Q);
		RemoverFila(Q);
		
		// vetor de adjacentes do ID retirado da fil
		adj = VerticesAdjacentes(G, tupla.ID);

		for(i = 0; i < G->nVertices; i++)
		{
			if(adj[i] > 0) // O VÉRTICE EXISTE
			{	// Se a distancia do proximo no (i) for maior que a soma da distancia ja percorrida + o peso da aresta
				if(dist[i] > (dist[tupla.ID] + G->vertices[tupla.ID][i])){
					
					// atualizo o valor da distancia ja percorrida
					dist[i] = (dist[tupla.ID] + G->vertices[tupla.ID][i]);
					
					// atualizo o vetor de predecessor e insiro o novo no na fila de prioridades
					predecessor[i] = tupla.ID;
					InserirFila(Q, i, dist[i]);
					


				}


			}
		}


	}

	return predecessor;
}

void ImprimirCaminho(int* predecessor, int origem, int destino)
{	// PRIMEIRO VÉRTICE A SER PRINTADO É A ORIGEM 
	// E TAMBÉM CONDIÇÃO DE PARADA DA RECURSÃO
	if(origem == destino)
		printf("%d ", origem);
	else if(predecessor[destino] == -1) // SE NÃO CHEGUEI NO DESTINO
		return ;
	else{ // CHAMO RECURSIVAMENTE PASSANDO O PREDECESSOR DO DESTINO
		ImprimirCaminho(predecessor, origem, predecessor[destino]);
		// PRINTO O DESTINO
		printf("%d ",destino);
	}
	

}
