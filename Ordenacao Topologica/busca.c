#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
#include "fila.h"
#include "pilha.h"

#define BLACK 1
#define GRAY 2
#define WHITE 0


void visit(Mat_Adj* mat, pilha_t* L, int u, int* time, int* color, int* predecessor, int* Tvisitado, int* Tfinalizado)
{
	int i;
	// VISITO O VERTICE u
	// E MARCO O TEMPO DELE
	// AUMENTO 1 NA MARCAÇÃO DE TEMPO

	color[u] = GRAY;
	Tvisitado[u] = (*time);
	*time += 1;
	// PEGANDO OS ADJACENTES A uInserirFila(L, u);
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
				visit(mat, L, i, time, color, predecessor, Tvisitado, Tfinalizado);
			}
		}
	}
	// u É FINALIZADO
	// E SEU TEMPO DE FINALIZAÇÃO MARCADO
	// AUMENTO 1 NA MARCAÇÃO DE TEMPO, E ENCERRO ESSA CHAMADA DA FUNÇÃO
	color[u] = BLACK;
	push(L, u);
	Tfinalizado[u] = *time;
	*time += +1; 


}





void DFS(Mat_Adj* mat)
{
	// INICIALIZANDO OS VETORES

	int i;
	int j;
	int cont = 0;


	fila_t* S = CriarFila();
	pilha_t* L = cria_pilha();

	for(i = 0; i < mat->nVertices; i++)
	{
		for(j = 0; j < mat->nVertices; j++)
		{
			if(mat->vertices[j][i] != -1)
				cont++;
		}
		if(cont == 0)
		{
			InserirFila(S, i);
			break;
		}
		cont = 0;
	}

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
	int origem = S->inicio->info;
	// VISITO A ORIGEM
	visit(mat, L, origem, &time, color, predecessor, Tvisitado, Tfinalizado);
	
	// IMPRIMO O CAMINHO ENCONTRADO

	ImprimirPilha(L);

}
