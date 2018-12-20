#ifndef FINALCODEPRODUCER_H_INCLUDED
#define FINALCODEPRODUCER_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "MidcodeProduecer.h"
#include "SymbolTableManage.h"
using namespace std;


//***********************************Data***********************************
extern int pc;
extern int valIndex;
extern int symbolIndex;
extern int strIndex;
extern int valueMem[1000];
extern symbolType symbolTable[1000];
extern midcodeType midcodeTable[1000];
extern char strTable[100][100];
extern ofstream fout;


//*********************************Function*********************************
void FinalcodeProducer();  //Éú³É»ã±à´úÂë
int CountTemp(int index, int offset);



#endif // FINALCODEPRODUCER_H_INCLUDED
