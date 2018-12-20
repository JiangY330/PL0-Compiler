#include "DAGAnalysis.h"

DAGNaviItem DAGNavi[500];
DAGDiagramItem DAGDiagram[500];
int DAGDiagram_num;
int DAGNavi_num;
bool ItemRel[500][500];
int order[500];
int orderL;
midcodeType tmpQuad[500];
int tmppc;

void DAGOptimize(int index)
{
	block_begin_op[index] = pc1;
	Bbegin[pc1] = true;
	int i;
	buildDAG(index);
	exportCode(index);
	for (i = 0; i < tmppc; i++)
	{
		OPmidcodeTable[pc1++] = tmpQuad[i];
	}
}

void buildDAG(int index)
{
	DAGDiagram_num = 0;
	DAGNavi_num = 0;
	memset(DAGNavi, 0, sizeof(DAGNavi));
	memset(DAGDiagram, 0, sizeof(DAGDiagram));
	memset(ItemRel, 0, sizeof(ItemRel));

	int i, j, k;
	int l, r, s, d;
	for (i = block_begin[index]; i < block_begin[index + 1]; i++)
	{
		if ((midcodeTable[i].op == JE) || (midcodeTable[i].op == JG)
			|| (midcodeTable[i].op == JLE) || (midcodeTable[i].op == JGE)
			|| (midcodeTable[i].op == JNE) || (midcodeTable[i].op == JL)
			|| (midcodeTable[i].op == JMP) || (midcodeTable[i].op == CALL)
			|| (midcodeTable[i].op == RET))
		{

		}
		else
		{
			l = findInNavi(midcodeTable[i].src1);
			r = findInNavi(midcodeTable[i].src2);
			if (l == -1)
			{
				l = DAGNavi_num;
				DAGDiagram[DAGDiagram_num].item = midcodeTable[i].src1;
				DAGDiagram[DAGDiagram_num].isMid = false;
				InsertNavi(midcodeTable[i].src1, DAGDiagram_num++);
			}
			if (r == -1)
			{
				r = DAGNavi_num;
				DAGDiagram[DAGDiagram_num].item = midcodeTable[i].src2;
				DAGDiagram[DAGDiagram_num].isMid = false;
				InsertNavi(midcodeTable[i].src2, DAGDiagram_num++);
			}

			if (midcodeTable[i].op == ASS)
				s = DAGNavi[l].no;
			else
				s = findInDiagram(midcodeTable[i].op, DAGNavi[l].no, DAGNavi[r].no);

			if (s == -1)
			{
				s = DAGDiagram_num;
				InsertDiagram(midcodeTable[i].op, DAGNavi[l].no, DAGNavi[r].no);
			}
			d = findInNavi(midcodeTable[i].des);
			if (d == -1)
			{
				InsertNavi(midcodeTable[i].des, s);
			}
			else
			{
				DAGNavi[d].no = s;
			}
		}
	}
}

int findInNavi(operandType x)
{
	int i, j;
	for (i = 0; i < DAGNavi_num; i++)
	{
		if (operandTypeEqual(x, DAGNavi[i].item))
		{
			return i;
		}
	}
	return -1;
}

void InsertNavi(operandType x, int loc)
{
	DAGNavi[DAGNavi_num].item = x;
	DAGNavi[DAGNavi_num].no = loc;
	DAGNavi_num++;
}

int findInDiagram(operationType op, int l, int r)
{
	int i;
	for (i = 0; i < DAGDiagram_num; i++)
	{
		if ((DAGDiagram[i].op == op) && (DAGDiagram[i].l == l) && (DAGDiagram[i].r == r))
		{
			return i;
		}
	}
	return -1;
}

void InsertDiagram(operationType op, int l, int r)
{
	DAGDiagram[DAGDiagram_num].op = op;
	DAGDiagram[DAGDiagram_num].l = l;
	DAGDiagram[DAGDiagram_num].r = r;
	ItemRel[l][DAGDiagram_num] = true;
	ItemRel[r][DAGDiagram_num] = true;
	DAGDiagram[DAGDiagram_num].isMid = true;
	DAGDiagram_num++;
}

