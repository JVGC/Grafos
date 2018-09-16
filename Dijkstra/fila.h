#ifndef _FILA_H_
#define _FILA_H_



// PONTEIRO PARA O PROXIMO E INFORMAÇÃO DO NO
typedef struct no
{
	struct no* prox;
	int ID;
	int peso;

}no_t;

// FILA COM PONTEIRO PARA O INICIO E PARA O FIM
typedef struct fila
{
	no_t* inicio;
	no_t* fim;
}fila_t;

fila_t* CriarFila(); // INICIALIZA A FILA
void InserirFila(fila_t* f, int ID, int peso);
void RemoverFila(fila_t* f); // REMOVE O PRIMEIRO ELEMENTO DA FILA f
void DestruirFila(fila_t* f); // DESTROI E DESALOCA A FILA f
void ImprimirFila(fila_t* f);
void atualizar(fila_t* f, int ID, int peso);
int Custo(fila_t* f, int ID);
no_t Front(fila_t* f);



#endif