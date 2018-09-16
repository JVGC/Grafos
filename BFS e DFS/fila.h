#ifndef _FILA_H_
#define _FILA_H_

// PONTEIRO PARA O PROXIMO E INFORMAÇÃO DO NO
typedef struct no
{
	struct no* prox;
	int info;

}no_t;

// FILA COM PONTEIRO PARA O INICIO E PARA O FIM
typedef struct fila
{
	no_t* inicio;
	no_t* fim;
}fila_t;

fila_t* CriarFila(); // INICIALIZA A FILA
void InserirFila(fila_t* f, int x); // INSERE x NA FILA f
void RemoverFila(fila_t* f); // REMOVE O PRIMEIRO ELEMENTO DA FILA f
void DestruirFila(fila_t* f); // DESTROI E DESALOCA A FILA f



#endif