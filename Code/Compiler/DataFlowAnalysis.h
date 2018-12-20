#ifndef DATAFLOWANALYSIS_H_INCLUDED
#define DATAFLOWANALYSIS_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MidcodeProduecer.h"
#include "SymbolTableManage.h"
#include "DAGAnalysis.h"
using namespace std;


//***********************************Data***********************************
extern int pc;
extern int pc1;
extern int valueMem[1000];
extern int valIndex;
extern int symbolIndex;
extern int strIndex;
extern int blockNum;
extern bool ArrayOpen;
extern operandType nop;
extern operandType block_in[100][100];
extern operandType block_out[100][100];
extern operandType block_def[100][100];
extern operandType block_use[100][100];
extern operandType block_mem[100][2];
extern symbolType symbolTable[1000];
extern midcodeType midcodeTable[1000];
extern midcodeType OPmidcodeTable[1000];
extern char strTable[100][100];
extern int jumpRelation[100][100];
extern int block_in_num[100];
extern int block_out_num[100];
extern int block_def_num[100];
extern int block_use_num[100];
extern int block_begin[100];
extern int blcok_begin_op[100];
extern ofstream fout;


//*********************************Function*********************************
void divideBlock(int enter, int quit);
void DataFlowAnalysis(int index);
void LiveVarAnalysis();
void DstRam(int index);
void initDefUse();
void adjustJMP();
void initFlowNavi();
int findBlock(int index);
int findInFlowNavi(operandType x);
bool isUse(int p, operandType a);
bool isDef(int p, operandType a);
bool refIn(int index);
bool judgeArray(int enter, int quit);
bool AddOut(int p, int q);


#endif // DATAFLOWANALYSIS_H_INCLUDED
