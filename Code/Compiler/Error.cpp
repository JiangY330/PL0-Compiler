#include "Error.h"

void Error(int errorNum)
{
	cout << line << endl;
	cout << "第" << lineNum << "行,";
	cout << "错误原因：";
	switch (errorNum)
	{
	case 1:
		cout << "字符缺少 '" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 2:
		cout << "非法字符" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 3:
		cout << "字符串缺少 \"" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 4:
		cout << "程序未以 . 结束" << endl;
		errorSum++;
		break;
	case 5:
		cout << "在" << line << "之前缺少 ;" << endl;
		errorSum++;
		break;
	case 6:
		cout << "缺少 ;" << endl;
		errorSum++;
		break;
	case 7:
		cout << "重复定义，符号表插入失败" << endl;
		errorSum++;
		break;
	case 8:
		cout << "数组定义数据类型不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 9:
		cout << "缺少保留字 of" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 10:
		cout << "缺少 ]" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 11:
		cout << "数组长度类型错误" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 12:
		cout << "缺少 [" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 13:
		cout << "缺少保留字 array" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 14:
		cout << "缺少 :" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 15:
		cout << "常量赋值符号不合法，非 :=" << endl;
		errorSum++;
		break;
	case 16:
		cout << "常量数据类型不合法" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 17:
		cout << "常量赋值符号不合法" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != COMMA)
		{
			getsym();
		}
		break;
	case 18:
		cout << "标识符定义不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 19:
		cout << "函数未以 ; 结束" << endl;
		errorSum++;
		break;
	case 20:
		cout << "过程未以 ; 结束" << endl;
		errorSum++;
		break;
	case 21:
		cout << "函数数据类型不合法" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != VARTK && symbol != BEGINTK)
		{
			getsym();
		}
		break;
	case 22:
		cout << "缺少保留字 end" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != FUNCTIONTK && symbol != PROCEDURETK)
		{
			getsym();
		}
		break;
	case 23:
		cout << "缺少保留字 begin" << endl;
		errorSum++;
		while (symbol != ENDTK)
		{
			getsym();
		}
		getsym();
		break;
	case 24:
		cout << "不合法语句" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != ENDTK)
		{
			getsym();
		}
		break;
	case 25:
		cout << "赋值语句标识符类型不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 26:
		cout << "缺少 :=" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 27:
		cout << "缺少保留字 then" << endl;
		errorSum++;
		while (symbol != ELSETK && symbol != ENDTK) 
		{
			getsym();
		}
		break;
	case 28:
		cout << "缺少保留字 if" << endl;
		errorSum++;
		while (symbol != SEMICN && symbol != THENTK && symbol != ELSETK)
		{
			getsym();
		}
		break;
	case 29:
		cout << "case语句情况元素表中常量类型不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 30:
		cout << "缺少保留字 case" << endl;
		errorSum++;
		while (symbol != ENDTK)
		{
			getsym();
		}
		break;
	case 31:
		cout << "查询符号表失败，未定义" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 32:
		cout << "缺少 )" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 33 :
		cout << "缺少 (" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 34:
		cout << "缺少保留字 read" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 35:
		cout << "缺少保留字 write" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 36:
		cout << "缺少保留字 downto 或 to" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 37:
		cout << "缺少保留字 do" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 38:
		cout << "缺少保留字 for" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 39:
		cout << "var类型和参数类型不匹配，需要使用变量" << endl;
		errorSum++;
		break;
	case 40:
		cout << "调用语句缺少 , 或 ;" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 41:
		cout << "参数数据类型定义不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 42:
		cout << "变量数据类型定义不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 43:
		cout << "参数个数不匹配" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 44:
		cout << "参数个数为0，调用过程或函数无参数" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 45:
		cout << "参数个数为0，不应有括号" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 46:
		cout << "因子类型不合法" << endl;
		errorSum++;
		while (symbol != SEMICN)
		{
			getsym();
		}
		break;
	case 47:
		cout << "write语句格式不合法" << endl;
		errorSum++;
		while (symbol != RPARENT && symbol != SEMICN)
		{
			getsym();
		}
		break;
	default:
		break;
	}
}
