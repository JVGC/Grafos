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

	unsigned int* RAM = (unsigned int*) malloc(sizeof(unsigned int)*tamanho_arq);
	
	for(i = 0; !feof(arq); i++){

		fscanf(arq,"%u", &RAM[i]);
		printf("RAM[%d] = %u\n",i, RAM[i]);
	}

	fclose(arq);

	int Registradores[32];

	for(i = 0; i < 32; i++)
		Registradores[i] = 0;

	UC Control_Unit;


	Control_Unit.estado_atual.s0 = 0;
	Control_Unit.estado_atual.s1 = 0;
	Control_Unit.estado_atual.s2 = 0;
	Control_Unit.estado_atual.s3 = 0;
	

	ULA Arithmetic_Unit;

	int cod_inst = 0;
	int IR;
	int MBR, MAR;
	int A, B;
	short int immediate;
	int ALUout;
	int ENDjump;
	int PCaux;
	int write_register;
	int write_data;
	int BNE;
	int cont = 0;

	while(1){


		seta_sinal_controle(&Control_Unit, cod_inst);
	
		if(Control_Unit.estado_atual.s0 == 0 && Control_Unit.estado_atual.s1 == 0 && Control_Unit.estado_atual.s2 == 0 && Control_Unit.estado_atual.s3 == 0)
			Imprime_registradores(Registradores);

		printf("PC = %d\n\n", PC);

		// MUX DO PC
		if(Control_Unit.IorD == 0){
			if(Control_Unit.MemRead == 1){
				// li a memoria
				MAR = PC;
				MBR = RAM[MAR];
				if(Control_Unit.IRWrite == 1){
					//printf("oi\n");	
					IR = MBR;
				}
			}
				
		}else{
			if(Control_Unit.MemRead == 1){
				MAR = ALUout;
				MBR = RAM[MAR];
			}else if(Control_Unit.MemWrite == 1){
				MAR = ALUout;
				RAM[MAR] = B;
			}
		}



		cod_inst = decifra_instrucao(IR);


		if(cod_inst == -1){
			printf("inst invalida \n");
			return 0;
		}

		A = IR >> 21;
		
		A = (A & 31); //11111
		
		B = IR >> 16;
		


		B = (B & 31);
		
		printf("A = %d\n", A);
		printf("B = %d\n", B);
		
		
		immediate = ((IR) << 16) >> 16;

		
		PCaux = (PC >> 27) << 27;
		ENDjump = (((IR << 6) >> 4) | PCaux) / 4;		

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
			Arithmetic_Unit.param2  = (int)((immediate) << 16) >> 16; 
		}else{
			// parametro 2 da ULA recebe valor imediato shiftado 2 bits
			Arithmetic_Unit.param2  = (int)(((immediate) << 16) >> 14) / 4; 
			//printf("Param2 = %d\n", Arithmetic_Unit.param2 );
			//printf("BEQ\n");

		}


		// ULA
		if(Control_Unit.ALUOp0 == 0 && Control_Unit.ALUOp1 == 0){ // operacao de soma
			Arithmetic_Unit.op = 0;
		}else if(Control_Unit.ALUOp0 == 1 && Control_Unit.ALUOp1 == 0){ // operacao de subtracao
			Arithmetic_Unit.op = 1;
			//printf("BEQ\n");
		}else if(Control_Unit.ALUOp0 == 1 && Control_Unit.ALUOp1 == 1){ // operacao de AND
			Arithmetic_Unit.op = 3;
		}else{ // chama a unidade de controle da ULA para decifrar a operacao
			Arithmetic_Unit.op = decifra_operacao(IR); 
		}

		if(Arithmetic_Unit.op == 0){
			Arithmetic_Unit.result = Arithmetic_Unit.param1 + Arithmetic_Unit.param2;
			printf("ULA OP = %d\n", Arithmetic_Unit.op);
			printf("Arithmetic_Unit.result = %d\n", Arithmetic_Unit.result );
		}else if(Arithmetic_Unit.op == 1){
			Arithmetic_Unit.result = Arithmetic_Unit.param1 - Arithmetic_Unit.param2;
			//printf("Arithmetic_Unit.result = %d\n",Arithmetic_Unit.result );
			if(Arithmetic_Unit.result == 0){
				//printf("oiiii\n");
				Arithmetic_Unit.zero = 1;
			}else{
				Arithmetic_Unit.zero = 0;
			}
		}else if(Arithmetic_Unit.op == 3){
			Arithmetic_Unit.result = Arithmetic_Unit.param1 & Arithmetic_Unit.param2;
		}else if(Arithmetic_Unit.op == 4){
			Arithmetic_Unit.result = Arithmetic_Unit.param1 | Arithmetic_Unit.param2;
		}else if(Arithmetic_Unit.op == 5){
			Arithmetic_Unit.result = Arithmetic_Unit.param1 - Arithmetic_Unit.param2;
			if(Arithmetic_Unit.result < 0){
				Arithmetic_Unit.zero = 1;
				Arithmetic_Unit.result = 1;
			}else{
				Arithmetic_Unit.zero = 0;
			}
		}





		

		// MUX DO REGDst

		if(Control_Unit.RegDst0 == 0 && Control_Unit.RegDst1 == 0){
			// write register recebe os bits de 20 a 16 da instrucao
			//printf("oi\n");
			write_register = B;

		}else if(Control_Unit.RegDst0 == 1 && Control_Unit.RegDst1 == 0){
			// write register recebe os bits de 15 a 11 da instrucao
			write_register = (IR >> 11) & 31;

		}else if(Control_Unit.RegDst0 == 0 && Control_Unit.RegDst1 == 1){
			// write register recebe $ra(31)
			write_register = 31;
			printf("ola\n");

		}


		// MUX DO MemtoReg


		if(Control_Unit.MemtoReg0 == 0 && Control_Unit.MemtoReg1 == 0){
			// write data ALUout
			write_data = ALUout;
			printf("ALUout = %d\n", ALUout);

		}else if(Control_Unit.MemtoReg0 == 1 && Control_Unit.MemtoReg1 == 0){
			// write data recebe MBR( vai ser usada em casa de SW)
			write_data = MBR;

		}else if(Control_Unit.MemtoReg0 == 0 && Control_Unit.MemtoReg1 == 1){
			// write data recebe PC (em jal ou jalr)
			//printf("ola2\n");
			write_data = PC;
		}

		if(Control_Unit.RegWrite == 1){
			//printf("ola2\n");
			//printf("write_register = %d\n", write_register);
				Registradores[write_register] = write_data;
		}

		// MUX DO BNE

		if(Control_Unit.BNE == 0){
			//BNE RECEBE SINAL zero DA ULA
			BNE = Arithmetic_Unit.zero;
			//printf("BNE = %d\n", BNE);
			//printf("BEQ\n");

		}else{
			//BNE RECEBE NOT(SINAL zero) DA ULA
			//printf("BNE\n");
			//printf("BNE = %d\n", BNE);
			BNE = NOT(Arithmetic_Unit.zero);
			//printf("!BNE = %d\n", BNE);
			
		}

		// MUX DO PC SOURCE

		if(Control_Unit.PCSource0 == 0 && Control_Unit.PCSource1 == 0){
			// PC RECEBE ALU RESULT
			if(Control_Unit.PCWrite == 1)
				PC = Arithmetic_Unit.result;
			else{
				//verificar os BNE da vida
				if((BNE & Control_Unit.PCWriteCond) == 1){
					PC = Arithmetic_Unit.result;
				}
			}
		}else if(Control_Unit.PCSource0 == 1 && Control_Unit.PCSource1 == 0){
			// PC RECEBE ALUOut

			//printf("PCWrite =  %d\n", Control_Unit.PCWrite);
			if(Control_Unit.PCWrite == 1){
				//printf("OLA345\n");
				PC = ALUout;
			}else{
				//printf("BNE = %d\n", BNE);
				//verificar os BNE da vida
				if((BNE & Control_Unit.PCWriteCond) == 1){
					//printf("OLA345\n");
					PC = ALUout;
				}
			}
		}else if(Control_Unit.PCSource0 == 0 && Control_Unit.PCSource1 == 1){
			//PC recebe endereço da jump
			//printf("ASHSAUHSUAHASUHASUHSAUHASUHASUASUHAS\n");
			
			if(Control_Unit.PCWrite == 1){
				//printf("jump =%d\n", ENDjump);
				PC = ENDjump;
			}else{
				//verificar os BNE da vida
				if((BNE & Control_Unit.PCWriteCond) == 1){
					PC = ENDjump;
				}
			}
		}else{

			// PC RECEBE O REGISTRADOR A 
			if(Control_Unit.PCWrite == 1){
				PC = Registradores[A] / 4; //DIVIDO POR 4 POIS O VALOR GUARDADO NO REGISTRADO ESTÁ A BYTE E NÃO A PALAVRA

			}else{
				//verificar os BNE da vida
				if((BNE & Control_Unit.PCWriteCond) == 1){
					PC = Registradores[A];
				}
			}

		}

		

		Control_Unit.estado_atual = Control_Unit.proximo_estado;
		cont++;

		ALUout = Arithmetic_Unit.result;

		//printf("ra = %d\n", Registradores[31]);

	}



	free(RAM);

	return 0;













}