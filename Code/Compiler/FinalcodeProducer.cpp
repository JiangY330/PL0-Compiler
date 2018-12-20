#include "FinalcodeProducer.h"

void FinalcodeProducer()
{
	int tempTable[1000];

	memset(tempTable, 0, sizeof(tempTable));
	fout << ".386                     " << endl;
	fout << ".model flat, stdcall     " << endl;
	fout << "option casemap : none    " << endl;
	fout << "                         " << endl;
	fout << "include msvcrt.inc       " << endl;
	fout << "includelib msvcrt.lib    " << endl;
	fout << "                         " << endl;
	fout << ".data                    " << endl;
	fout << "strFmt db '%s', 0" << endl;
	fout << "intFmt db '%d', 0" << endl;
	fout << "chaFmt db ' %c', 0" << endl;  //ºöÂÔÁËËùÓÐ¿Õ°××Ö·û
	fout << "t1 dd 10" << endl;

	for (int i = 0; i < strIndex; i++)
	{
		fout << "str" << i << " db \"" << strTable[i] << "\", 0" << endl;
	}

	fout << ".code                     " << endl;
	for (int j = levelTableIndex - 1; j >= 0; j--)
	{
		if (j != 0)  //非主函数，是过程或者函数
		{
			fout << "proce_" << j << " PROC" << endl;
		}
		else
		{
			fout << "start:" << endl;
		}

		fout << "push ebp" << endl;
		fout << "mov ebp, esp" << endl;

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
		fout << "sub esp, " << offset * 4 + CountTemp(j, offset) << "d" << endl;

		for (int i = levelTable[j].entranceAddress; i < levelTable[j].exitAddress; i++)
		{
			fout << "pc" << i << ":" << endl;
			switch (midcodeTable[i].op)
			{

			case ADD:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "add eax, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "add eax, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "add eax, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "add eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "add ebx, [ebx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
					fout << "add eax, ebx" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "add eax, [ebx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "add eax, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "add eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "add eax, [ebx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp - " << valueMem[midcodeTable[i].des.value] << "] , eax" << endl;
				}
				else if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						if (midcodeTable[i].des.value >= 0)
						{
							fout << "mov [ebp - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d],eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov [ebx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
					}
				}
				else
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
						}
						else
						{
							fout << "mov [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov [ecx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
					}
				}
				break;
			}

			case SUB:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
 					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "sub eax, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "sub eax, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "sub eax, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "sub eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub eax, [ebx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
					fout << "sub eax, ebx" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "sub eax, [ebx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "sub eax, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [evp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "sub eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub eax, [ebx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp - " << valueMem[midcodeTable[i].des.value] << "], eax" << endl;
				}
				else if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						if (midcodeTable[i].des.auxPara == 0)
						{
							fout << "mov [ebp - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
						}
						else
						{
							fout << "mov [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxParaValue == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov [ebx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov [ebx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
					}
				}
				else
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
						}
						else
						{
							fout << "mov [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov [ecx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
					}
				}
				break;
			}

			case MUL:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara== 0)
					{
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << midcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara== 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara== 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara== 0)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebx-" << midcodeTable[i].src1.value * 4 << "]" << endl;
						else
							fout << "mov eax,[ebx+" << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara== 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara== 3)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << midcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mul " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara== 0)
					{
						if (midcodeTable[i].src2.value >= 0)
							fout << "mul [ebp-" << midcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mul [ebp+" << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara== 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mul [ebx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara== 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mul [ebx-" << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[midcodeTable[i].src2.value] << "]" << endl;
					fout << "mul ebx" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara== 0)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
							fout << "mul [ebx-" << midcodeTable[i].src2.value * 4 << "]" << endl;
						else
							fout << "mul [ebx+" << (midcodeTable[i].src2.value - levelTable[j].levelNum - 1) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara== 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mul [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara== 3)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mul [ebx-" << midcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}

				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[midcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara== 0)
					{
						if (midcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << midcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara== 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara== 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << midcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (midcodeTable[i].des.auxPara== 0)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov [ebx-" << midcodeTable[i].des.value * 4 << "],eax" << endl;
						else
							fout << "mov [ebx+" << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * -4 << "d],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara== 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara== 3)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << midcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}

			case DIVI:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax," << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebp-" << midcodeTable[i].src1.value * 4 << "d]" << endl;
						else
							fout << "mov eax,[ebp+" << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov eax,[ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax,[ebp-" << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov eax,[ebx-" << midcodeTable[i].src1.value * 4 << "]" << endl;
						else
							fout << "mov eax,[ebx+" << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov eax,[ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax,[ebx-" << midcodeTable[i].src1.value * 4 << "]" << endl;

					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx," << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
							fout << "mov ebx,[ebp-" << midcodeTable[i].src2.value * 4 << "d]" << endl;
						else
							fout << "mov ebx,[ebp+" << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx,[ebp+" << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,ebp" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp-" << valueMem[midcodeTable[i].src2.value] << "]" << endl;
					//fout<<"mov ebx,ebx"<<endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx,[ebp+" << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov ebx,[ecx-" << midcodeTable[i].src2.value * 4 << "]" << endl;
						else
							fout << "mov ebx,[ecx+" << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov ebx,[ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx,[ebp+" << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx,[ebp-" << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx,[ecx-" << midcodeTable[i].src2.value * 4 << "]" << endl;

					}
				}

				fout << "mov edx,0" << endl;
				fout << "idiv ebx" << endl;

				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp-" << valueMem[midcodeTable[i].des.value] << "],eax" << endl;
				}
				else if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						if (midcodeTable[i].des.value >= 0)
							fout << "mov [ebp-" << midcodeTable[i].des.value * 4 << "d],eax" << endl;
						else
							fout << "mov [ebp+" << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * -4 << "d]" << endl;
						fout << "mov [ebx],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,ebp" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << midcodeTable[i].des.value * 4 << "d],eax" << endl;
					}
				}
				else
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
							fout << "mov [ebx-" << midcodeTable[i].des.value * 4 << "],eax" << endl;
						else
							fout << "mov [ebx+" << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * -4 << "d],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx,[ebx+" << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * -4 << "d]" << endl;
						fout << "mov [ecx],eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx,[ebp+" << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx,[ebp-" << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx-" << midcodeTable[i].des.value * 4 << "],eax" << endl;
					}
				}
				break;
			}

			case ASS:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp - " << valueMem[midcodeTable[i].des.value] << "], eax" << endl;
				}
				else if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						if (midcodeTable[i].des.value >= 0)
						{
							fout << "mov [ebp - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
						}
						else
						{
							fout << "mov [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov [ebx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
					}
				}
				else if (midcodeTable[i].des.typeNum == 7)
				{
					fout << "mov [ebp + 12d], eax" << endl;
				}
				else
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov [ebx - " << (midcodeTable[i].des.value * 4) << "], eax" << endl;
						}
						else
						{
							fout << "mov [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov [ecx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
					}
				}
				break;
			}

			case JE:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 3) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov eca, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "mov ebx, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx,[ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov ebx, [ecx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}
				fout << "cmp eax, ebx" << endl;
				fout << "je pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case JG:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "mov ebx, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov ebx, [ecx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}
				fout << "cmp eax, ebx" << endl;
				fout << "jg pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case JGE:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov bex, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "mov ebx, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov ebx, [ecx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}
				fout << "cmp eax, ebx" << endl;
				fout << "jge pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case JL:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.auxPara == 0)
						{
							fout << "mov ebx, [ebp + " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "mov ebx, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov ebx, [ecx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}
				fout << "cmp eax, ebx" << endl;
				fout << "jl pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case JLE:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d]" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax,[ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov ecx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "mov ebx, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov ebx, [ecx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}
				fout << "cmp eax, ebx" << endl;
				fout << "jle pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case JMP:
			{
				fout << "jmp pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case JNE:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				if (midcodeTable[i].src2.typeNum == 1)
				{
					fout << "mov ebx, " << midcodeTable[i].src2.value << "d" << endl;
				}
				else if (midcodeTable[i].src2.typeNum == 4)
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						if (midcodeTable[i].src2.value >= 0)
						{
							fout << "mov ebx, [ebp - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov ebx, [evp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, ebp" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src2.typeNum == 3)
				{
					fout << "mov ebx, [ebp - " << valueMem[midcodeTable[i].src2.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src2.auxPara == 0)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov ebx, [ecx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src2.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src2.value - levelTable[j].levelNum + midcodeTable[i].src2.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov ebx, [ecx]" << endl;
					}
					else if (midcodeTable[i].src2.auxPara == 3)
					{
						fout << "mov ecx, [ebp + " << (midcodeTable[i].src2.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "sub ecx, [ebp - " << valueMem[midcodeTable[i].src2.auxParaValue] << "]" << endl;
						fout << "mov ebx, [ecx - " << midcodeTable[i].src2.value * 4 << "]" << endl;
					}
				}
				fout << "cmp eax, ebx" << endl;
				fout << "jne pc" << midcodeTable[i].des.value << endl;
				break;
			}

			case WRITE:
			{
				char* ty = "intFmt";

				if (midcodeTable[i].src2.typeNum == 1)
				{
					ty = "chaFmt";
				}
				if (midcodeTable[i].src1.typeNum == 5)
				{
					fout << "invoke crt_printf, addr strFmt, offset str" << midcodeTable[i].src1.value << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "invoke crt_printf, addr " << ty << ", " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
							fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
							fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
						fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
					fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
						fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
						fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						fout << "invoke crt_printf, addr " << ty << ", eax" << endl;
					}
				}
				break;
			}

			case END:
			{
				break;
			}

			case RET:
			{
				fout << "mov esp, ebp" << endl;
				fout << "pop ebp" << endl;
				fout << "ret" << endl;
				break;
			}

			case READ:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					if (midcodeTable[i].src1.value == 1)
					{
						fout << "invoke crt_scanf, addr chaFmt, addr t1" << endl;
					}
					else
					{
						fout << "invoke crt_scanf, addr intFmt, addr t1" << endl;
						//fout << "invoke crt_fflush" << endl;
					}
				}

				fout << "mov eax, t1" << endl;

				if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						if (midcodeTable[i].des.value >= 0)
						{
							fout << "mov [ebp - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
						}
						else
						{
							fout << "mov [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov [ebx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
					}
				}
				else if (midcodeTable[i].des.typeNum == 7)
				{
					fout << "mov [ebp + 12d], eax" << endl;
				}
				else
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
						}
						else
						{
							fout << "mov [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov [ecx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
					}
				}
				break;
			}

			case PUD:
			{
				if (midcodeTable[i].src1.value == 0)
				{
					fout << "push ebp" << endl;
				}
				else
				{
					fout << "push [ebp + " << (midcodeTable[i].src1.value + 2) * 4 << "]" << endl;
				}
				break;
			}

			case PUSH:
			{
				if (midcodeTable[i].src2.typeNum == 0)
				{
					if (midcodeTable[i].src1.typeNum == 0)
					{
						fout << "sub esp, 4" << endl;
					}
					else if (midcodeTable[i].src1.typeNum == 1)
					{
						fout << "push " << midcodeTable[i].src1.value << "d" << endl;
					}
					else if (midcodeTable[i].src1.typeNum == 4)
					{
						if (midcodeTable[i].src1.auxPara == 0)
						{
							if (midcodeTable[i].src1.value >= 0)
							{
								fout << "push [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
							}
							else
							{
								fout << "push [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
							}
						}
						else if (midcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
							fout << "push [ebx]" << endl;
						}
						else if (midcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx, ebp" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "push [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.typeNum == 3)
					{
						fout << "push [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
					}
					else
					{
						if (midcodeTable[i].src1.auxPara == 0)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							if (midcodeTable[i].src1.value >= 0)
							{
								fout << "push [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
							}
							else
							{
								fout << "push [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
							}
						}
						else if (midcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
							fout << "push [ecx]" << endl;
						}
						else if (midcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "push [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
					}
				}
				else
				{
					if (midcodeTable[i].src1.typeNum == 0)
					{
						fout << "sub esp, 4" << endl;
					}
					else if (midcodeTable[i].src1.typeNum == 1)
					{
						fout << "push " << midcodeTable[i].src1.value << "d" << endl;
					}
					else if (midcodeTable[i].src1.typeNum == 4)
					{
						if (midcodeTable[i].src1.auxPara == 0)
						{
							if (midcodeTable[i].src1.value >= 0)
							{
								fout << "mov ebx, ebp" << endl;
								fout << "sub ebx, " << midcodeTable[i].src1.value * 4 << "d" << endl;
								fout << "push ebx" << endl;
							}
							else
							{
								fout << "mov ebx, ebp" << endl;
								fout << "add ebx, " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d" << endl;
								fout << "push ebx" << endl;
							}
						}
						else if (midcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
							fout << "push ebx" << endl;
						}
						else if (midcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx, ebp" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, " << midcodeTable[i].src1.value * 4 << "d" << endl;
							fout << "push ebx" << endl;
						}
					}
					else if (midcodeTable[i].src1.typeNum == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, " << valueMem[midcodeTable[i].src1.value] << endl;
						fout << "push ebx" << endl;
					}
					else
					{
						if (midcodeTable[i].src1.auxPara == 0)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							if (midcodeTable[i].src1.value >= 0)
							{
								fout << "sub ebx, " << midcodeTable[i].src1.value * 4 << endl;
							}
							else
							{
								fout << "sub ebx, " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * 4 << endl;
							}
							fout << "push ebx" << endl;
						}
						else if (midcodeTable[i].src1.auxPara == 1)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
							fout << "push ecx" << endl;
						}
						else if (midcodeTable[i].src1.auxPara == 3)
						{
							fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
							fout << "sub ebx, " << midcodeTable[i].src1.value * 4 << endl;
							fout << "push ebx" << endl;
						}
					}
				}
				break;
			}

			case POP:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "add esp, " << midcodeTable[i].src1.value * 4 << endl;
				}
				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "pop eax" << endl;
					fout << "pop eax" << endl;
					fout << "mov [ebp - " << valueMem[midcodeTable[i].des.value] << "], eax" << endl;
				}
				break;
			}

			case CALL:
			{
				fout << "call proce_" << midcodeTable[i].src1.value << endl;
				break;
			}

			case NEG:
			{
				if (midcodeTable[i].src1.typeNum == 1)
				{
					fout << "mov eax, " << midcodeTable[i].src1.value << "d" << endl;
				}
				else if (midcodeTable[i].src1.typeNum == 4)
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebp - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
						}
						else
						{
							fout << "mov eax, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov eax, [ebx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "d]" << endl;
					}
				}
				else if (midcodeTable[i].src1.typeNum == 3)
				{
					fout << "mov eax, [ebp - " << valueMem[midcodeTable[i].src1.value] << "]" << endl;
				}
				else
				{
					if (midcodeTable[i].src1.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
						}
						else
						{
							fout << "mov eax, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum - 1) * (-4) << "d]" << endl;
						}
					}
					else if (midcodeTable[i].src1.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].src1.value - levelTable[j].levelNum + midcodeTable[i].src1.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov eax, [ecx]" << endl;
					}
					else if (midcodeTable[i].src1.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].src1.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].src1.auxParaValue] << "]" << endl;
						fout << "mov eax, [ebx - " << midcodeTable[i].src1.value * 4 << "]" << endl;
					}
				}

				fout << "neg eax" << endl;

				if (midcodeTable[i].des.typeNum == 3)
				{
					fout << "mov [ebp - " << valueMem[midcodeTable[i].des.value] << "], eax" << endl;
				}
				else if (midcodeTable[i].des.typeNum == 4)
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						if (midcodeTable[i].des.value >= 0)
						{
							fout << "mov [ebp - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
						}
						else
						{
							fout << "mov [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 2) * (-4) << "d]" << endl;
						fout << "mov [ebx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, ebp" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "d], eax" << endl;
					}
				}
				else
				{
					if (midcodeTable[i].des.auxPara == 0)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						if (midcodeTable[i].src1.value >= 0)
						{
							fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
						}
						else
						{
							fout << "mov [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum - 1) * (-4) << "d], eax" << endl;
						}
					}
					else if (midcodeTable[i].des.auxPara == 1)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "mov ecx, [ebx + " << (midcodeTable[i].des.value - levelTable[j].levelNum + midcodeTable[i].des.typeNum - 9) * (-4) << "d]" << endl;
						fout << "mov [ecx], eax" << endl;
					}
					else if (midcodeTable[i].des.auxPara == 3)
					{
						fout << "mov ebx, [ebp + " << (midcodeTable[i].des.typeNum - 7 + 2) * 4 << "d]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "sub ebx, [ebp - " << valueMem[midcodeTable[i].des.auxParaValue] << "]" << endl;
						fout << "mov [ebx - " << midcodeTable[i].des.value * 4 << "], eax" << endl;
					}
				}

				break;
			}

			default:
				break;
			}
		}

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

