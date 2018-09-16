#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "PRIM.h"


int main()
{

	int nArestas, nVertices;

	int origem, destino, peso;

	scanf("%d", &nVertices);
	scanf("%d", &nArestas);

	Mat_Adj* mat = CriarMatriz(nVertices);
	mat->direcionado = '0'; // GRAFO DÍGRAFO
	int i, j;

	// ADICIONO TODAS AS ARESTAS NO GRAFO
	for(i = 0; i < nArestas; i++)
	{
		scanf("%d", &origem);
		scanf("%d", &destino);
		scanf("%d", &peso);
		AdicionarAresta(mat, origem, destino, peso);
	}

	PRIM(mat);

}


