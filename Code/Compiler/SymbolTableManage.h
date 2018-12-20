#ifndef SYMBOLTABLEMANAGE_H_INCLUDED
#define SYMBOLTABLEMANAGE_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Error.h"
#include "MidcodeProduecer.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
enum Type
{
    Integer, Char, Array, Nop
};
enum Kind
{
   Constant, Variable, Procedure, Function, Param, Varparam
};
struct symbolType
{
    char name[MAX_LEX_LEN];  //标识符名称
    Kind kind;  //标识符类型
    Type dataType;  //数据类型
    int address;  //数据区存储对应地址
    int length;  //记录数组长度
	int level;  //标识符所在层次
};
struct findAns
{
    int typeNum;  //1:常量 2:变量 3:数组 4:函数或过程 5:参数
    int level;  //记录相对层数（之前i层）
    int symbolTableIndex;
    int value;
};
struct levelType  //用于记录函数或者过程的相关信息
{
    char name[MAX_LEX_LEN];  //函数名或者函数名
    Kind kind;  //记录函数或者过程类型
    int outNum;  //外层次号
    int levelNum;  //当前层次号
    int symbolAddress;  //函数名或者过程名在符号表中的位置
    int entranceAddress;  //函数或者过程的入口（可用于设置开始标志）
    int exitAddress;  //函数或者过程的出口（可用于设置结束标志）
    int paraNum;  //参数个数
    int varNum;  //变量个数
    int constNum;  //常量个数
    int profuncNum;  //过程函数个数
    int recLen;  //活动记录长度
    int temp;
    operandType mem[2];
};
extern int nowLevel;
extern int symbolIndex;
extern int pc;
extern int levelTableIndex;
extern int valueMem[1000];
extern int start;
extern int end;
extern symbolType symbolTable[1000];
extern levelType levelTable[1000];


//*********************************Function*********************************
bool insertSymbolTable(symbolType tableItem);  //插入符号表
void insertLevelTable(levelType levelTableItem);  //插入层次表
findAns findTable(char* name);  //在符号表中查找相应信息


#endif // SYMBOLTABLEMANAGE_H_INCLUDED