int CountTemp(int index, int offset)
{
	int i, j, k;
	int stack[1000];
	int l = 0;
	bool b;

	memset(stack, 0, sizeof(stack));
	for (i = levelTable[index].entranceAddress; i < levelTable[index].exitAddress; i++)
	{
		if (midcodeTable[i].src1.typeNum == 3)
		{
			b = false;
			for (j = 0; j < l; j++)  //判断当前的临时变量是否已经在之前分配了空间。若分配，则标记
			{
				if (stack[j] == midcodeTable[i].src1.value)
				{
					b = true;
				}
			}
			if (!b)  //若未分配，则分配空间。
			{
				stack[l++] = midcodeTable[i].src1.value;
			}
		}
		if (midcodeTable[i].src2.typeNum == 3)
		{
			b = false;
			for (j = 0; j < l; j++)
			{
				if (stack[j] == midcodeTable[i].src2.value)
				{
					b = true;
				}
			}
			if (!b)
			{
				stack[l++] = midcodeTable[i].src2.value;
			}
		}
		if (midcodeTable[i].des.typeNum == 3)
		{
			b = false;
			for (j = 0; j < l; j++)
			{
				if (stack[j] == midcodeTable[i].des.value)
				{
					b = true;
				}
			}
			if (!b)
			{
				stack[l++] = midcodeTable[i].des.value;
			}
		}
	}

	for (i = 0; i < l; i++)
	{
		valueMem[stack[i]] = (i + 1 + offset) * 4;  //临时变量的偏移量
	}

	return l * 4;
}
