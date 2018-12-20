#ifndef DAGANALYSIS_H_INCLUDED
#define DAGANALYSIS_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MidcodeProduecer.h"
#include "SymbolTableManage.h"
using namespace std;


//***********************************Data***********************************
struct DAGDiagramItem  //DAGÍ¼½ÚµãÏî
{
	operationType op;
	int l, r;
	bool isMid;
	operandType item;
};
struct DAGNaviItem
{
	operandType item;
	int no;
};
extern int pc;
extern int pc1;
extern int valueMem[1000];
extern int valIndex;
extern int symbolIndex;
extern int strIndex;
extern int blockNum;
extern operandType nop;
extern ofstream fout;
extern int block_in_num[100];
extern int block_out_num[100];
extern int block_begin[100];
extern int block_begin_op[100];
extern bool Bbegin[1000];
extern operandType block_in[100][100];
extern operandType block_out[100][100];
extern symbolType symbolTable[1000];
extern midcodeType midcodeTable[1000];
extern midcodeType OPmidcodeTable[1000];
extern char strTable[100][100];


//*********************************Function*********************************
void DAGOptimize(int index);
void buildDAG(int index);
void exportCode(int index);
void InsertNavi(operandType x, int loc);
void InsertDiagram(operationType op, int l, int r);
void dfs(int index);
void initArray(int index);
int findInNavi(operandType x);
int findInDiagram(operationType op, int l, int r);

#endif // DAGANALYSIS_H_INCLUDED
