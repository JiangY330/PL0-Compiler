#include "FinalcodeProducerOP.h"

IdNaviItem IdNavi[100];
int IdNavi_num;
MemPoolItem MemPool[6];

void FinalcodeProducerOP()
{
	FinalcodeProducerOPinit();
	int tempTable[1000];
	memset(tempTable, 0, sizeof(tempTable));
	fout << ".386                  " << endl;
	fout << ".model flat, stdcall  " << endl;
	fout << "option casemap :none  " << endl;
	fout << "                      " << endl;
	fout << "include msvcrt.inc    " << endl;
	fout << "includelib msvcrt.lib " << endl;
	fout << "                      " << endl;
	fout << ".data                 " << endl;
	fout << "strFmt db '%s', 0" << endl;
	fout << "intFmt db '%d', 0" << endl;
	fout << "chaFmt db '%c', 0" << endl;
	fout << "t1 dd 10" << endl;

	for (int i = 0; i < strIndex; i++)
	{
		fout << "str" << i << " db \"" << strTable[i] << "\", 0" << endl;
	}

	fout << ".code                          " << endl;
	for (int j = levelTableIndex - 1; j >= 0; j--)
	{
		if (j != 0)
		{
			fout << "proce_" << j << " PROC" << endl;
		}
		else
		{
			fout << "start:" << endl;
		}

		fout << "push ebp" << endl;
		fout << "mov ebp,esp" << endl;
		int offset = 0;
		for (int k = levelTable[j].symbolAddress + levelTable[j].constNum; k < levelTable[j].symbolAddress + levelTable[j].constNum + levelTable[j].varNum; k++)
		{
			if (symbolTable[k].length == 0)
			{
				offset++;
			}
			else
			{
				offset += symbolTable[k].length;
			}
		}
		fout << "sub esp," << offset * 4 + counttmp(j, offset) + 8 << "d" << endl;
		fout << "mov [ebp - " << offset * 4 + 4 << "],esi" << endl;
		fout << "mov [ebp - " << offset * 4 + 8 << "],edi" << endl;

		if (!operandTypeEqual(nop, levelTable[j].mem[0]))
		{
			if (levelTable[j].mem[0].typeNum == 1)
			{
				fout << "mov esi," << levelTable[j].mem[0].value << "d" << endl;
			}
			else if (levelTable[j].mem[0].typeNum == 4)
			{
				if (levelTable[j].mem[0].auxPara == 0)
				{
					if (levelTable[j].mem[0].value >= 0)
						fout << "mov esi,[ebp-" << levelTable[j].mem[0].value * 4 << "d]" << endl;
					else
						fout << "mov esi,[ebp+" << (levelTable[j].mem[0].value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
				}
				else if (levelTable[j].mem[0].auxPara == 1)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					fout << "mov esi,[ebx]" << endl;
				}
				else if (levelTable[j].mem[0].auxPara == 3)
				{
					fout << "mov ebx,ebp" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "mov esi,[ebx-" << levelTable[j].mem[0].value * 4 << "d]" << endl;
				}

			}
			else if (levelTable[j].mem[0].typeNum == 3)
			{
				fout << "mov esi,[ebp-" << valueMem[levelTable[j].mem[0].value] << "]" << endl;
			}
			else
			{
				if (levelTable[j].mem[0].auxPara == 0)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].typeNum - 7 + 2) * 4 << "d]" << endl;
					fout << "mov esi,[ebx-" << levelTable[j].mem[0].value * 4 << "]" << endl;
				}
				else if (levelTable[j].mem[0].auxPara == 1)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].typeNum - 7 + 2) * 4 << "d]" << endl;
					fout << "mov ecx,[ebx+" << (levelTable[j].mem[0].value - levelTable[j].levelNum + levelTable[j].mem[0].typeNum - 9) * -4 << "d]" << endl;
					fout << "mov esi,[ecx]" << endl;
				}
				else if (levelTable[j].mem[0].auxPara == 3)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].typeNum - 7 + 2) * 4 << "d]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
					fout << "mov esi,[ebx-" << levelTable[j].mem[0].value * 4 << "]" << endl;

				}

			}
		}

		if (!operandTypeEqual(nop, levelTable[j].mem[1]))
		{
			if (levelTable[j].mem[1].typeNum == 1)
			{
				fout << "mov edi," << levelTable[j].mem[1].value << "d" << endl;
			}
			else if (levelTable[j].mem[1].typeNum == 4)
			{
				if (levelTable[j].mem[1].auxPara == 0)
				{
					if (levelTable[j].mem[1].value >= 0)
						fout << "mov edi,[ebp-" << levelTable[j].mem[1].value * 4 << "d]" << endl;
					else
						fout << "mov edi,[ebp+" << (levelTable[j].mem[1].value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
				}
				else if (levelTable[j].mem[1].auxPara == 1)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					fout << "mov edi,[ebx]" << endl;
				}
				else if (levelTable[j].mem[1].auxPara == 3)
				{
					fout << "mov ebx,ebp" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "mov edi,[ebx-" << levelTable[j].mem[1].value * 4 << "d]" << endl;
				}

			}
			else if (levelTable[j].mem[1].typeNum == 3)
			{
				fout << "mov edi,[ebp-" << valueMem[levelTable[j].mem[1].value] << "]" << endl;
			}
			else
			{
				if (levelTable[j].mem[1].auxPara == 0)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].typeNum - 7 + 2) * 4 << "d]" << endl;
					fout << "mov edi,[ebx-" << levelTable[j].mem[1].value * 4 << "]" << endl;
				}
				else if (levelTable[j].mem[1].auxPara == 1)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].typeNum - 7 + 2) * 4 << "d]" << endl;
					fout << "mov ecx,[ebx+" << (levelTable[j].mem[1].value - levelTable[j].levelNum + levelTable[j].mem[1].typeNum - 9) * -4 << "d]" << endl;
					fout << "mov edi,[ecx]" << endl;
				}
				else if (levelTable[j].mem[1].auxPara == 3)
				{
					fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].typeNum - 7 + 2) * 4 << "d]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
					fout << "mov edi,[ebx-" << levelTable[j].mem[1].value * 4 << "]" << endl;

				}

			}
		}

		for (int i = levelTable[j].entranceAddress; i < levelTable[j].exitAddress; i++)
		{
			fout << "pc" << i << ":" << endl;
			switch (OPmidcodeTable[i].op)
			{
			case ADD:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}

				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}

				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "add eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "add eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "add eax," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "add eax,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "add eax,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "add eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "add eax,[ebx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					fout << "add eax,ebx" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "add eax,[ebx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "add eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "add eax,[ebx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}


				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}
			case SUB:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "sub eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "sub eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "sub eax," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "sub eax,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "sub eax,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "sub eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub eax,[ebx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					fout << "sub eax,ebx" << endl;
					//fout<<"mov eax,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub eax,[ebx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "sub eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub eax,[ebx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}
			case MUL:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ecx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ecx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ecx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ecx, [ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ecx, [ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ecx, [ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ecx, [ebx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov edx,[ecx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ecx, [edx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ecx, [ebx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}

				fout << "mul ecx" << endl;

				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}
			case DIVI:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}


				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}

				fout << "mov edx,0" << endl;
				fout << "idiv ebx" << endl;

				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}
			case ASS:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else if (OPmidcodeTable[i].des.typeNum == 7)
				{
					fout << "mov [ebp+12d],eax" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}
			case JE:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}
				fout << "cmp eax,ebx" << endl;
				fout << "je pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case JG:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}
				fout << "cmp eax,ebx" << endl;
				fout << "jg pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case JGE:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}
				fout << "cmp eax,ebx" << endl;
				//fout<<"cmp ebx,0"<<endl;
				fout << "jge pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case JL:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}
				fout << "cmp eax,ebx" << endl;
				fout << "jl pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case JLE:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}
				fout << "cmp eax,ebx" << endl;
				//fout<<"cmp ebx,0"<<endl;
				fout << "jle pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case JMP:
			{
				fout << "jmp pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case JNE:
			{
				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[0]))
				{
					fout << "mov ebx,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src2, levelTable[j].mem[1]))
				{
					fout << "mov ebx,edi" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << OPmidcodeTable[i].src2.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src2.typeNum == 4)
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						if (OPmidcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (OPmidcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[OPmidcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (OPmidcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src2.value - levelTable[j].levelNum + OPmidcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (OPmidcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[OPmidcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << OPmidcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}
				fout << "cmp eax,ebx" << endl;
				fout << "jne pc" << OPmidcodeTable[i].des.value << endl;
				break;
			}
			case WRITE://È±¸ñÊ½
			{
				char* ty = "intFmt";
				if (OPmidcodeTable[i].src2.typeNum == 1)
				{
					ty = "chaFmt";
				}

				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "invoke crt_printf, addr " << ty << ",esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "invoke crt_printf, addr " << ty << ",edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 5)
				{
					fout << "invoke crt_printf, addr strFmt,offset str" << OPmidcodeTable[i].src1.value << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "invoke crt_printf, addr " << ty << "," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
							fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
						}
						else
						{
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
							fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
						}
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
						fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
					}

				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
					fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
						fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
						fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
						fout << "invoke crt_printf, addr " << ty << ",eax" << endl;
					}
				}
				break;
			}
			case END:
			{
				//fout<<"ret"<<endl;
				break;
			}
			case RET:
			{
				if (!operandTypeEqual(nop, levelTable[j].mem[0]))
				{
					if (levelTable[j].mem[0].typeNum == 3)
					{
						fout << "mov [ebp-" << valueMem[levelTable[j].mem[0].value] << "],esi" << endl;
					}
					else if (levelTable[j].mem[0].typeNum == 4)
					{
						if (levelTable[j].mem[0].auxPara == 0)
						{
							if (levelTable[j].mem[0].value >= 0)
								fout << "mov [ebp-" << levelTable[j].mem[0].value * 4 << "d],esi" << endl;
							else
								fout << "mov [ebp+" << (levelTable[j].mem[0].value - levelTable[j].levelNum - 2) * -4 << "d],esi" << endl;
						}
						else if (levelTable[j].mem[0].auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
							fout << "mov [ebx],esi" << endl;
						}
						else if (levelTable[j].mem[0].auxPara == 3)
						{
							fout << "mov ebx,ebp" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "mov [ebx-" << levelTable[j].mem[0].value * 4 << "d],esi" << endl;
						}
					}
					else
					{
						if (levelTable[j].mem[0].auxPara == 0)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov [ebx-" << levelTable[j].mem[0].value * 4 << "],esi" << endl;
						}
						else if (levelTable[j].mem[0].auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov ecx,[ebx+" << (levelTable[j].mem[0].value - levelTable[j].levelNum + levelTable[j].mem[0].typeNum - 9) * -4 << "d]" << endl;
							fout << "mov [ecx],esi" << endl;
						}
						else if (levelTable[j].mem[0].auxPara == 3)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[0].typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[0].auxParaValue] << "]" << endl;
							fout << "mov [ebx-" << levelTable[j].mem[0].value * 4 << "],esi" << endl;
						}
					}
				}
				if (!operandTypeEqual(nop, levelTable[j].mem[1]))
				{
					if (levelTable[j].mem[1].typeNum == 3)
					{
						fout << "mov [ebp-" << valueMem[levelTable[j].mem[1].value] << "],edi" << endl;
					}
					else if (levelTable[j].mem[1].typeNum == 4)
					{
						if (levelTable[j].mem[1].auxPara == 0)
						{
							if (levelTable[j].mem[1].value >= 0)
								fout << "mov [ebp-" << levelTable[j].mem[1].value * 4 << "d],edi" << endl;
							else
								fout << "mov [ebp+" << (levelTable[j].mem[1].value - levelTable[j].levelNum - 2) * -4 << "d],edi" << endl;
						}
						else if (levelTable[j].mem[1].auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
							fout << "mov [ebx],edi" << endl;
						}
						else if (levelTable[j].mem[1].auxPara == 3)
						{
							fout << "mov ebx,ebp" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "mov [ebx-" << levelTable[j].mem[1].value * 4 << "d],edi" << endl;
						}
					}
					else
					{
						if (levelTable[j].mem[1].auxPara == 0)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov [ebx-" << levelTable[j].mem[1].value * 4 << "],edi" << endl;
						}
						else if (levelTable[j].mem[1].auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov ecx,[ebx+" << (levelTable[j].mem[1].value - levelTable[j].levelNum + levelTable[j].mem[1].typeNum - 9) * -4 << "d]" << endl;
							fout << "mov [ecx],edi" << endl;
						}
						else if (levelTable[j].mem[1].auxPara == 3)
						{
							fout << "mov ebx,[ebp+" << (levelTable[j].mem[1].typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[levelTable[j].mem[1].auxParaValue] << "]" << endl;
							fout << "mov [ebx-" << levelTable[j].mem[1].value * 4 << "],edi" << endl;
						}
					}
				}
				fout << "mov esi,[ebp - " << offset * 4 + 4 << "]" << endl;
				fout << "mov edi,[ebp - " << offset * 4 + 8 << "]" << endl;
				fout << "mov esp,ebp" << endl;

				fout << "pop ebp" << endl;
				fout << "ret " << endl;
				break;
			}
			case  READ:
			{
				if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					if (OPmidcodeTable[i].src1.value == 1)
					{
						fout << "invoke crt_scanf,  addr chaFmt, addr t1" << endl;
					}
					else
					{
						fout << "invoke crt_scanf,  addr intFmt, addr t1" << endl;
					}
				}

				fout << "mov eax,t1" << endl;

				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else if (OPmidcodeTable[i].des.typeNum == 7)
				{
					fout << "mov [ebp+12d],eax" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}
			case PUD:
			{
				if (OPmidcodeTable[i].src1.value == 0)
				{
					fout << "push ebp" << endl;
				}
				else
				{
					fout << "push [ebp+" << (OPmidcodeTable[i].src1.value + 2) * 4 << "]" << endl;
				}
				break;
			}
			case PUSH:
			{
				if (OPmidcodeTable[i].src2.typeNum == 0)
				{
					if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
					{
						fout << "push esi" << endl;
					}
					else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
					{
						fout << "push edi" << endl;
					}
					else if (OPmidcodeTable[i].src1.typeNum == 0)
					{
						fout << "sub esp,4" << endl;
					}
					else if (OPmidcodeTable[i].src1.typeNum == 1)
					{
						fout << "push " << OPmidcodeTable[i].src1.value << "d" << endl;
					}
					else if (OPmidcodeTable[i].src1.typeNum == 4)
					{
						if (OPmidcodeTable[i].src1.auxPara == 0)
						{
							if (OPmidcodeTable[i].src1.value >= 0)
								fout << "push [ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
							else
								fout << "push [ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
							fout << "push [ebx]" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx,ebp" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "push [ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						}
					}
					else if (OPmidcodeTable[i].src1.typeNum == 3)
					{
						fout << "push [ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
					}
					else
					{
						if (OPmidcodeTable[i].src1.auxPara == 0)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "push [ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
							fout << "push [ecx]" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "push [ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
						}
					}
				}
				else
				{
					if (OPmidcodeTable[i].src1.typeNum == 0)
					{
						fout << "sub esp,4" << endl;
					}
					else if (OPmidcodeTable[i].src1.typeNum == 1)
					{
						fout << "push " << OPmidcodeTable[i].src1.value << "d" << endl;
					}
					else if (OPmidcodeTable[i].src1.typeNum == 4)
					{
						if (OPmidcodeTable[i].src1.auxPara == 0)
						{
							if (OPmidcodeTable[i].src1.value >= 0)
							{
								fout << "mov ebx,ebp" << endl;
								fout << "sub ebx," << OPmidcodeTable[i].src1.value * 4 << "d" << endl;
								fout << "push ebx" << endl;
							}
							else
							{
								fout << "mov ebx,ebp" << endl;
								fout << "add ebx," << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d" << endl;
								fout << "push ebx" << endl;
							}
						}
						else if (OPmidcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
							fout << "push ebx" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx,ebp" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx," << OPmidcodeTable[i].src1.value * 4 << "d" << endl;
							fout << "push ebx" << endl;
						}
					}
					else if (OPmidcodeTable[i].src1.typeNum == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx," << valueMem[OPmidcodeTable[i].src1.value] << endl;
						fout << "push ebx" << endl;
					}
					else
					{
						if (OPmidcodeTable[i].src1.auxPara == 0)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx," << OPmidcodeTable[i].src1.value * 4 << endl;
							fout << "push ebx" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
							fout << "push ecx" << endl;
						}
						else if (OPmidcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx," << OPmidcodeTable[i].src1.value * 4 << endl;
							fout << "push ebx" << endl;
						}
					}
				}

				break;
			}
			case POP:
			{
				if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "add esp," << OPmidcodeTable[i].src1.value * 4 << endl;
				}
				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "pop esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "pop edi" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "pop eax" << endl;
					fout << "pop eax" << endl;
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				break;
			}
			case CALL:
			{
				fout << "call proce_" << OPmidcodeTable[i].src1.value << endl;
				break;
			}
			case NEG:
			{

				if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[0]))
				{
					fout << "mov eax,esi" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].src1, levelTable[j].mem[1]))
				{
					fout << "mov eax,edi" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << OPmidcodeTable[i].src1.value << "d" << endl;
				}
				else if (OPmidcodeTable[i].src1.typeNum == 4)
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						if (OPmidcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "d]" << endl;
					}

				}
				else if (OPmidcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[OPmidcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (OPmidcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].src1.value - levelTable[j].levelNum + OPmidcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (OPmidcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << OPmidcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				fout << "neg eax" << endl;

				if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[0]))
				{
					fout << "mov esi,eax" << endl;
				}
				else if (operandTypeEqual(OPmidcodeTable[i].des, levelTable[j].mem[1]))
				{
					fout << "mov edi,eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[OPmidcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (OPmidcodeTable[i].des.typeNum == 4)
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						if (OPmidcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (OPmidcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (OPmidcodeTable[i].des.value - levelTable[j].levelNum + OPmidcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (OPmidcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (OPmidcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[OPmidcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << OPmidcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
				break;
			}
			default:
				break;
			}
		}
		//fout<<"sub esp,"<<offset * 4<<"d"<<endl;


		if (j != 0)
		{
			fout << "proce_" << j << " ENDP" << endl;
		}
		else
		{
			fout << "end start" << endl;
		}
	}
}

void FinalcodeProducerOPinit()
{
	int i, j, k, l = 0;;
	int stack[1000];
	memset(stack, 0, sizeof(stack));
	for (i = 0; i < pc1; i++)
	{
		if (OPmidcodeTable[i].src1.typeNum == 3)
		{
			stack[l++] = OPmidcodeTable[i].src1.value;
		}
		if (OPmidcodeTable[i].src2.typeNum == 3)
		{
			stack[l++] = OPmidcodeTable[i].src2.value;
		}
		if (OPmidcodeTable[i].des.typeNum == 3)
		{
			stack[l++] = OPmidcodeTable[i].des.value;
		}
		if (OPmidcodeTable[i].src1.auxPara == 3)
		{
			stack[l++] = OPmidcodeTable[i].src1.auxParaValue;
		}
		if (OPmidcodeTable[i].src2.auxPara == 3)
		{
			stack[l++] = OPmidcodeTable[i].src2.auxParaValue;
		}
		if (OPmidcodeTable[i].des.auxPara == 3)
		{
			stack[l++] = OPmidcodeTable[i].des.auxParaValue;
		}
	}
	for (i = 0; i < l; i++)
	{
		for (j = i + 1; j <l; j++)
		{
			if (stack[i] > stack[j])
			{
				k = stack[i];
				stack[i] = stack[j];
				stack[j] = k;
			}
			else if (stack[i] == stack[j])
			{
				stack[j] = stack[--l];
				j--;
			}
		}
	}
	for (i = 0; i < pc1; i++)
	{
		if (OPmidcodeTable[i].src1.typeNum == 3)
		{
			for (j = 0; j < l; j++)
			{
				if (OPmidcodeTable[i].src1.value == stack[j])
				{
					OPmidcodeTable[i].src1.value = j;
					break;
				}
			}
		}
		if (OPmidcodeTable[i].src2.typeNum == 3)
		{
			for (j = 0; j < l; j++)
			{
				if (OPmidcodeTable[i].src2.value == stack[j])
				{
					OPmidcodeTable[i].src2.value = j;
					break;
				}
			}
		}
		if (OPmidcodeTable[i].des.typeNum == 3)
		{
			for (j = 0; j < l; j++)
			{
				if (OPmidcodeTable[i].des.value == stack[j])
				{
					OPmidcodeTable[i].des.value = j;
					break;
				}
			}
		}
		if (OPmidcodeTable[i].src1.auxPara == 3)
		{
			for (j = 0; j < l; j++)
			{
				if (OPmidcodeTable[i].src1.auxParaValue == stack[j])
				{
					OPmidcodeTable[i].src1.auxParaValue = j;
					break;
				}
			}
		}
		if (OPmidcodeTable[i].src2.auxPara == 3)
		{
			for (j = 0; j < l; j++)
			{
				if (OPmidcodeTable[i].src2.auxParaValue == stack[j])
				{
					OPmidcodeTable[i].src2.auxParaValue = j;
					break;
				}
			}
		}
		if (OPmidcodeTable[i].des.auxPara == 3)
		{
			for (j = 0; j < l; j++)
			{
				if (OPmidcodeTable[i].des.auxParaValue == stack[j])
				{
					OPmidcodeTable[i].des.auxParaValue = j;
					break;
				}
			}
		}
	}
}

int counttmp(int index, int offset)
{
	int i, j, k;
	int stack[1000];
	int l = 0;
	bool b;
	memset(stack, 0, sizeof(stack));
	for (i = levelTable[index].entranceAddress; i < levelTable[index].exitAddress; i++)
	{
		if (OPmidcodeTable[i].src1.typeNum == 3)
		{
			b = false;
			for (j = 0; j < l; j++)
			{
				if (stack[j] == OPmidcodeTable[i].src1.value)
				{
					b = true;
				}
			}
			if (!b)
				stack[l++] = OPmidcodeTable[i].src1.value;
		}
		if (OPmidcodeTable[i].src2.typeNum == 3)
		{
			b = false;
			for (j = 0; j < l; j++)
			{
				if (stack[j] == OPmidcodeTable[i].src2.value)
				{
					b = true;
				}
			}
			if (!b)
				stack[l++] = OPmidcodeTable[i].src2.value;
		}
		if (OPmidcodeTable[i].des.typeNum == 3)
		{
			b = false;
			for (j = 0; j < l; j++)
			{
				if (stack[j] == OPmidcodeTable[i].des.value)
				{
					b = true;
				}
			}
			if (!b)
				stack[l++] = OPmidcodeTable[i].des.value;
		}
	}

	for (i = 0; i <l; i++)
	{
		valueMem[stack[i]] = (i + 1 + offset + 2) * 4;
	}
	return l * 4;
}

void initIdNavi(int index)
{
	int i, j, k;
	for (i = levelTable[index].entranceAddress; i < levelTable[index].exitAddress; i++)
	{
		if (findInIdNavi(OPmidcodeTable[i].src1) == -1)
		{
			insertIdNavi(OPmidcodeTable[i].src1, index);
		}
		if (findInIdNavi(OPmidcodeTable[i].src2) == -1)
		{
			insertIdNavi(OPmidcodeTable[i].src2, index);
		}
		if (findInIdNavi(OPmidcodeTable[i].des) == -1)
		{
			insertIdNavi(OPmidcodeTable[i].des, index);
		}
	}
}

int findInIdNavi(operandType x)
{
	for (int i = 0; i < IdNavi_num; i++)
	{
		if (operandTypeEqual(x, IdNavi[i].item))
		{
			return i;
		}
	}
	return -1;
}

void insertIdNavi(operandType x, int j)
{
	IdNavi[IdNavi_num].item = x;
	if (x.typeNum == 1)
	{
		IdNavi[IdNavi_num++].value = itost(x.value);
	}
	else if (x.typeNum == 4)
	{
		if (x.auxPara == 0)
		{
			if (x.value >= 0)
			{
				IdNavi[IdNavi_num++].value = "[ebp-" + itost(x.value * 4) + "d]";
			}
			else
				IdNavi[IdNavi_num++].value = "[ebp+" + itost((x.value - levelTable[j].levelNum - 2) * -4) + "d]";
		}
		else if (x.auxPara == 1)
		{
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "mov edx,[ebp+" + itost((x.value - levelTable[j].levelNum - 2) * -4) + "d]";
			IdNavi[IdNavi_num++].value = "[edx]";
		}
		else if (x.auxPara == 3)
		{
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "mov edx,ebp";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num++].value = "[edx-" + itost(x.value * 4) + "d]";
		}

	}
	else if (x.typeNum == 3)
	{
		IdNavi[IdNavi_num++].value = "[ebp-" + itost(valueMem[x.value]) + "]";
	}
	else
	{
		if (x.auxPara == 0)
		{
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "mov edx,[ebp+" + itost((x.typeNum - 7 + 2) * 4) + "d]";
			IdNavi[IdNavi_num++].value = "[edx-" + itost(x.value * 4) + "]";
		}
		else if (x.auxPara == 1)
		{
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "mov edx,[ebp+" + itost((x.typeNum - 7 + 2) * 4) + "d]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "mov edx,[edx+" + itost((x.value - levelTable[j].levelNum + x.typeNum - 9) * -4) + "d]";
			IdNavi[IdNavi_num++].value = "[edx]";
		}
		else if (x.auxPara == 3)
		{
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "mov edx,[ebp+" + itost((x.typeNum - 7 + 2) * 4) + "d]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num].preOp[IdNavi[IdNavi_num].prev++] = "sub edx,[ebp-" + itost(valueMem[x.auxParaValue]) + "]";
			IdNavi[IdNavi_num++].value = "[edx-" + itost(x.value * 4) + "]";

		}

	}
}

string itost(int x)
{
	stringstream s;
	s.clear();
	s << x;
	return s.str();
}

void initMemPool()
{
	memset(MemPool, 0, sizeof(MemPool));
	MemPool[0].mem = "eax";
	MemPool[1].mem = "ebx";
	MemPool[2].mem = "ecx";
	MemPool[3].mem = "esi";
	MemPool[4].mem = "edi";
}

int insertMemPool(int index)
{
	int i, j, k;
	for (i = 0; i < 5; i++)
	{
		if (!MemPool[i].isUse)
		{
			MemPool[i].isUse = true;
			MemPool[i].item = IdNavi[index].item;
			return i;
		}
	}
	k = index % 5;
	j = findInIdNavi(MemPool[k].item);
	for (i = 0; i < IdNavi[j].prev; i++)
	{
		fout << IdNavi[j].preOp[i] << endl;
	}
	fout << "mov " << IdNavi[j].value << "," << MemPool[k].mem << endl;
	for (i = 0; i < IdNavi[index].prev; i++)
	{
		fout << IdNavi[index].preOp[i] << endl;
	}
	fout << "mov " << MemPool[k].mem << "," << IdNavi[index].value << endl;
	MemPool[k].item = IdNavi[index].item;
	return k;
}

int findInMemPool(operandType x)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (operandTypeEqual(MemPool[i].item, x))
		{
			return i;
		}
	}
	return -1;
}