#ifndef _BUSCA_H_
#define _BUSCA_H_

#include "matriz.h"

void BFS(Mat_Adj* mat, int origem, int destino); // BUSCA EM LARGURA
void DFS(Mat_Adj* mat); // BUSCA EM PROFUNDIDADE
void ImprimirCaminho(int* predecessor, int origem, int destino); // IMPRIME O CAMINHO DA ORIGEM AO DESTINO




#endif