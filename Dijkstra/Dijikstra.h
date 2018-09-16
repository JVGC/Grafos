#ifndef _DIJIKSTRA_H_
#define _DIJIKSTRA_H_

#include "matriz.h"

int* Dijikstra(Mat_Adj* G, int origem, int destino);
void ImprimirCaminho(int* predecessor, int origem, int destino);
#endif