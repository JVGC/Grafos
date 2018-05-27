#ifndef _UC_H_
#define _UC_H_


#define FALSE 0
#define TRUE 1

#define NOT ! 
#define AND && 
#define OR || 

typedef struct state{

	char s0;
	char s1;
	char s2;
	char s3;

}State;


typedef struct uc{

	char RegDst0;
	char RegDst1;
	char RegWrite;
	char ALUSrcA;
	char ALUSrcB0;
	char ALUSrcB1;
	char ALUOp0;
	char ALUOp1;
	char PCSource0;
	char PCSource1;
	char PCWriteCond;
	char PCWrite;
	char IorD;
	char MemRead;
	char MemWrite;
	char BNE;
	char IRWrite;
	char MemtoReg0;
	char MemtoReg1;

	State estado_atual;
	State proximo_estado;


}UC;


void decifra_instrucao(int inst);

void seta_sinal_controle(UC* u, int cod_inst);

void printa_sinal(UC Control_Unit);





#endif