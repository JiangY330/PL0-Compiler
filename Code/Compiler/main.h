#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "LexiconAnalysis.h"
#include "Error.h"
#include "SyntaxAnalysis.h"
#include "SymbolTableManage.h"
#include "MidcodeProduecer.h"
#include "FinalcodeProducer.h"
#include "Optimize.h"
#include "DAGAnalysis.h"
#include "DataFlowAnalysis.h"
#include "FinalcodeProducerOP.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
int cc;  //行缓冲区指针
int ll;  //行缓冲区长度
int lineNum;  //行号
int number;  //数字
int nowLevel;  //当前层次数
int pc;  //中间代码表指针（指令号）
int pc1;
int symbolIndex;  //标识符表指针
int levelTableIndex;  //层次表指针
int valIndex;  //数据存储区指针
int expressionType;  //记录表达式返回值类型 0:integer 1:char
int strIndex;  //字符串数组指针
int symbolLevel;  //标识符层次
int errorLineNum;  //记录错误出现的行数
int blockNum;
int errorSum;
char ch;  //读取到的字符
bool insertSign;  //是否插入标志
bool ArrayOpen;
enum symbol symbol;  //存放符号类型
operandType nop;  //定义一个操作数的空类型
int valueMem[1000];  //数据存储区
int funcOrder[100];
int block_in_num[100];
int block_out_num[100];
int block_def_num[100];
int block_use_num[100];
int block_begin[100];
int block_begin_op[100];
int jumpRelation[100][100];
char line[1000];  //行缓冲区
char token[256];  //存放当前字符
char strTable[100][100];  //存放字符串
bool Bbegin[1000];
symbolType symbolTable[1000];  //标识符表
midcodeType midcodeTable[1000];  //四元式-中间代码表
midcodeType OPmidcodeTable[1000];
levelType levelTable[1000];  //存放过程或者函数的每层相关信息的表（用层次号作为指针）
operandType block_in[100][100];
operandType block_out[100][100];
operandType block_def[100][100];
operandType block_use[100][100];
operandType block_mem[100][2];
ifstream fin;
ofstream fout;


//*********************************Function*********************************
void init();  //初始化
void LexiconAnalysisTest();  //词法分析程序测试
void symbolTableTest();  //符号表内容测试
void midcodeTest();  //中间代码测试


#endif // MAIN_H_INCLUDED
