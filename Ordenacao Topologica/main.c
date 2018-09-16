#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
#include "matriz.h"



int main()
{
	int nArestas, nVertices;

	int origem, destino;

	scanf("%d", &nVertices);
	scanf("%d", &nArestas);

	Mat_Adj* mat = CriarMatriz(nVertices);
	mat->direcionado = 1; // GRAFO DÍGRAFO
	int i, j;

	// ADICIONO TODAS AS ARESTAS NO GRAFO
	for(i = 0; i < nArestas; i++)
	{
		scanf("%d", &origem);
		scanf("%d", &destino);
		AdicionarAresta(mat, origem, destino, 1);
	}

	//E EXECUTO A BUSCA
	
	DFS(mat);

	return 0;

}
