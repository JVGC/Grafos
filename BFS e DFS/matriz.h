#ifndef _MATRIZ_H_
#define _MATRIZ_H_

typedef struct{
	int v1;
	int v2;
	int peso;

}aresta;

typedef struct _adj
{
	int** vertices; // A MATRIZ EM SI
	int nVertices; // NUMERO DE VERTICES
	char direcionado; // 1 SE O GRAFO EH DIRECIONADO, 0 SE NAO
	aresta menor; // ARESTA DE MENOR PESO
}Mat_Adj;

Mat_Adj* CriarMatriz(int nVertices); // CRIA A MATRIZ com nVertices x nVertices
void AdicionarAresta(Mat_Adj* adj, int v1, int v2, int peso); // Adiciona a aresta na matriz
void RemoverAresta(Mat_Adj* adj, int v1, int v2); // Retira a aresta da matriz
void ImprimirGrafo(Mat_Adj* adj); // Imprimi o Grafo
void MenorAresta(Mat_Adj* adj); // Imprime a Aresta de menor peso do Grafo
int* VerticesAdjacentes(Mat_Adj* adj, int vertice); // Imprime todos os vertices adjacentes de determinado vertice
void ImprimirGrafoTransposto(Mat_Adj* adj); // Imprime o Transposto do Grafo
void DestroiMatriz(Mat_Adj* adj); // DESALOCA A MATRIZ

#endif