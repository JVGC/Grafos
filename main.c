#include <stdio.h>
#include <stdlib.h>
#include "UC.h"



int main()
{

	int i;
	int PC = 0;

	char nome_arq[15];
	scanf("%s", nome_arq);


	FILE* arq = fopen(nome_arq, "rb");

	fseek(arq, 0, SEEK_END);


	long int tamanho_arq = ftell(arq)/4;


	fseek(arq, 0, SEEK_SET);

	int* RAM = (int*) malloc(sizeof(int)*tamanho_arq);
	
	for(i = 0; !feof(arq); i++){

		fscanf(arq,"%d", &RAM[i]);
		//printf("%d\n", RAM[i]);
	}

	UC Control_Unit;

	Control_Unit.estado_atual.s0 = 0;
	Control_Unit.estado_atual.s1 = 0;
	Control_Unit.estado_atual.s2 = 0;
	Control_Unit.estado_atual.s3 = 1;

	int cod_inst = 0;

	seta_sinal_controle(&Control_Unit, cod_inst);

	printa_sinal(Control_Unit);



	exit(0);


	//CICLO 1 - CICLO DE BUSCA

	int IR,MBR,MAR;

	MAR = PC;
	MBR = RAM[MAR];


	// ciclo 2
	for (int i = 0; i < tamanho_arq; ++i){
		decifra_instrucao(RAM[PC++]);	
	}
	
	fclose(arq);


	free(RAM);

	return 0;













}