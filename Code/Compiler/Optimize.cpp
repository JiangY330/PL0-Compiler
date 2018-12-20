#include "Optimize.h"

void divideFunc()
{
	int i, j, k;
	int top = 0;
	for (i = 0; i < levelTableIndex; i++)
	{
		funcOrder[i] = i;
	}
	for (i = 0; i < levelTableIndex; i++)
	{
		for (j = i; j < levelTableIndex; j++)
		{
			if (levelTable[funcOrder[i]].entranceAddress > levelTable[funcOrder[j]].entranceAddress)
			{
				k = funcOrder[i];
				funcOrder[i] = funcOrder[j];
				funcOrder[j] = k;
			}
		}
	}
}

void Optimize()
{
	int i, j, k;
	int in;
	memset(funcOrder, 0, sizeof(funcOrder));

	divideFunc();
	for (i = 0; i < levelTableIndex; i++)
	{
		in = pc1;
		DataFlowAnalysis(funcOrder[i]);
		levelTable[funcOrder[i]].entranceAddress = in;
		levelTable[funcOrder[i]].exitAddress = pc1;
	}

	cout << "pc:" << pc << endl;
	cout << "pc_new:" << pc1 << endl;

}