#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "Dijikstra.h"


int main()
{

	int nArestas, nVertices;

	int origem, destino, peso;

	scanf("%d", &nVertices);
	scanf("%d", &nArestas);

	Mat_Adj* mat = CriarMatriz(nVertices);
	mat->direcionado = '1'; // GRAFO DÍGRAFO
	int i, j;

	// ADICIONO TODAS AS ARESTAS NO GRAFO
	for(i = 0; i < nArestas; i++)
	{
		scanf("%d", &origem);
		scanf("%d", &destino);
		scanf("%d", &peso);
		AdicionarAresta(mat, origem, destino, peso);
	}

	// LENDO OS VERTICES DE ORIGEM E DESTINO E REALIZANDO O ALGORITMO DE DIJIKSTRA
	while(!feof(stdin)){
		scanf("%d", &origem);
		scanf("%d", &destino);
		if(feof(stdin))
			break;

		int* predecessor = Dijikstra(mat, origem, destino);
		
		ImprimirCaminho(predecessor, origem, destino);

		printf("\n");

	}

	return 0;

}