void exportCode(int index)
{
	int i, j, k;
	int l, r;
	operandType ttt;
	orderL = 0;
	memset(order, 0, sizeof(order));
	memset(tmpQuad, 0, sizeof(tmpQuad));
	tmppc = 0;
	initArray(index);
	for (i = DAGDiagram_num - 1; i >= 0; i--)
	{
		dfs(i);
	}
	for (i = orderL - 1; i >= 0; i--)
	{
		operandType src1, src2, res;
		j = order[i];
		if (DAGDiagram[DAGDiagram[j].l].isMid)
		{
			src1.typeNum = 3;
			src1.value = DAGDiagram[j].l * -1;
			src1.auxPara = 0;
			src1.auxParaValue = 0;
		}
		else
		{
			src1 = DAGDiagram[DAGDiagram[j].l].item;
		}
		if (DAGDiagram[DAGDiagram[j].r].isMid)
		{
			src2.typeNum = 3;
			src2.value = DAGDiagram[j].r * -1;
			src2.auxPara = 0;
			src2.auxParaValue = 0;
		}
		else
		{
			src2 = DAGDiagram[DAGDiagram[j].r].item;
		}
		res.typeNum = 3;
		res.value = j * -1;
		res.auxPara = 0;
		res.auxParaValue = 0;
		tmpQuad[tmppc].src1 = src1;
		tmpQuad[tmppc].src2 = src2;
		tmpQuad[tmppc].des = res;
		tmpQuad[tmppc].op = DAGDiagram[j].op;
		if (tmpQuad[tmppc].op == ASS)
		{
			tmpQuad[tmppc].src1 = DAGDiagram[j].item;
		}
		tmppc++;
	}
	for (i = block_begin[index]; i < block_begin[index + 1]; i++)
	{
		if ((midcodeTable[i].des.typeNum != 0) && (midcodeTable[i].des.typeNum != 1) && (midcodeTable[i].des.typeNum != 2) && (midcodeTable[i].des.typeNum != 5) && (midcodeTable[i].des.typeNum != 3))
		{
			tmpQuad[tmppc].op = ASS;
			tmpQuad[tmppc].des = midcodeTable[i].des;
			tmpQuad[tmppc].src2 = nop;
			l = findInNavi(midcodeTable[i].des);
			if (DAGDiagram[DAGNavi[l].no].isMid)
			{
				tmpQuad[tmppc].src1.typeNum = 3;
				tmpQuad[tmppc].src1.value = DAGNavi[l].no * -1;
				tmpQuad[tmppc].src1.auxPara = 0;
				tmpQuad[tmppc].src1.auxParaValue = 0;
			}
			else
			{
				tmpQuad[tmppc].src1 = DAGDiagram[DAGNavi[l].no].item;
			}
			tmppc++;
		}
	}
	for (i = 0; i < block_out_num[index]; i++)
	{
		if (block_out[index][i].typeNum == 3)
		{
			l = findInNavi(block_out[index][i]);
			if (l != -1)
			{
				tmpQuad[tmppc].op = ASS;
				tmpQuad[tmppc].des = block_out[index][i];
				tmpQuad[tmppc].src2 = nop;
				l = findInNavi(block_out[index][i]);
				if (DAGDiagram[DAGNavi[l].no].isMid)
				{
					tmpQuad[tmppc].src1.typeNum = 3;
					tmpQuad[tmppc].src1.value = DAGNavi[l].no * -1;
					tmpQuad[tmppc].src1.auxPara = 0;
					tmpQuad[tmppc].src1.auxParaValue = 0;
				}
				else
				{
					tmpQuad[tmppc].src1 = DAGDiagram[DAGNavi[l].no].item;
				}
				tmppc++;
			}
		}
	}
	for (i = block_begin[index]; i < block_begin[index + 1]; i++)
	{
		if ((midcodeTable[i].op == JE) || (midcodeTable[i].op == JG)
			|| (midcodeTable[i].op == JLE) || (midcodeTable[i].op == JGE)
			|| (midcodeTable[i].op == JNE) || (midcodeTable[i].op == JL)
			|| (midcodeTable[i].op == JMP) || (midcodeTable[i].op == CALL)
			|| (midcodeTable[i].op == RET))
		{
			tmpQuad[tmppc].op = midcodeTable[i].op;
			tmpQuad[tmppc].des = midcodeTable[i].des;
			l = findInNavi(midcodeTable[i].src1);
			r = findInNavi(midcodeTable[i].src2);
			if (l == -1)
			{
				tmpQuad[tmppc].src1 = midcodeTable[i].src1;
			}
			else
			{
				if (DAGDiagram[DAGNavi[l].no].isMid)
				{
					tmpQuad[tmppc].src1.typeNum = 3;
					tmpQuad[tmppc].src1.value = DAGNavi[l].no * -1;
					tmpQuad[tmppc].src1.auxPara = 0;
					tmpQuad[tmppc].src1.auxParaValue = 0;
				}
				else
				{
					tmpQuad[tmppc].src1 = DAGDiagram[DAGNavi[l].no].item;
				}
			}
			if (r == -1)
			{
				tmpQuad[tmppc].src2 = midcodeTable[i].src2;
			}
			else
			{
				if (DAGDiagram[DAGNavi[r].no].isMid)
				{
					tmpQuad[tmppc].src2.typeNum = 3;
					tmpQuad[tmppc].src2.value = DAGNavi[l].no * -1;
					tmpQuad[tmppc].src2.auxPara = 0;
					tmpQuad[tmppc].src2.auxParaValue = 0;
				}
				else
				{
					tmpQuad[tmppc].src2 = DAGDiagram[DAGNavi[r].no].item;
				}
			}
			tmppc++;
		}
	}

	for (i = 0; i < tmppc; i++)
	{
		if (tmpQuad[i].src1.auxPara == 3)
		{
			ttt.typeNum = 3;
			ttt.value = tmpQuad[i].src1.auxParaValue;
			ttt.auxPara = 0;
			ttt.auxParaValue = 0;
			l = findInNavi(ttt);
			if (DAGDiagram[DAGNavi[l].no].isMid)
			{
				tmpQuad[i].src1.auxPara = 3;
				tmpQuad[i].src1.auxParaValue = DAGNavi[l].no * -1;
			}
		}
		if (tmpQuad[i].src2.auxPara == 3)
		{
			ttt.typeNum = 3;
			ttt.value = tmpQuad[i].src2.auxParaValue;
			ttt.auxPara = 0;
			ttt.auxParaValue = 0;
			l = findInNavi(ttt);
			if (DAGDiagram[DAGNavi[l].no].isMid)
			{
				tmpQuad[i].src2.auxPara = 3;
				tmpQuad[i].src2.auxParaValue = DAGNavi[l].no * -1;
			}
		}
		if (tmpQuad[i].des.auxPara == 3)
		{
			ttt.typeNum = 3;
			ttt.value = tmpQuad[i].des.auxParaValue;
			ttt.auxPara = 0;
			ttt.auxParaValue = 0;
			l = findInNavi(ttt);
			if (DAGDiagram[DAGNavi[l].no].isMid)
			{
				tmpQuad[i].des.auxPara = 3;
				tmpQuad[i].des.auxParaValue = DAGNavi[l].no * -1;
			}
		}
	}
}

