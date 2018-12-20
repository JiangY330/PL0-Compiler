#ifndef FINALCODEPRODUCEROP_H_INCLUDED
#define FINALCODEPRODUCEROP_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include "MidcodeProduecer.h"
#include "SymbolTableManage.h"
using namespace std;


//***********************************Data***********************************
struct IdNaviItem
{
	operandType item;
	string value;
	int prev;
	string preOp[5];
};
struct MemPoolItem
{
	operandType item;
	string mem;
	bool isUse;
};
extern int valueMem[1000];
extern int valIndex;
extern int symbolIndex;
extern midcodeType OPmidcodeTable[1000];
extern int pc1;
extern symbolType symbolTable[1000];
extern ofstream fout;
extern char strTable[100][100];
extern int strIndex;
extern bool Bbegin[1000];
extern operandType nop;


//*********************************Function*********************************
void FinalcodeProducerOP();
void FinalcodeProducerOPinit();
int counttmp(int index, int offset);
int findInIdNavi(operandType x);
void initIdNavi(int index);
void insertIdNavi(operandType x, int j);
string itost(int x);
int insertMemPool(int index);
int findInMemPool(operandType x);

#endif // FINALCODEPRODUCEROP_H_INCLUDED
