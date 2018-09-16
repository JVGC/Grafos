#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
#include "fila.h"

#define BLACK 1
#define GRAY 2
#define WHITE 0


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

void BFS(Mat_Adj* mat, int origem, int destino)
{
	// INICIALIZANDO TODO OS VETORES NECESSÁRIOS
	// CORES: WHITE PARA NÃO VISITADO
		//    GRAY PARA JÁ VISITADO
		//	  BLACK PARA QUANDO TODO OS VÉRTICES ADJACENTES JÁ FORAM VISITADOS

	// DISTANCIA É O VETOR QUE DÁ A DISTANCIA DE DETERMINANDO VÉRTICE PARA A ORIGEM
	// PREDECESSOR DE CADA VÉRTICE(ATRAVÉS DE QUAL VÉRTICE SE CHEGOU NO ATUAL)

	int* color = (int*) malloc(sizeof(int)*mat->nVertices);
	int* distancia = (int*) malloc(sizeof(int)*mat->nVertices);
	int* predecessor = (int*) malloc(sizeof(int)*mat->nVertices);

	int i;
	// TODOS OS VÉRTICES NÃO FORAM VISITADOS
	for(i = 0; i < mat->nVertices; i++)
	{
		color[i] = WHITE;
	}
	// A DISTANCIA É NULA POR ENQUANTO
	for(i = 0; i < mat->nVertices; i++)
	{
		distancia[i] = -1;
	}
	// NINGUÉM TEM PREDECESSORES POR ENQUANTO
	for(i = 0; i < mat->nVertices; i++)
	{
		predecessor[i] = -1;
	}
	// VISITO O VÉRTICE DE ORIGEM
	color[origem] = GRAY;
	distancia[origem] = 0; // A DISTANCIA PARA ELE MESMO É 0
	predecessor[origem] = origem; // O PREDECESSOR DA ORIGEM É ELE MESMO

	fila_t* f = CriarFila(); 

	InserirFila(f, origem); // INSIRO A ORIGEM NO INICIO DA FILA

	int* adj; // VETOR DE ADJACENTES
	int u; // VÉRTICE ATUAL
	while(f->inicio != NULL)
	{
		u = f->inicio->info; // O VÉRTICE ATUAL É O DO NO INICIO DA FILA
		adj = VerticesAdjacentes(mat, u); // ADJACENTES AO VERTICE ATUAL
		for(i = 0; i < mat->nVertices; i++)
		{
			// SE HOUVER ARESTA ENTRE u E i
			if(adj[i] == 1)
			{
				//  SE i AINDA NAO FOI VISITADO
				if(color[i] == WHITE)
				{	
					// VISITO i
					color[i] = GRAY;
					distancia[i] = distancia[u] + 1; // A DISTANCIA PARA ELE É A ATÉ u +1
					predecessor[i] = u; // CHEGUEI EM i ATRAVÉS DE u

					InserirFila(f, i); // INSIRO i NA FILA
				}
			
			}

		}
		RemoverFila(f);	// REMOVO u DA FILA
			
		color[u] = BLACK; // TODOS OS VÉRTICES ADJACENTES A u JA FORAM VISITADOS
	}
	// IMPRIMO O CAMINHO DA ORIGEM ATÉ O DESTINO
	ImprimirCaminho(predecessor, origem, destino);
	printf("\n");

}



void visit(Mat_Adj* mat, int u, int* time, int* color, int* predecessor, int* Tvisitado, int* Tfinalizado)
{
	int i;
	// VISITO O VERTICE u
	// E MARCO O TEMPO DELE
	// AUMENTO 1 NA MARCAÇÃO DE TEMPO
	color[u] = GRAY;
	Tvisitado[u] = (*time);
	*time += 1;
	// PEGANDO OS ADJACENTES A u
	int* adj = VerticesAdjacentes(mat, u);
	for(i = 0; i < mat->nVertices; i++)
	{
		// SE HOUVER ARESTA ENTRE u E i, E i NÃO FOI VISITADO AINDA
		if(adj[i] == 1)
		{
			if(color[i] == WHITE)
			{
				// CHEGUEI A i ATRAVES DE u
				// VISITO i
				predecessor[i] = u;
				visit(mat, i, time, color, predecessor, Tvisitado, Tfinalizado);
			}
		}
	}
	// u É FINALIZADO
	// E SEU TEMPO DE FINALIZAÇÃO MARCADO
	// AUMENTO 1 NA MARCAÇÃO DE TEMPO, E ENCERRO ESSA CHAMADA DA FUNÇÃO
	color[u] = BLACK;
	Tfinalizado[u] = *time;
	*time += +1; 


}





void DFS(Mat_Adj* mat, int origem, int destino)
{
	// INICIALIZANDO OS VETORES

	int i = 0;

	// INICIALIZANDO TODO OS VETORES NECESSÁRIOS
	// CORES: WHITE PARA NÃO VISITADO
		//    GRAY PARA JÁ VISITADO
		//	  BLACK PARA QUANDO TODO OS VÉRTICES ADJACENTES JÁ FORAM VISITADOS
	// PREDECESSOR DE CADA VÉRTICE(ATRAVÉS DE QUAL VÉRTICE SE CHEGOU NO ATUAL)
	// Tfinalizado MARCA O TEMPO EM QUE O VÉRTICE FOI FINALIZADO
	// E Tvisitado MARCO O TEMPO DE QUANDO O VÉRTICE FOI VISITADO
	int* color = (int*) malloc(sizeof(int)*mat->nVertices);
	int* predecessor = (int*) malloc(sizeof(int)*mat->nVertices);
	int* Tfinalizado = (int*) malloc(sizeof(int)*mat->nVertices);
	int* Tvisitado = (int*) malloc(sizeof(int)*mat->nVertices);

	// SETANDO TODOS OS VÉRTICE PARA NÃO VISITADOS E SEM PREDECESSORES
	for(i = 0; i < mat->nVertices; i++)
	{
		color[i] = WHITE;
		predecessor[i] = -1;
	}
	// VARIÁVEL DE TEMPO
	int time;
	time = 0;
	// VISITO A ORIGEM
	visit(mat, origem, &time, color, predecessor, Tvisitado, Tfinalizado);
	
	// IMPRIMO O CAMINHO ENCONTRADO
	ImprimirCaminho(predecessor, origem, destino);

}
