#include "main.h"

void init()
{
    ch = ' ';
    cc = 0;
    ll = 0;
    lineNum = 0;
    number = 0;
    nowLevel = 0;
	symbolIndex = 0;
	levelTableIndex = 1;
	pc = 0;
	valIndex = 0;
	expressionType = 0;
	strIndex = 0;
	symbolLevel = 0;
	errorSum = 0;
	insertSign = true;
	memset(strTable, 0, sizeof(strTable));
	memset(levelTable, 0, sizeof(levelTable));
}

void LexiconAnalysisTest()
{
    int i = 0;

    while (ch != '\0')
    {
        getsym();
        i++;
        switch (symbol)
        {
        case IDENT:
            fout << i << " " << "IDENT" << " " << token << endl;
            break;
        case INTCON:
            fout << i << " " << "INTCON" << " " << token << endl;
            break;
        case CHARCON:
            fout << i << " " << "CHARCON" << " " << token << endl;
            break;
        case STRTK:
            fout << i << " " << "STRTK" << " " << token << endl;
            break;
        case CONSTTK:
            fout << i << " " << "CONSTTK" << " " << token << endl;
            break;
        case VARTK:
            fout << i << " " << "VARTK" << " " << token << endl;
            break;
        case INTTK:
            fout << i << " " << "INTTK" << " " << token << endl;
            break;
        case CHARTK:
            fout << i << " " << "CHARTK" << " " << token << endl;
            break;
        case ARRAYTK:
            fout << i << " " << "ARRAYTK" << " " << token << endl;
            break;
        case PROCEDURETK:
            fout << i << " " << "PROCEDURETK" << " " << token << endl;
            break;
        case FUNCTIONTK:
            fout << i << " " << "FUNCTIONTK" << " " << token << endl;
            break;
        case BEGINTK:
            fout << i << " " << "BEGINTK" << " " << token << endl;
            break;
        case ENDTK:
            fout << i << " " << "ENDTK" << " " << token << endl;
            break;
        case IFTK:
            fout << i << " " << "IFTK" << " " << token << endl;
            break;
        case THENTK:
            fout << i << " " << "THENTK" << " " << token << endl;
            break;
        case ELSETK:
            fout << i << " " << "ELSETK" << " " << token << endl;
            break;
        case CASETK:
            fout << i << " " << "CASETK" << " " << token << endl;
            break;
        case OFTK:
            fout << i << " " << "OFTK" << " " << token << endl;
            break;
        case FORTK:
            fout << i << " " << "FORTK" << " " << token << endl;
            break;
        case TOTK:
            fout << i << " " << "TOTK" << " " << token << endl;
            break;
        case DOWNTK:
            fout << i << " " << "DOWNTK" << " " << token << endl;
            break;
        case DOTK:
            fout << i << " " << "DOTK" << " " << token << endl;
            break;
        case READTK:
            fout << i << " " << "READTK" << " " << token << endl;
            break;
        case WRITETK:
            fout << i << " " << "WRITETK" << " " << token << endl;
            break;
        case PLUS:
            fout << i << " " << "PLUS" << " " << token << endl;
            break;
        case MINUS:
            fout << i << " " << "MINUS" << " " << token << endl;
            break;
        case MULT:
            fout << i << " " << "MULT" << " " << token << endl;
            break;
        case DIV:
            fout << i << " " << "DIV" << " " << token << endl;
            break;
        case LSS:
            fout << i << " " << "LSS" << " " << token << endl;
            break;
        case LEQ:
            fout << i << " " << "LEQ" << " " << token << endl;
            break;
        case GRE:
            fout << i << " " << "GRE" << " " << token << endl;
            break;
        case GEQ:
            fout << i << " " << "GEQ" << " " << token << endl;
            break;
        case EQL:
            fout << i << " " << "EQL" << " " << token << endl;
            break;
        case NEQ:
            fout << i << " " << "NEQ" << " " << token << endl;
            break;
        case ASSIGN:
            fout << i << " " << "ASSIGN" << " " << token << endl;
            break;
        case LPARENT:
            fout << i << " " << "LPARENT" << " " << token << endl;
            break;
        case RPARENT:
            fout << i << " " << "RPARENT" << " " << token << endl;
            break;
        case LBRACK:
            fout << i << " " << "LBRACK" << " " << token << endl;
            break;
        case RBRACK:
            fout << i << " " << "RBRACK" << " " << token << endl;
            break;
        case COLON:
            fout << i << " " << "COLON" << " " << token << endl;
            break;
        case COMMA:
            fout << i << " " << "COMMA" << " " << token << endl;
            break;
        case SEMICN:
            fout << i << " " << "SEMICN" << " " << token << endl;
            break;
        case PERIOD:
            fout << i << " " << "PERIOD" << " " << token << endl;
            break;
        default:
            break;
        }
        symbol = NUL;
    }
}

