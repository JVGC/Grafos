#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include <limits.h>


// PROCURA A ARESTA DE MENOR VALOR NA MATRIZ E COLOCA ELA NA MATRIZ
void ProcurarMenor(Mat_Adj* adj){
	int i, j;

	aresta aux;
	aux.peso = INT_MAX;

	for(i = 0; i < adj->nVertices; i++)
		for(j = 0; j < adj->nVertices; j++){
			if(adj->vertices[i][j] < aux.peso && adj->vertices[i][j] != -1){	
				aux.peso = adj->vertices[i][j];
				aux.v1 = i;
				aux.v2 = j;
			}
		}

	adj->menor = aux;	

}


Mat_Adj* CriarMatriz(int nVertices){
	int i, j;

	// ALOCANDO A MEMORIA NECESSARIA E INICIALIZANDO AS VARIAIS
	Mat_Adj* a = (Mat_Adj*) malloc(sizeof(Mat_Adj));
	
	a->vertices = (int**) malloc(sizeof(int*)*nVertices);
	for(i = 0; i < nVertices; i++)
		a->vertices[i] =(int*) malloc(sizeof(int)*nVertices);

	// INICIANDO A MATRIZ COM PESO DOS VERTICES IGUAL A -1
	for(i = 0; i < nVertices; i++)
		for(j = 0; j < nVertices; j++)
			a->vertices[i][j] = -1;
	a->nVertices = nVertices;
	a->menor.v1 = -1;
	a->menor.v2 = -1;
	a->menor.peso = -1;

	return a;

}

void DestroiMatriz(Mat_Adj* adj){
	int i;

	for(i = 0; i < adj->nVertices; i++)
		free(adj->vertices[i]);
	free(adj->vertices);

	free(adj);


}

void AdicionarAresta(Mat_Adj* adj, int v1, int v2, int peso){
	adj->vertices[v1][v2] = peso;
	
	if(adj->direcionado == '0') // GRAFO NAO DIRECIONADO
		adj->vertices[v2][v1] = peso;
	if(adj->menor.v1 == -1){ //PRIMEIRA ARESTA SENDO ADICIONADA
		adj->menor.v1 = v1;
		adj->menor.v2 = v2;
		adj->menor.peso = peso;
	}else if(adj->menor.peso >= peso){ // CASO A ARESTA NOVA SEJA DE PESO MENOR QUE A MENOR DO GRAFO
		adj->menor.v1 = v1;
		adj->menor.v2 = v2;
		adj->menor.peso = peso;
	}
}

void RemoverAresta(Mat_Adj* adj, int v1, int v2){	
	adj->vertices[v1][v2] = -1;
	
	if(adj->direcionado == '0') // GRAFO NAO DIRECIONADO
		adj->vertices[v2][v1] = -1;

	//VERIFICAR SE A ARESTA REMOVIDO ERA O DE MENOR PESO
	// SE FOR, PROCURA A NOVA ARESTA DE MENOR PESO DO GRAFO
	if((v1 == adj->menor.v1) && (v2 == adj->menor.v2)){
		ProcurarMenor(adj);
	}else if((v2 == adj->menor.v1) && (v1 == adj->menor.v2)){
		ProcurarMenor(adj);
	}
}

void ImprimirGrafo(Mat_Adj* adj){
	int i, j;

	for(i = 0; i < adj->nVertices; i++){
		for(j = 0; j < adj->nVertices; j++){
			if(adj->vertices[i][j] == -1)
				printf(". ");
			else
				printf("%d ", adj->vertices[i][j]);
		}
		printf("\n");
	}
}


void MenorAresta(Mat_Adj* adj){
	// IMPRIME EM ORDEM CRESCENTE DE VERTICES
	if(adj->menor.v1 < adj->menor.v2){	
		printf("%d ", adj->menor.v1);
		printf("%d", adj->menor.v2);
		printf("\n");
	}else{
		printf("%d ", adj->menor.v2);
		printf("%d", adj->menor.v1);
		printf("\n");
	}
}


void VerticesAdjacentes(Mat_Adj* adj, int vertice){
	int i;
	for(i = 0; i < adj->nVertices; i++){
		if(adj->vertices[vertice][i] != -1)
			printf("%d ", i);
	}
	printf("\n");
}

void ImprimirGrafoTransposto(Mat_Adj* adj){
	int i, j;

	// CRIANDO UMA MATRIZ AUXILIAR PARA TRANSPOR A MATRIZ INICIAL
	Mat_Adj* t = CriarMatriz(adj->nVertices);
	for(i = 0; i < t->nVertices; i++){
		for(j = 0; j < t->nVertices; j++){
			if(adj->vertices[i][j] != -1)
				AdicionarAresta(t, j, i, adj->vertices[i][j]);
		}
	}
	// IMPRIME A MATRIZ TRANSPOSTA
	ImprimirGrafo(t);
	// DESALOCA A MATRIZ TRANSPOSTA
	DestroiMatriz(t);
}