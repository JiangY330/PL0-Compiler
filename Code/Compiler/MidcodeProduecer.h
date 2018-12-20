#ifndef MIDCODEPRODUECER_H_INCLUDED
#define MIDCODEPRODUECER_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
enum operationType
{
	NNN,
    ADD, SUB, MUL, DIVI, NEG,
    JMP, JG, JGE, JL, JLE, JE, JNE,
    ASS, CALL, RET, READ, WRITE, PUSH, POP, PUD, END, NOP
};
struct operandType
{
    int typeNum;  //类型编号1:常数 2:指令入口 3:临时变量 4:直接访问变量 5:字符串 6:函数/过程 7:返回值 7+i:之前i层中的变量
    int value;  //值 常数值|指令地址|相对地址
    int auxPara;  //辅助参数，用于数组和传地址
    int auxParaValue;
};
struct midcodeType
{
    operationType op;
    operandType src1;
    operandType src2;
    operandType des;
};
extern int pc;
extern midcodeType midcodeTable[1000];


//*********************************Function*********************************
void gen(operationType op, operandType src1, operandType src2, operandType res);  //将中间代码记录到四元式表中
bool operandTypeEqual(operandType src1, operandType src2);


#endif // MIDCODEPRODUECER_H_INCLUDED
