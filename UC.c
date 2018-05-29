#include <stdio.h>
#include <stdlib.h>
#include "UC.h"



int decifra_instrucao(int inst){


	int cod_inst = inst >> 26;
	//printf("INST =  %d\n",inst);
	printf("COD_INST =  %d\n",cod_inst);

	if(cod_inst != 0 && cod_inst != 2 && cod_inst != 3 && cod_inst != 4 && cod_inst != 5  && cod_inst != 8 && cod_inst != 12 && cod_inst != 20 && cod_inst != 21 && cod_inst != 35 && cod_inst != 43)
		return -1;

	return cod_inst;
}


int  decifra_operacao(int inst){
	int cod_op;

	cod_op = (inst & 63); //111111

	 if(cod_op == 32){ //add
	 	cod_op = 0;
	 }else if(cod_op == 34){ //sub
	 	cod_op = 1;
	 }else if(cod_op == 36){ //and
	 	cod_op = 3;
	 }else if(cod_op == 37){ //or
	 	cod_op = 4;
	 }else if(cod_op == 42){ //set or less than
	 	cod_op = 5;
	 }


	 return cod_op;

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
	u->PCWrite = (S3 AND S2 AND NOT(S1)) OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND NOT(S0)) OR (S3 AND S2 AND S0) OR (S3 AND NOT(S1) AND S0);
	u->MemWrite = NOT(S3) AND S2 AND NOT(S1) AND S0;
	u->MemRead = (NOT(S3) AND NOT(S2) AND NOT(S1) AND NOT(S0)) OR (NOT(S3) AND NOT(S2) AND S1 AND S0);
	u->RegWrite = (NOT(S3) AND S2 AND NOT(S1) AND NOT(S0)) OR (NOT(S3) AND S2 AND S1 AND S0) OR (S3 AND NOT(S2) AND S1 AND S0) OR (S3 AND S2 AND NOT(S1) AND S0);

	// AC'D + ABC' + ABD + A'B'C'D'
	//ABD 
	//ABC' + A'B'C'D'
	//cod_inst = inst >> 26;
	//printf("%d\n",cod_inst);

	int OP0, OP1, OP2, OP3, OP4, OP5;

	OP5 = cod_inst >> 5;
	OP4 = (cod_inst & 16) >> 4;
	OP3 = (cod_inst & 8) >> 3;
	OP2 = (cod_inst & 4) >> 2;
	OP1 = (cod_inst & 2) >> 1;
	OP0 = (cod_inst & 1);
	printf("%d%d%d%d%d%d\n",OP5, OP4, OP3, OP2, OP1, OP0);

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
	//010100
	// 0001

	//100011-> 35 (LW)
	//101011-> 43 (SW)
	//001000-> 8 (ADDI)
	//001100-> 12 (ANDI)
	//010101-> 21 (JALR)

	u->proximo_estado.s1 = (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND OP5 AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND OP5 AND NOT(OP4) AND OP3 AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND NOT(OP4) AND OP3 AND NOT(OP2) AND NOT(OP1) AND NOT(OP0))
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND OP5 AND NOT(OP4) AND NOT(OP3) AND NOT(OP2) AND OP1 AND OP0)
		OR (NOT(S3) AND NOT(S2) AND NOT(S1) AND S0 AND NOT(OP5) AND OP4 AND NOT(OP3) AND OP2 AND NOT(OP1) AND NOT(OP0))
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND NOT(OP5) AND NOT(OP4) AND OP3 AND NOT(OP2) AND NOT(OP1) AND NOT(OP0))
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
		OR (S3 AND S2 AND S1 AND NOT(S0))
		OR (NOT(S3) AND NOT(S2) AND S1 AND NOT(S0) AND NOT(OP5) AND NOT(OP4) AND OP3 AND NOT(OP2) AND NOT(OP1) AND NOT(OP0));

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


void Imprime_registradores(int* Registradores){

	printf("\nBanco de Registradores\n");

	printf("R00(r0)=%d\n", Registradores[0]);
	printf("R01(at)=%d\n", Registradores[1]);
	printf("R02(v0)=%d\n", Registradores[2]);
	printf("R03(v1)=%d\n", Registradores[3]);
	printf("R04(a0)=%d\n", Registradores[4]);
	printf("R05(a1)=%d\n", Registradores[5]);
	printf("R06(a2)=%d\n", Registradores[6]);
	printf("R07(a3)=%d\n", Registradores[7]);
	printf("R08(t0)=%d\n", Registradores[8]);
	printf("R09(t1)=%d\n", Registradores[9]);
	printf("R10(t2)=%d\n", Registradores[10]);
	printf("R11(t3)=%d\n", Registradores[11]);
	printf("R12(t4)=%d\n", Registradores[12]);
	printf("R13(t5)=%d\n", Registradores[13]);
	printf("R14(t6)=%d\n", Registradores[14]);
	printf("R15(t7)=%d\n", Registradores[15]);
	printf("R16(s0)=%d\n", Registradores[16]);
	printf("R17(s1)=%d\n", Registradores[17]);
	printf("R18(s2)=%d\n", Registradores[18]);
	printf("R19(s3)=%d\n", Registradores[19]);
	printf("R20(s4)=%d\n", Registradores[20]);
	printf("R21(s5)=%d\n", Registradores[21]);
	printf("R22(s6)=%d\n", Registradores[22]);
	printf("R23(s7)=%d\n", Registradores[23]);
	printf("R24(t8)=%d\n", Registradores[24]);
	printf("R25(t9)=%d\n", Registradores[25]);
	printf("R26(k0)=%d\n", Registradores[26]);
	printf("R27(k1)=%d\n", Registradores[27]);
	printf("R28(gp)=%d\n", Registradores[28]);
	printf("R29(sp)=%d\n", Registradores[29]);
	printf("R30(fp)=%d\n", Registradores[30]);
	printf("R31(ra)=%d\n", Registradores[31]);

}