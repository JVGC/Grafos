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

	int Registradores[32];

	UC Control_Unit;


	Control_Unit.estado_atual.s0 = 0;
	Control_Unit.estado_atual.s1 = 0;
	Control_Unit.estado_atual.s2 = 0;
	Control_Unit.estado_atual.s3 = 0;

	ULA Arithmetic_Unit;

	int cod_inst;
	int IR, MBR, MAR;
	int A, B;
	short int immediate;
	int ALUout;
	int ENDjump;
	int PCaux;
	


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
				MAR = ALUout;
				MBR = RAM[MAR];
			}else if(Control_Unit.MemWrite == 1){ // estou numa sw
				MAR = ALUout
				RAM[MAR] = B;
			}
		}

		//printf("IR = %d\n", IR);
		//exit(0);



		A = IR >> 20;
		A = (A & 31);//11111
		B = IR >> 15;
		B = (B & 31);

		immediate = ((IR) << 16) >> 16;

		
		PCaux = (PC >> 27) << 27;
		ENDjump = ((IR << 4) >> 4) & PCaux;

		printf("im = %d\n", immediate);
		// MUX DO PARAMETRO A DA ULA
		if(Control_Unit.ALUSrcA == 0){
			 Arithmetic_Unit.param1 = PC;
		}else{
			Arithmetic_Unit.param1 =  Registradores[A];
		}
		

		// MUX DO PARAMETRO B DA ULA
		if(Control_Unit.ALUSrcB0 == 0 && Control_Unit.ALUSrcB1 == 0){
			//parametro 2 da ULA recebe registrador B
			Arithmetic_Unit.param2 =  Registradores[B];

		}else if(Control_Unit.ALUSrcB0 == 1 && Control_Unit.ALUSrcB1 == 0){
			//parametro 2 da ula recebe 4
			Arithmetic_Unit.param2 = 1; //tamanho de uma word
		}else if(Control_Unit.ALUSrcB0 == 0 && Control_Unit.ALUSrcB1 == 1){
			//parametro 2 da ula recebe valor imediato da instrucao
			printf("ola\n");
			Arithmetic_Unit.param2  = (int)((immediate) << 16) >> 16; 
		}else{
			// parametro 2 da ULA recebe valor imediato shiftado 2 bits
			Arithmetic_Unit.param2  = (int)((immediate) << 16) >> 14; 

		}

		//printf("Param1 = %d\n", Arithmetic_Unit.param1);
		//printf("Param2 = %d\n", Arithmetic_Unit.param2);

		//exit(0);

		// MUX DO PC SOURCE

		if(Control_Unit.PCSource0 == 0 && Control_Unit.PCSource1 == 0){
			// PC RECEBE ALU RESULT
			if(Control_Unit.PCWrite == 1)
				PC = Arithmetic_Unit.result;

		}else if(Control_Unit.PCSource0 == 1 && Control_Unit.PCSource1 == 0){
			// PC RECEBE ALUOut
			if(PCWrite == 1)
				PC += ALUout;
		}else if(Control_Unit.PCSource0 == 0 && Control_Unit.PCSource1 == 1){
			//PC recebe endereço da jump
			
			if(PCWrite == 1)
				PC = ENDjump;
		}else{
			// PC RECEBE O REGISTRADOR A 
			if(Control_Unit.PCWrite == 1){
				PC = Registradores[A];
			}else{
				//verificar os BNE da vida
			}

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