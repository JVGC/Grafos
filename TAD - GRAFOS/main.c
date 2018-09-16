#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matriz.h"
#include "listaADJ.h"


int main(){
	char direcionado; // VER SE O GRAFO É DIFERECIONADO OU NAO
	char tipo; // MATRIZ OU LISTA
	char aux;
	int i, j;


	int vertices;
	int arestas;

	int linha, coluna, peso;

	scanf("%c",&direcionado); //DIRECIONADO OU NAO
	getchar(); // TIRAR O ESPAÇO
	scanf("%c",&tipo); // TIPO DE REPRESENTACAO

	scanf("%d", &vertices);// nVertices
	scanf("%d", &arestas); // nArestas
	getchar();
	
	// SE O GRAFO FOR SER REPRESENTADO POR UMA MATRIZ DE ADJACENCIA
	if(tipo == 'M'){
		//CRIAR A MATRIZ
		Mat_Adj* mat = CriarMatriz(vertices);
	
		if(direcionado == 'D')
			mat->direcionado = '1';
		else
			mat->direcionado = '0';
		
		// LER A MATRIZ E ADICIONA AS ARESTAS
		for(i = 0; i < arestas; i++){
			scanf("%d", &linha);
			scanf("%d", &coluna);
			scanf("%d", &peso);
			AdicionarAresta(mat, linha, coluna, peso);
			
		}
		getchar();
		// OPERACOES 
		while(!feof(stdin)){
			
			if(aux == 'I'){ // IMPRESSAO
				scanf("%c", &aux);
				if(aux == 'G'){ //IMPRESSAO NORMAL DO GRAFO
					ImprimirGrafo(mat);
					getchar();
				}else if(aux == 'T'){ //IMPRESSAO TRANSPOSTA
					// SO VALE PARA GRAFOS DIRECIONADOS
					if(direcionado == 'D'){ //IMPRIME O TRANSPOSTO
						ImprimirGrafoTransposto(mat);
					}else
						continue;

				}
			}else if(aux == 'V'){ // IMPRIMIR VERTICES ADJACENTES
				getchar();
				getchar();
				scanf("%d", &vertices); // VERTICE QUE TERA SUAS ARESTAS IMPRESSAS
				VerticesAdjacentes(mat, vertices);
			}else if(aux == 'A'){ // ADICIONAR ARESTA
				getchar();
				scanf("%d %d %d", &linha, &coluna, &peso);
				AdicionarAresta(mat, linha, coluna, peso);

			}else if(aux == 'R'){ // REMOVER ARESTA
				getchar();
				scanf("%d", &linha);
				scanf("%d", &coluna);

				RemoverAresta(mat, linha, coluna);
			}else if(aux == 'M'){ // IMPRIME ARESTA DE MENOR PESO
				getchar();
				MenorAresta(mat);
				
			}
			scanf("%c", &aux);
			if(aux == EOF)
					break;

		}
		// DESALOCA A MATRIZ
		DestroiMatriz(mat);

		return 0;

	}else{// SE O GRAFO FOR SER REPRESENTADO POR UMA LISTA DE ADJACENCIA
		// CRIA A LISTA
		Lista_Adj* l = CriarLista(vertices);
		if(direcionado == 'D')
			l->direcionado = '1';
		else
			l->direcionado = '0';

		// LER A LISTA E ADICIONA AS ARESTAS
		for(i = 0; i < arestas; i++){
			scanf("%d", &linha);
			scanf("%d", &coluna);
			scanf("%d", &peso);
			AdicionarAresta2(l, linha, coluna, peso);
			
		}
		getchar();
		// OPERACOES
		while(!feof(stdin)){
			
			if(aux == 'I'){ // IMPRESSAO
				scanf("%c", &aux);
				if(aux == 'G'){ //IMPRESSAO NORMAL DO GRAFO
					ImprimirGrafo2(l);
					getchar();
				}else if(aux == 'T'){ //IMPRESSAO TRANSPOSTA
					// SO VALE PARA GRAFOS DIRECIONADOS
					if(direcionado == 'D'){ //IMPRIME O TRANSPOSTO
						ImprimirGrafoTransposto2(l);
					}else
						continue;

				}
			}else if(aux == 'V'){ // IMPRIMIR VERTICES ADJACENTES
				getchar();
				getchar();
				scanf("%d", &vertices); // VERTICE QUE TERA SUAS ARESTAS IMPRESSAS
				VerticesAdjacentes2(l, vertices);
			}else if(aux == 'A'){ // ADICIONAR ARESTA
				getchar();
				scanf("%d %d %d", &linha, &coluna, &peso);
				AdicionarAresta2(l, linha, coluna, peso);

			}else if(aux == 'R'){ // REMOVER ARESTA
				getchar();
				scanf("%d", &linha);
				scanf("%d", &coluna);

				RemoverAresta2(l, linha, coluna);
			}else if(aux == 'M'){ // IMPRIME ARESTA DE MENOR PESO
				getchar();
				MenorAresta2(l);
				
			}
			scanf("%c", &aux);
			if(aux == EOF)
					break;

		}
		// DESALOCA A LISTA
		DestroiLista(l);
		return 0;
	}
}