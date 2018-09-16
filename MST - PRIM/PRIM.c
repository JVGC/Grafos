#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "fila.h"
#include "PRIM.h"


int* PRIM(Mat_Adj* G)
{	
	int i; 

	int* predecessor = (int*) malloc(sizeof(int) * G->nVertices);
	int* arvore = (int*) malloc(sizeof(int) * G->nVertices);
	int* adj = NULL;

	int custo;
	no_t* tupla;
	fila_t* Q = CriarFila();



	for(i = 0; i < G->nVertices; i++)
	{	
		predecessor[i] = -1;
		arvore[i] = 0;
		custo =  INT_MAX;
		InserirFila(Q, i, custo);
	}



	atualizar(Q, 0, 0); //ATUALIZA O VERTICE 0 COM O CUSTO 0
	
	
	while(Q->inicio != NULL)
	{
		tupla = RemoverFila(Q);
		//printf("tupla = %d\n", tupla->ID);
		
		arvore[tupla->ID] = 1;
		if(predecessor[tupla->ID] != -1)
		{
			if(predecessor[tupla->ID] < tupla->ID)
				printf("(%d,%d) ", predecessor[tupla->ID], tupla->ID);
			else
				printf("(%d,%d) ", tupla->ID, predecessor[tupla->ID]);
		}

		

		adj = VerticesAdjacentes(G, tupla->ID);

		for(i = 0; i < G->nVertices; i++)
		{
			if(adj[i] > 0) // O VÉRTICE EXISTE
			{	
				custo = Custo(Q, i);
				if((arvore[i] == 0) && (G->vertices[tupla->ID][i] < custo))
				{
					atualizar(Q, i, G->vertices[tupla->ID][i]);
					//ImprimirFila(Q);
					predecessor[i] = tupla->ID;
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