void dfs(int index)
{
	int i, j, k;
	if (!DAGDiagram[index].isMid)
		return;
	bool b = true;
	for (i = 0; i < DAGDiagram_num; i++)
	{
		if (ItemRel[index][i])
		{
			b = false;
			break;
		}
	}
	if (b)
	{
		order[orderL++] = index;
		ItemRel[DAGDiagram[index].l][index] = false;
		ItemRel[DAGDiagram[index].r][index] = false;
		ItemRel[index][index] = true;
		dfs(DAGDiagram[index].l);
		dfs(DAGDiagram[index].r);
	}
}

void initArray(int index)
{
	int i, j, k;
	operandType a1, a2, a3;
	for (i = block_begin[index]; i < block_begin[index + 1]; i++)
	{
		if (midcodeTable[i].src1.auxPara == 3)
		{
			a1.typeNum = 3;
			a1.value = midcodeTable[i].src1.auxParaValue;
			a1.auxPara = 0;
			a1.auxParaValue = 0;
			k = findInNavi(a1);
			DAGDiagram[DAGNavi[k].no].isMid = true;
			if (DAGDiagram[DAGNavi[k].no].op == NNN)
			{
				DAGDiagram[DAGNavi[k].no].op = ASS;
			}
		}

		if (midcodeTable[i].src2.auxPara == 3)
		{
			a1.typeNum = 3;
			a1.value = midcodeTable[i].src2.auxParaValue;
			a1.auxPara = 0;
			a1.auxParaValue = 0;
			k = findInNavi(a1);
			DAGDiagram[DAGNavi[k].no].isMid = true;
			if (DAGDiagram[DAGNavi[k].no].op == NNN)
			{
				DAGDiagram[DAGNavi[k].no].op = ASS;
			}
		}

		if (midcodeTable[i].des.auxPara == 3)
		{
			a1.typeNum = 3;
			a1.value = midcodeTable[i].des.auxParaValue;
			a1.auxPara = 0;
			a1.auxParaValue = 0;
			k = findInNavi(a1);
			DAGDiagram[DAGNavi[k].no].isMid = true;
			if (DAGDiagram[DAGNavi[k].no].op == NNN)
			{
				DAGDiagram[DAGNavi[k].no].op = ASS;
			}
		}
	}
}