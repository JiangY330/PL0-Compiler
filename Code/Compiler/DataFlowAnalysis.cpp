#include "DataFlowAnalysis.h"

operandType flowNavi[100];
int flowNavi_num;

void DataFlowAnalysis(int index)
{
	int i, j, k;
	blockNum = 0;
	memset(jumpRelation, 0, sizeof(jumpRelation));
	memset(block_in, 0, sizeof(block_in));
	memset(block_out, 0, sizeof(block_out));
	memset(block_use, 0, sizeof(block_use));
	memset(block_def, 0, sizeof(block_def));
	memset(block_begin, 0, sizeof(block_begin));
	memset(block_in_num, 0, sizeof(block_in_num));
	memset(block_out_num, 0, sizeof(block_out_num));
	memset(block_def_num, 0, sizeof(block_def_num));
	memset(block_use_num, 0, sizeof(block_use_num));

	int enter = levelTable[index].entranceAddress;
	int quit = levelTable[index].exitAddress;

	if (judgeArray(enter, quit) && (ArrayOpen))
	{
		int dist = enter - pc1;
		for (i = enter; i < quit; i++)
		{
			OPmidcodeTable[pc1] = midcodeTable[i];
			if (OPmidcodeTable[pc1].des.typeNum == 2)
			{
				OPmidcodeTable[pc1].des.value -= dist;
			}
			pc1++;
		}
	}
	else
	{
		divideBlock(enter, quit);
		initDefUse();
		LiveVarAnalysis();
		DstRam(index);
		for (i = 0; i < blockNum; i++)
		{
			DAGOptimize(i);
		}
		block_begin_op[blockNum] = pc1;
		adjustJMP();
	}
}

bool judgeArray(int enter, int quit)
{
	int i, j, k;
	for (i = enter; i < quit; i++)
	{
		if (midcodeTable[i].src1.auxPara == 3)
		{
			return true;
		}
		if (midcodeTable[i].src2.auxPara == 3)
		{
			return true;
		}
		if (midcodeTable[i].des.auxPara == 3)
		{
			return true;
		}
	}
	return false;
}

void divideBlock(int enter, int quit)
{
	int i, j, k, tmp;
	k = 0;
	memset(block_begin, 0, sizeof(block_begin));
	block_begin[0] = enter;
	k++;
	for (i = enter; i < quit; i++)
	{
		switch (midcodeTable[i].op)
		{
		case JE: case JG: case JGE:
		case JLE: case JMP: case JNE:
		case JL:
			block_begin[k] = i + 1;
			block_begin[k + 1] = midcodeTable[i].des.value;
			k += 2;
			break;
		case CALL:
			block_begin[k++] = i + 1;
		default:
			break;
		}
	}
	for (i = 0; i < k; i++)
	{
		for (j = i + 1; j < k; j++)
		{
			if (block_begin[i] > block_begin[j])
			{
				tmp = block_begin[i];
				block_begin[i] = block_begin[j];
				block_begin[j] = tmp;
			}
			else if (block_begin[i] == block_begin[j])
			{
				block_begin[j] = block_begin[k - 1];
				k--;
				j--;
			}
		}
	}
	block_begin[k] = quit;
	blockNum = k;
	for (i = 0; i < k - 1; i++)
	{
		jumpRelation[i][i + 1] = 1;
	}
	for (i = enter; i < quit; i++)
	{
		switch (midcodeTable[i].op)
		{
		case JE: case JG: case JGE:
		case JLE: case JNE:	case JL:
			jumpRelation[findBlock(i)][findBlock(midcodeTable[i].des.value)] = 1;
			break;
		case JMP:
			jumpRelation[findBlock(i)][findBlock(i) + 1] = 0;
			jumpRelation[findBlock(i)][findBlock(midcodeTable[i].des.value)] = 1;
			break;
		default:
			break;
		}
	}
}

void LiveVarAnalysis()
{
	int i, j, k;
	bool b = true;
	while (b)
	{
		b = false;
		for (i = blockNum - 1; i >= 0; i--)
		{
			for (j = 0; j < blockNum; j++)
			{
				if (jumpRelation[i][j] == 1)
				{
					if (AddOut(i, j))
					{
						b = true;
					}
				}
			}
			if (refIn(i))
			{
				b = true;
			}
		}
	}

}