void symbolTableTest()
{
    int i = 0;

    for (i = 0; i < symbolIndex; i++)
       fout << symbolTable[i].name << "  " << symbolTable[i].kind << "  " << symbolTable[i].dataType << "  " << symbolTable[i].length << "  " << symbolTable[i].level << "  " << symbolTable[i].address << endl;
}

void midcodeTest()
{
	int i;

	for (i = 0; i < pc; i++)
	{
		fout << i << "\t" "\t";
		switch (OPmidcodeTable[i].op)
		{
		case ADD:
			fout << "ADD    ";
			break;
		case SUB:
			fout << "SUB    ";
			break;
		case MUL:
			fout << "MUL    ";
			break;
		case DIVI:
			fout << "DIVI   ";
			break;
		case NEG:
			fout << "NEG    ";
			break;
		case JMP:
			fout << "JMP    ";
			break;
		case JG:
			fout << "JG     ";
			break;
		case JL:
			fout << "JL     ";
			break;
		case JGE:
			fout << "JGE    ";
			break;
		case JLE:
			fout << "JLE    ";
			break;
		case JE:
			fout << "JE     ";
			break;
		case JNE:
			fout << "JNE    ";
			break;
		case ASS:
			fout << "ASS    ";
			break;
		case CALL:
			fout << "CALL   ";
			break;
		case RET:
			fout << "RET    ";
			break;
		case READ:
			fout << "READ   ";
			break;
		case WRITE:
			fout << "WRITE  ";
			break;
		case PUSH:
			fout << "PUSH   ";
			break;
		case POP:
			fout << "POP    ";
			break;
		case PUD:
			fout << "PUD    ";
			break;
		case NOP:
			fout << "NOP    ";
			break;
		case END:
			fout << "END    ";
			break;
		default:
			break;
		}

		switch (OPmidcodeTable[i].src1.typeNum)
		{
		case 1:
			fout << "常数        " << OPmidcodeTable[i].src1.value << "\t";
			break;
		case 2:
			fout << "入口        " << OPmidcodeTable[i].src1.value << "\t";
			break;
		case 3:
			fout << "临时变量    " << OPmidcodeTable[i].src1.value << "\t";
			break;
		case 4:
			fout << "变量        " << OPmidcodeTable[i].src1.value << "\t";
			break;
		case 5:
			fout << "字符串      " << OPmidcodeTable[i].src1.value << "\t";
			break;
		default:
			break;
		}

		switch (OPmidcodeTable[i].src2.typeNum)
		{
		case 1:
			fout << "常数        " << OPmidcodeTable[i].src2.value << "\t";
			break;
		case 2:
			fout << "入口        " << OPmidcodeTable[i].src2.value << "\t";
			break;
		case 3:
			fout << "临时变量    " << OPmidcodeTable[i].src2.value << "\t";
			break;
		case 4:
			fout << "变量        " << OPmidcodeTable[i].src2.value << "\t";
			break;
		default:
			break;
		}

		switch (OPmidcodeTable[i].des.typeNum)
		{
		case 1:
			fout << "常数        " << OPmidcodeTable[i].des.value << "\t";
			break;
		case 2:
			fout << "入口        " << OPmidcodeTable[i].des.value << "\t";
			break;
		case 3:
			fout << "临时变量    " << OPmidcodeTable[i].des.value << "\t";
			break;
		case 4:
			fout << "变量        " << OPmidcodeTable[i].des.value << "\t";
			break;
		default:
			break;
		}
		fout << endl;
	}
}

int main()
{
    char inputFileName[100];  //输入程序文件名
    char outputFileName[100];  //输出程序文件名

    cout << "Please enter input file's name:" << endl;
    cin >> inputFileName;
    //cout << "Please enter output file's name:" << endl;
    //cin >> outputFileName;
    fin.open(inputFileName, ios::in);
    fout.open("FinalCode.txt", ios::out);
    //fout.open(outputFileName, ios::out);
    init();
    //LexiconAnalysisTest();
    program();
    //symbolTableTest();
	FinalcodeProducer();
	//Optimize();
	//midcodeTest();
	//FinalcodeProducerOP();

	if (errorSum == 0)
	{
		cout << "Compiler success!" << endl;
	}
	else
	{
		cout << "The sum of errors is " << errorSum << endl;
		cout << "Compiler end." << endl;
	}

    return 0;
}
