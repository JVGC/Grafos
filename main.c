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
	}

	fclose(arq);

	UC Control_Unit;

	Control_Unit.estado_atual.s0 = 0;
	Control_Unit.estado_atual.s1 = 0;
	Control_Unit.estado_atual.s2 = 0;
	Control_Unit.estado_atual.s3 = 0;

	int cod_inst;


	seta_sinal_controle(&Control_Unit, cod_inst);
	
		
		// MUX DO PC
		if(Control_Unit.IorD == 0){
			if(Control_Unit.MemRead == 1){
				// li a memoria
				MAR = PC;
				MBR = RAM[MAR];
				if(Control_Unit.IRWrite == 1){
					IR = MBR;				}
			}
				
		}else{
			if(Control_Unit.MemRead == 1){ // ESTOU NUMA LW

			}
		}

		// MUX DO PARAMETRO A DA ULA
		if(Control_Unit.ALUSrcA == 0){
			// Parametro 1 da ULA recebe PC
		}else{
			//parametro 1 da ULA RECEBE registrador A
		}
		

		// MUX DO PARAMETRO B DA ULA
		if(Control_Unit.ALUSrcB0 == 0 && Control_Unit.ALUSrcB1 == 0){
			//parametro 2 da ULA recebe registrador B

		}else if(Control_Unit.ALUSrcB0 == 1 && Control_Unit.ALUSrcB1 == 0){
			//parametro 2 da ula recebe 4
		}else if(Control_Unit.ALUSrcB0 == 0 && Control_Unit.ALUSrcB1 == 1){
			//parametro 2 da ula recebe valor imediato da instrucao
		}else{
			// parametro 2 da ULA recebe valor imediato shiftado 2 bits
		}

		// MUX DO PC SOURCE

		if(Control_Unit.PCSource0 == 0 && Control_Unit.PCSource1 == 0){
			// PC RECEBE ALU RESULT

		}else if(Control_Unit.PCSource0 == 1 && Control_Unit.PCSource1 == 0){
			// PC RECEBE ALUOut
		}else if(Control_Unit.PCSource0 == 0 && Control_Unit.PCSource1 == 1){
			//PC recebe endereço da jump
		}else{
			// PC RECEBE O REGISTRADOR A 
		}

		// MUX DO REGDst

		if(Control_Unit.RegDst0 == 0 && Control_Unit.RegDst1 == 0){
			// write register recebe os bits de 20 a 16 da instrucao


		}else if(Control_Unit.RegDst0 == 1 && Control_Unit.RegDst1 == 0){
			// write register recebe os bits de 15 a 11 da instrucao

		}else if(Control_Unit.RegDst0 == 0 && Control_Unit.RegDst1 == 1){
			// write register recebe $ra(31)
		}


		// MUX DO MemtoReg


		if(Control_Unit.MemtoReg0 == 0 && Control_Unit.MemtoReg1 == 0){
			// write data ALUout


		}else if(Control_Unit.MemtoReg0 == 1 && Control_Unit.MemtoReg1 == 0){
			// write data recebe MBR( vai ser usada em casa de SW)

		}else if(Control_Unit.MemtoReg0 == 0 && Control_Unit.MemtoReg1 == 1){
			// write data recebe PC (em jal ou jalr)
		}


		// MUX DO BNE

		if(Control_Unit.BNE == 0){
			//BNE RECEBE SINAL zero DA ULA

		}else{
			//BNE RECEBE NOT(SINAL zero) DA ULA
		}

	




		

		


		// ciclo 2
		for (int i = 0; i < tamanho_arq; ++i){
			decifra_instrucao(IR);	
		}
	
	


	free(RAM);

	return 0;













}