void DstRam(int index)
{
	int i, j, k, max;
	bool net[100][100];
	int netval[100];
	int stack[100];
	int stack_num = 0;
	bool ide[100];
	bool b;
	memset(ide, 0, sizeof(ide));
	memset(stack, 0, sizeof(stack));
	memset(net, 0, sizeof(net));
	memset(netval, 0, sizeof(netval));
	initFlowNavi();
	memset(block_mem, 0, sizeof(block_mem));
	for (i = 0; i < blockNum; i++)
	{
		for (j = 0; j < block_in_num[i]; j++)
		{
			for (k = 0; k < block_in_num[i]; k++)
			{
				if (j != k)
				{
					net[findInFlowNavi(block_in[i][j])][findInFlowNavi(block_in[i][k])] = true;
				}
			}
		}
	}
	for (i = 0; i < flowNavi_num; i++)
	{
		for (j = 0; j < flowNavi_num; j++)
		{
			if (net[i][j])
			{
				netval[i]++;
			}
		}
		ide[i] = true;
	}
	k = flowNavi_num;
	while (k != 0)
	{
		b = false;
		for (i = 0; i < flowNavi_num; i++)
		{
			if ((netval[i] < 2) && (ide[i]))
			{
				stack[stack_num++] = i;
				for (j = 0; j < flowNavi_num; j++)
				{
					if (net[i][j])
					{
						net[i][j] = false;
						netval[i]--;
					}
					if (net[j][i])
					{
						net[j][i] = false;
						netval[j]--;
					}
				}
				k--;
				ide[i] = false;
				b = true;
				break;
			}
		}
		if (!b)
		{
			max = 0;
			for (i = 0; i < flowNavi_num; i++)
			{
				if ((netval[i] > netval[max]) && (ide[i]))
				{
					max = i;
				}
			}
			for (j = 0; j < flowNavi_num; j++)
			{
				if (net[max][j])
				{
					net[max][j] = false;
					netval[max]--;
				}
				if (net[j][max])
				{
					net[j][max] = false;
					netval[j]--;
				}
			}
			k--;
			ide[max] = false;
		}
	}
	for (i = 0; i < blockNum; i++)
	{
		for (j = 0; j < stack_num; j++)
		{
			levelTable[index].mem[j % 2] = flowNavi[stack[j]];
			for (k = 0; k < block_in_num[i]; k++)
			{
				if (operandTypeEqual(flowNavi[stack[j]], block_in[i][k]))
				{
					block_mem[i][j % 2] = block_in[i][k];
					break;
				}
			}
		}
	}
}

void initFlowNavi()
{
	int i, j, k;
	memset(flowNavi, 0, sizeof(flowNavi));
	flowNavi_num = 0;
	bool b;
	for (i = 0; i < blockNum; i++)
	{
		for (j = 0; j < block_in_num[i]; j++)
		{
			b = false;
			for (k = 0; k < flowNavi_num;k++)
			{
				if (operandTypeEqual(flowNavi[k], block_in[i][j]))
				{
					b = true;
					break;
				}
			}
			if (!b)
			{
				flowNavi[flowNavi_num++] = block_in[i][j];
			}
		}
	}
}

int findInFlowNavi(operandType x)
{
	for (int k = 0; k < flowNavi_num;k++)
	{
		if (operandTypeEqual(flowNavi[k], x))
		{
			return k;
		}
	}
	return -1;
}

int findBlock(int index)
{
	int i;
	for (i = 0; i < blockNum; i++)
	{
		if ((block_begin[i] <= index) && (block_begin[i + 1] > index))
			return i;
	}
	return -1;
}

