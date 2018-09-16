#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct lista lista_t;


typedef struct no{
	struct no* prox;
	int vertice;
	int peso;
}no_t;


struct lista{
	no_t* inicio;
};

lista_t* cria_lista(); // CRIA A LISTA
void insere(lista_t* l, int v, int peso); // INSERE UM ELEMENTO NA LISTA
void retira(lista_t* l, int v); // RETIRA UM ELEMENTO DA LISTA
void libera_lista(lista_t* l); // DESALOCA A MEMORIA DA LISTA

void imprimir_lista(lista_t* l); // IMPRIME A LISTA



#endif