#ifndef OPTIMIZE_H_INCLUDED
#define OPTIMIZE_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MidcodeProduecer.h"
#include "SymbolTableManage.h"
#include "DAGAnalysis.h"
#include "DataFlowAnalysis.h"
using namespace std;


//***********************************Data***********************************
extern int pc;
extern int pc1;
extern int valueMem[1000];
extern int valIndex;
extern int symbolIndex;
extern midcodeType midcodeTable[1000];
extern int funcOrder[100];


//*********************************Function*********************************
void Optimize();
void divideFunc();


#endif // OPTIMIZE_H_INCLUDED
