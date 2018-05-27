#include <stdio.h>
#include <stdlib.h>
#include "UC.h"




void decifra_instrucao(int inst){

	//printf("%d\n", inst);

	int cod_inst = inst >> 26;

	printf("%d\n",cod_inst);

	return ;
}

void seta_sinal_controle(UC* u, int cod_inst){


	int S0 = u->estado_atual.s0;
	int S1 = u->estado_atual.s1;
	int S2 = u->estado_atual.s2;
	int S3 = u->estado_atual.s3;

	printf("s0 = %d\n", S0);
	printf("s1 = %d\n", S1);
	printf("s2 = %d\n", S2);
	printf("s3 = %d\n", S3);

	u->IorD = S0;
	u->MemtoReg0 = NOT(S3) AND NOT(S1);
	u->MemtoReg1 = S3 AND S2;
	u->IRWrite = NOT(S3) AND NOT(S2) AND NOT(S1) AND NOT(S0);
	u->PCSource1 = S0;
	u->PCSource0 = S1 OR ((S3) AND NOT(S0));
	u->ALUOp0 = S3;
	u->ALUOp1 = (NOT(S3) AND S2) OR (S3 AND S1);
	u->ALUSrcB0 = NOT(S3) AND NOT(S1);
	u->ALUSrcB1 = S0 OR (NOT(S2) AND S1);
	u->ALUSrcA = S1 OR S3;
	u->RegDst0 = NOT(S3);
	u->RegDst1 = NOT(S1);
	u->BNE = S2;
	u->PCWriteCond = S3 AND NOT(S1) AND NOT(S0);
	u->PCWrite = (S3 AND NOT(S1)) OR (NOT(S2) AND NOT(S1) AND NOT(S0)) OR (S3 AND S2 AND S0);
	u->MemWrite = NOT(S3) AND S2 AND NOT(S1) AND S0;
	u->MemRead = (NOT(S3) AND NOT(S2) AND NOT(S1) AND NOT(S0)) OR (NOT(S3) AND NOT(S2) AND S1 AND S0);
	u->RegWrite = (NOT(S3) AND S2 AND NOT(S1) AND NOT(S0)) OR (NOT(S3) AND S2 AND S1 AND S0) OR (S3 AND NOT(S2) AND S1 AND S0) OR (S3 AND S2 AND NOT(S1) AND S0);


}

void printa_sinal(UC Control_Unit){

	printf("MemWrite = %d\n", Control_Unit.MemWrite);
	printf("RegWrite = %d\n", Control_Unit.RegWrite);
	printf("MemRead = %d\n", Control_Unit.MemRead);
	printf("ALUSrcA = %d\n", Control_Unit.ALUSrcA);
	printf("IorD = %d\n", Control_Unit.IorD);
	printf("IRWrite = %d\n", Control_Unit.IRWrite);
	printf("ALUSrcB0 = %d\n", Control_Unit.ALUSrcB0);
	printf("ALUSrcB1 = %d\n", Control_Unit.ALUSrcB1);
	printf("ALUOp0 = %d\n", Control_Unit.ALUOp0);
	printf("ALUOp1 = %d\n", Control_Unit.ALUOp1);
	printf("PCWrite = %d\n", Control_Unit.PCWrite);
	printf("PCSource0 = %d\n", Control_Unit.PCSource0);
	printf("PCSource1 = %d\n", Control_Unit.PCSource1);
	printf("MemtoReg0 = %d\n", Control_Unit.MemtoReg0);
	printf("MemtoReg1 = %d\n", Control_Unit.MemtoReg1);
	printf("RegDst0 = %d\n", Control_Unit.RegDst0);
	printf("RegDst1 = %d\n", Control_Unit.RegDst1);
	printf("PCWriteCond = %d\n", Control_Unit.PCWriteCond);
	printf("BNE = %d\n", Control_Unit.BNE);

}