void initDefUse()
{
	int i, j, k;
	for (i = 0; i < blockNum - 1; i++)
	{
		for (j = block_begin[i];j < block_begin[i + 1]; j++)
		{
			if ((midcodeTable[j].src1.typeNum != 0) && (midcodeTable[j].src1.typeNum != 1) && (midcodeTable[j].src1.typeNum != 2) && (midcodeTable[j].src1.typeNum != 5))
			{
				if (!(isUse(i, midcodeTable[j].src1)) && !(isDef(i, midcodeTable[j].src1)))
				{
					block_use[i][block_use_num[i]] = midcodeTable[j].src1;
					block_use_num[i] += 1;
				}
			}
			if ((midcodeTable[j].src2.typeNum != 0) && (midcodeTable[j].src2.typeNum != 1) && (midcodeTable[j].src2.typeNum != 2) && (midcodeTable[j].src2.typeNum != 5))
			{
				if (!(isUse(i, midcodeTable[j].src2)) && !(isDef(i, midcodeTable[j].src2)))
				{
					block_use[i][block_use_num[i]] = midcodeTable[j].src2;
					block_use_num[i] += 1;
				}
			}
			if ((midcodeTable[j].des.typeNum != 0) && (midcodeTable[j].des.typeNum != 1) && (midcodeTable[j].des.typeNum != 2) && (midcodeTable[j].des.typeNum != 5))
			{
				if (!(isUse(i, midcodeTable[j].des)) && !(isDef(i, midcodeTable[j].des)))
				{
					block_def[i][block_def_num[i]] = midcodeTable[j].des;
					block_def_num[i] += 1;
				}
			}
		}
	}
}

bool isUse(int p, operandType a)
{
	int i;
	for (i = 0; i < block_use_num[p]; i++)
	{
		if (operandTypeEqual(block_use[p][i], a))
			return true;
	}
	return false;
}

bool isDef(int p, operandType a)
{
	int i;
	for (i = 0; i < block_def_num[p]; i++)
	{
		if (operandTypeEqual(block_def[p][i], a))
			return true;
	}
	return false;
}

bool AddOut(int p, int q)
{
	int i, j, k;
	bool b1, b2;
	b2 = false;
	for (i = 0; i < block_in_num[q]; i++)
	{
		b1 = false;
		for (j = 0; j < block_out_num[p]; j++)
		{
			if (operandTypeEqual(block_in[q][i], block_out[p][j]))
			{
				b1 = true;
				break;
			}
		}
		if (!b1)
		{
			block_out[p][block_out_num[p]++] = block_in[q][i];
			b2 = true;
		}
	}
	return b2;
}

bool refIn(int index)
{
	int i, j, k;
	bool b1, b2;
	b2 = false;
	operandType tmp[100];
	int tmpNum;
	for (i = 0; i < block_use_num[index]; i++)
	{
		b1 = false;
		for (j = 0; j < block_in_num[index]; j++)
		{
			if (operandTypeEqual(block_use[index][i], block_in[index][j]))
			{
				b1 = true;
				break;
			}
		}
		if (!b1)
		{
			block_in[index][block_in_num[index]++] = block_use[index][i];
			b2 = true;
		}
	}
	tmpNum = block_out_num[index];
	for (i = 0; i < block_out_num[index]; i++)
	{
		tmp[i] = block_out[index][i];
	}

	for (i = 0; i < block_def_num[index]; i++)
	{
		for (j = 0; j < tmpNum; j++)
		{
			if (operandTypeEqual(block_def[index][i], tmp[j]))
			{
				tmp[j] = tmp[--tmpNum];
				break;
			}
		}
	}

	for (i = 0; i < tmpNum; i++)
	{
		b1 = false;
		for (j = 0; j < block_in_num[index]; j++)
		{
			if (operandTypeEqual(tmp[i], block_in[index][j]))
			{
				b1 = true;
				break;
			}
		}
		if (!b1)
		{
			block_in[index][block_in_num[index]++] = tmp[i];
			b2 = true;
		}
	}
	return b2;
}

void adjustJMP()
{
	int i, j, k;
	for (i = 0; i < blockNum; i++)
	{
		for (j = 0; j < blockNum; j++)
		{
			if ((jumpRelation[i][j] == 1) && (j != i + 1))
			{
				OPmidcodeTable[block_begin_op[i + 1] - 1].des.value = block_begin_op[j];
				break;
			}
		}
	}
}