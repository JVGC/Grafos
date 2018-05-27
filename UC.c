#include <stdio.h>
#include <stdlib.h>
#include "UC.h"



int decifra_instrucao(int inst){


	int cod_inst = inst >> 26;

	printf("%d\n",cod_inst);

	return cod_inst;
}

void seta_sinal_controle(UC* u, int cod_inst){


	char S0 = u->estado_atual.s0;
	char S1 = u->estado_atual.s1;
	char S2 = u->estado_atual.s2;
	char S3 = u->estado_atual.s3;

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



	//cod_inst = inst >> 26;

	int OP0, OP1, OP2, OP3, OP4, OP5;

	OP5 = cod_inst >> 5;
	OP4 = (cod_inst & 16) >> 4;
	OP3 = (cod_inst & 8) >> 3;
	OP2 = (cod_inst & 4) >> 2;
	OP1 = (cod_inst & 2) >> 1;
	OP0 = (cod_inst & 1);

	u->proximo_estado.s0 = (NOT(S3) AND NOT(S2) AND NOT(S1) AND NOT(S0))
		OR (NOT(S3) AND S2 AND S1 AND NOT(S0))
		OR (S3 AND NOT(S2) AND S1 AND NOT(S0))
	 	OR (S3 AND S2 AND S1 AND NOT(S0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND NOT(OP0))
	 	OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND NOT(OP0))
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND OP5 AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND OP5 AND NOT(OP4) AND OP3 AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND NOT(OP5) AND NOT(OP4) AND OP3 AND NOT(OP2) AND NOT(OP1) AND NOT(OP0));

	printf("ns0 = %d\n", u->proximo_estado.s0);

	u->proximo_estado.s1 = (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND ( (OP5 AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0) OR (OP5 AND NOT(OP4) AND OP3 AND NOT(OP2) AND OP1 AND OP0) OR (NOT(OP5) AND NOT(OP4) AND OP3 AND NOT(OP2) AND NOT(OP1) AND NOT(OP0)) ) )
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND OP5 AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND NOT(OP1) AND NOT(OP0))
		OR (NOT(S3) AND S2 AND S1 AND NOT(S0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND OP3 AND OP2 AND NOT(OP1) AND NOT(OP0))
	 	OR (S3 AND NOT(S2) AND S1 AND NOT(S0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND OP0)
		OR (S3 AND S2 AND S1 AND NOT(S0));

		printf("ns1 = %d\n", u->proximo_estado.s1);

	u->proximo_estado.s2 = (NOT(S3) AND NOT(S2) AND S1 AND S0)
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND OP5 AND NOT(OP4) AND OP3 AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND NOT(OP1) AND NOT(OP0))
		OR (NOT(S3) AND S2 AND S1 AND NOT(S0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND OP2 AND NOT(OP1) AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND NOT(OP0))
		OR (S3 AND S2 AND S1 AND NOT(S0));

		printf("ns2 = %d\n", u->proximo_estado.s2);

	u->proximo_estado.s3 =(NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND OP2 AND NOT(OP1) AND NOT(OP0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND NOT(OP0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND OP3 AND OP2 AND NOT(OP1) AND NOT(OP0))
		OR (S3 AND NOT(S2) AND S1 AND NOT(S0))
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND OP2 AND NOT(OP1) AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND NOT(OP0))
		OR (S3 AND S2 AND S1 AND NOT(S0));

		printf("ns3 = %d\n", u->proximo_estado.s3);


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