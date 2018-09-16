 #include <stdio.h>
#include <stdlib.h>
#include "fila.h"


// ALOCA MEMORIA E SETA OS PONTEIROS PARA NULL
fila_t* CriarFila()
{
	fila_t* f = (fila_t*) malloc(sizeof(fila_t));
	f->inicio = NULL;
	f->fim = NULL;

	return f;
}

void InserirFila(fila_t* f, int ID, int peso)
{
	// CRIA O NOVO NO
	no_t* p = (no_t*) malloc(sizeof(no_t));
	p->ID = ID;
	p->peso = peso;
	p->prox = NULL;
	
	if(f->inicio == NULL) // PRIMEIRO ELEMENTO NA FILA
	{
		f->inicio = p;
		f->fim = p;
	}else{ // JA TEM UM ELEMENTO NA FILA
		f->fim->prox = p;
		f->fim = p;
	}
}
// REMOVENDO O PRIMEIRO ELEMENTO DA FILA
no_t* RemoverFila(fila_t* f)
{
	no_t* aux = f->inicio;
	f->inicio = aux->prox;
	return aux;

}
// DESALOCANDO TODA A MEMÓRIA DA FILA
void DestruirFila(fila_t* f)
{
	no_t* p;
	while(f->inicio != NULL)
	{
		p = f->inicio;
		f->inicio = f->inicio->prox;
		free(p);
	}
	free(f);
}
void atualizar(fila_t* f, int ID, int peso)
{

	no_t* atual, *prox, *found;

	found = NULL;
	atual = f->inicio;
	prox = atual->prox;
	// se o ID do inicio for igual ao que estou procurando
	// apenas atualizo o peso, já que ele vai continuar sendo o menor da fila
	if(atual->ID == ID){
		atual->peso = peso;
		return ;
	}

	while(prox != NULL){
		if(prox->ID == ID){ // ACHEI O VÉRTICE
		
			//Guardo o vértice em found
			found = prox;
			found->peso = peso; //atualizo o peso
			// tiro o found da fila
			atual->prox = found->prox; // o proximo do anterior recebe o proximo do encontrado
			// reinicio os ponteiros pro começo da fila
			atual = f->inicio;
			prox = atual->prox;
			// se o peso do primeiro vertice ja for maior que o peso novo
			if(peso < atual->peso){
				//coloco o vértice no inicio
				f->inicio = found;
				found->prox = atual;
				return ;
			}else if(peso == atual->peso){
				//COMPARO POR ID
				// se o ID do inicio da fila ja for maior que o novo
				//então o novo no é adicionado no fim da fila
				if(atual->ID > ID){
					f->inicio = found;
					found->prox = atual;
					return ;
				}

				// senão, anda na fila enquanto o peso do prox for igual ao novo
				while(prox != NULL && peso == prox->peso){
					if(ID < prox->ID){ // se o ID de prox for maior que o novo, insiro o found antes de prox
						atual->prox = found;
						found->prox = prox;
						return;
					}
					atual= atual->prox;
					prox = prox->prox;
				}
				if(prox != NULL){ // se eu sai do while e o prox é diferente de NULL
					// então é pq o peso de prox é maior que o peso de found
					// entao insiro found antes de prox
					atual->prox = found;
					found->prox = prox;
				}else{ // se prox  == NULL, insiro found como o ultimo elemento da fila
					atual->prox = found;
					found->prox = NULL;
					f->fim= found;
				}
			}
			// senao, então enquanto não chegar no fim da fila
			// e o peso novo for maior que o peso dos nos da fila
			while(prox != NULL && (prox->peso < found->peso)){
				// ando na fila
				atual = atual->prox;
				prox = prox->prox;
			}
			// se eu sai do while e o prox é diferente de NULL
			// então o peso do no PROX é > ou = ao novo peso
			if(prox != NULL){ //ACHEI O LUGAR
			
				// se for menor, então insiro o found antes de prox
				if(found->peso < prox->peso){
					atual->prox = found;
					found->prox = prox;
					return ;
				}else{ // SE NAO É MENOR ENTÃO É IGUAL
					if(found->ID < prox->ID){ // comparo por ID
		
						atual->prox = found;
						found->prox = prox;
						return ;
					}else{// ando mais um nó pra frente
						if(prox == f->fim){
							f->fim = found;
						}
						atual = atual->prox;
						prox= prox->prox;
						// e atualizo os ponteiros
						atual->prox = found;
						found->prox = prox;
						return ;

					}
				}
			}else{// se sai do while porque o prox é igual de NULL, então atual = f->fim
				atual->prox = found;
				f->fim = found;
				found->prox = NULL;
				return ;
			}
		}else{ // CONTINUO ANDANDO NA FILA
			atual = atual->prox;
			prox = prox->prox;
		}
	}

	if(atual->ID == ID){ // O VERTICE É O ULTIMO ELEMENTO DA FILA
	
		//Guardo o vértice em found
			found = prox;
			found->peso = peso; //atualizo o peso
			// tiro o found da fila
			atual->prox = found->prox; // o proximo do anterior recebe o proximo do encontrado
			found->prox = NULL;
			// reinicio os ponteiros pro começo da fila
			atual = f->inicio;
			prox = atual->prox;
			// se o peso do primeiro vertice ja for maior que o peso novo
			if(peso < atual->peso){
				//coloco o vértice no inicio
				f->inicio = found;
				found->prox = atual;
				return ;
			}
			// senao, então enquanto não chegar no fim da fila
			// e o peso novo for maior que o peso dos nos da fila
			while(prox != NULL && (prox->peso < found->peso)){
				// ando na fila
				atual = atual->prox;
				prox = prox->prox;
			}
			// se eu sai do while e o prox é diferente de NULL
			// então o peso do no PROX é > ou = ao novo peso
			if(prox != NULL){ //ACHEI O LUGAR
		
				// se for menor, então insiro o found antes de prox
				if(found->peso < prox->peso){
					atual->prox = found;
					found->prox = prox;
					return ;
				}else{ // SE NAO É MENOR ENTÃO É IGUAL
					if(found->ID < prox->ID){ // comparo por ID
					
						atual->prox = found;
						found->prox = prox;
						return ;
					}else{// ando mais um nó pra frente
						if(prox == f->fim){
							f->fim = found;
						}
						atual = atual->prox;
						prox= prox->prox;
						// e atualizo os ponteiros
						atual->prox = found;
						found->prox = prox;
						return ;

					}
				}
			}else{// se sai do while porque o prox é igual de NULL, então atual = f->fim
				atual->prox = found;
				f->fim = found;
				found->prox = NULL;
				return ;
			}
	}
}
int Custo(fila_t* f, int ID)
{
	no_t* atual;

	atual = f->inicio;

	while(atual != NULL)
	{
		if(atual->ID == ID)
			return atual->peso;
		atual = atual->prox;
	}
	return 0;

}

void ImprimirFila(fila_t* f){
	no_t* aux;
	aux = f->inicio;
	printf("FILA:");
	while(aux != NULL)
	{
		printf("ID = %d, Peso = %d;", aux->ID, aux->peso);
		aux = aux->prox;
	}
	printf("\n");


}