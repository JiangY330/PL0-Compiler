#ifndef LEXICONANALYSIS_H_INCLUDED
#define LEXICONANALYSIS_H_INCLUDED


//**********************************Header**********************************
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Error.h"
#define MAX_LEX_LEN 30
#define MAX_VAR_NUM 20
using namespace std;


//***********************************Data***********************************
enum symbol
{
    NUL, INTCON, CHARCON, IDENT,
    INTTK, CHARTK, STRTK, ARRAYTK, CONSTTK, VARTK, PROCEDURETK, FUNCTIONTK,
    BEGINTK, ENDTK, IFTK, THENTK, ELSETK, CASETK, OFTK, FORTK, TOTK, DOWNTK, DOTK, READTK, WRITETK,
    PLUS, MINUS, MULT, DIV, LSS, LEQ, GRE, GEQ, EQL, NEQ, ASSIGN, LPARENT, RPARENT, LBRACK, RBRACK, COLON, COMMA, SEMICN, PERIOD
};
extern ifstream fin;
extern char line[1000];
extern char token[256];
extern char ch;
extern int cc;
extern int ll;
extern int lineNum;
extern int number;
extern enum symbol symbol;


//*********************************Function*********************************
void getch();  //读取下一字符
void getsym();  //词法分析程序
void clearLine();  //清空行缓冲区
void clearToken();  //清空字符存放区内容
void addToken();  //将单个字符放入字符存放区中
bool isSpace();  //判断是否为空格
bool isNewLine();  //判断是否为换行符
bool isTab();  //判断是否为换码符
bool isLetter();  //判断是否为字母
bool ifLetter(); //判断是否为字母的同时再将标识符中所有字母转换成小写
bool isDigit();  //判断是否为数字
bool isStr();  //判断是否是字符串
int reserverWords();  //查询保留字表确定类型助记符
int changeNumber();  //转换数字


#endif // LEXICONANALYSIS_H_INCLUDED
