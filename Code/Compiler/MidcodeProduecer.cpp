#include "MidcodeProduecer.h"

void gen(operationType op, operandType src1, operandType src2, operandType res)
{
    midcodeTable[pc].op = op;
    midcodeTable[pc].src1 = src1;
    midcodeTable[pc].src2 = src2;
    midcodeTable[pc].des = res;
    //printMidcode(midcodeTable[pc]);
    pc++;
}

bool operandTypeEqual(operandType src1, operandType src2)
{
	if (src1.typeNum != src2.typeNum)
	{
		return false;
	}
	if (src1.auxPara != src2.auxPara)
	{
		return false;
	}
	if (src1.value != src2.value)
	{
		return false;
	}
	if (src1.auxParaValue != src2.auxParaValue)
	{
		return false;
	}
	return true;
}

