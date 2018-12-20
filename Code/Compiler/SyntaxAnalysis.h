#ifndef SYNTAXANALYSIS_H_INCLUDED
#define SYNTAXANALYSIS_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "LexiconAnalysis.h"
#include "SymbolTableManage.h"
#include "Error.h"
#include "MidcodeProduecer.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
extern int number;
extern int symbolIndex;
extern int nowLevel;
extern int pc;
extern int valIndex;
extern int expressionType;
extern int strIndex;
extern int symbolLevel;
extern bool insertSign;
extern operandType nop;
extern enum symbol symbol;
extern symbolType symbolTable[1000];
extern levelType levelTable[1000];
extern int valueMem[1000];
extern char strTable[100][100];


//*********************************Function*********************************
void program();
void block();
void varDeclaration();
void constDeclaration();
void funcDeclaration();
void procDeclaration();
void funcHead();
void procHead();
void compoundStatement();
void statement();
void assignStatement();
void ifStatement();
void caseStatement();
void readStatement();
void writeStatement();
void forStatement();
int arguement();
int argSegment();
operandType callStatement();
operandType expression();
operandType expression2();
operandType term();
operandType factor();


#endif // SYNTAXANALYSIS_H_INCLUDED
