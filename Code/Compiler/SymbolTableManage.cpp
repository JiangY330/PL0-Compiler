#include "SymbolTableManage.h"

bool insertSymbolTable(symbolType tempItem)
{
	int sign = 1;
	int i = symbolIndex - 1;

	while (symbolTable[i].level == tempItem.level)
	{
		if (strcmp(symbolTable[i].name, tempItem.name) == 0)
		{
			sign = 0;
			break;
		}
		else
		{
			i--;
			if (i == -1)
            {
                break;
            }
		}
	}

	if (sign == 0)
	{
		cout << "重复定义" << endl;
		return false;
	}
	else
	{
		symbolTable[symbolIndex] = tempItem;
		symbolIndex++;
		return true;
	}
}

void insertLevelTable(levelType tempLevel)
{
	levelTable[levelTableIndex] = tempLevel;
	nowLevel = levelTableIndex;
	levelTableIndex++;
}

findAns findTable(char* name)
{
	findAns tempFind;
	int i, j;
	int level = nowLevel;

	//先查找当前作用域
	for (i = levelTable[level].symbolAddress; i < levelTable[level].symbolAddress+ levelTable[level].constNum; i++)
	{
		if (strcmp(name, symbolTable[i].name) == 0)
		{
			tempFind.typeNum = 1;
			tempFind.level = 0;
			tempFind.symbolTableIndex = i;
			tempFind.value = valueMem[symbolTable[i].address];
			return tempFind;
		}
	}
	for (i = levelTable[level].symbolAddress - levelTable[level].paraNum; i < levelTable[level].symbolAddress; i++)  //此处初始值为何为减法请查看SyntaxAnakysis中funcHead和procHead部分
	{
		if (strcmp(name, symbolTable[i].name) == 0)
		{
			if (symbolTable[i].kind == Varparam)
			{
				tempFind.typeNum = 5;
			}
			else
			{
				tempFind.typeNum = 2;
			}
			tempFind.level = 0;
			tempFind.symbolTableIndex = i;
			tempFind.value = i - levelTable[level].symbolAddress;
			return tempFind;
		}
	}

	int offset = 1;  //偏移地址

	for (i = levelTable[level].symbolAddress + levelTable[level].constNum; i < levelTable[level].symbolAddress + levelTable[level].constNum + levelTable[level].varNum; i++)
	{
		if (strcmp(name, symbolTable[i].name) == 0)
		{
			if (symbolTable[i].length != 0)  //数组变量
			{
				tempFind.typeNum = 3;
				tempFind.level = 0;
				tempFind.symbolTableIndex = i;
				tempFind.value = offset;
				return tempFind;
			}
			else
			{
				tempFind.typeNum = 2;
				tempFind.level = 0;
				tempFind.symbolTableIndex = i;
				tempFind.value = offset;
				return tempFind;
			}
		}
		if (symbolTable[i].length == 0)
		{
			offset++;
		}
		else
		{
			offset += symbolTable[i].length;
		}
	}
	for (i = 0; i < levelTableIndex; i++)
	{
		if ((levelTable[i].outNum == level) && (strcmp(levelTable[i].name, name) == 0))
		{
			tempFind.typeNum = 4;
			tempFind.level = 0;
			tempFind.value = i;
			tempFind.symbolTableIndex = 0;
			return tempFind;
		}
	}

	j = 0;
	while (level != 0)
	{
		j++;  //相对层数加一（之前j层）
		level = levelTable[level].outNum;
		for (i = levelTable[level].symbolAddress; i < levelTable[level].symbolAddress + levelTable[level].constNum; i++)
		{
			if (strcmp(name, symbolTable[i].name) == 0)
			{
				tempFind.typeNum = 1;
				tempFind.level = 0;
				tempFind.symbolTableIndex = i;
				tempFind.value = valueMem[symbolTable[i].address];
				return tempFind;
			}
		}
		for (i = levelTable[level].symbolAddress - levelTable[level].paraNum; i < levelTable[level].symbolAddress; i++)
		{
			if (strcmp(name, symbolTable[i].name) == 0)
			{
				if (symbolTable[i].kind == Varparam)
				{
					tempFind.typeNum = 5;
				}

				{
					tempFind.typeNum = 2;
				}
				tempFind.level = j;
				tempFind.symbolTableIndex = i;
				tempFind.value = i - levelTable[level].symbolAddress;
				return tempFind;
			}
		}

		int offset = 1;

		for (i = levelTable[level].symbolAddress + levelTable[level].constNum; i < levelTable[level].symbolAddress + levelTable[level].constNum + levelTable[level].varNum; i++)
		{
			if (strcmp(name, symbolTable[i].name) == 0)
			{
				if (symbolTable[i].length != 0)
				{
					tempFind.typeNum = 3;
					tempFind.level = j;
					tempFind.symbolTableIndex = i;
					tempFind.value = offset;
					return tempFind;
				}
				else
				{
					tempFind.typeNum = 2;
					tempFind.level = j;
					tempFind.symbolTableIndex = i;
					tempFind.value = offset;
					return tempFind;
				}
			}
			if (symbolTable[i].length == 0)
			{
				offset++;
			}
			else
			{
				offset += symbolTable[i].length;
			}
		}

		for (i = 0; i < levelTableIndex; i++)
		{
			if ((levelTable[i].outNum == level) && (strcmp(levelTable[i].name, name) == 0))
			{
				tempFind.typeNum = 4;
				tempFind.level = 0;
				tempFind.value = i;
				tempFind.symbolTableIndex = 0;
				return tempFind;
			}
		}
	}
	//未找到
	tempFind.typeNum = 0;
	return tempFind;
}
