#include "LexiconAnalysis.h"

void getch()
{
    if (cc == ll)
    {
        clearLine();
        if (fin.eof())
        {
            ch = '\0';
            symbol = NUL;
        }
        lineNum++;
        ll = 0;
        cc = 0;
        fin.get(ch);
        while (ch != '\n')
        {
            if (fin.eof())  //eof真是太迷了- - eof在读取完最后一个数据后仍然是false，当再次试图读取一个数据时发现没有数据可读取了，才发现到结尾了，为true。
            {
                ll++;
                break;
            }
            line[ll] = ch;
            ll++;
            fin.get(ch);
        }
        ch = ' ';
    }
    else
    {
        ch = line[cc++];
    }
}

void clearLine()
{
    memset(line, 0, 1000);
}

void addToken()
{
    int length;

    length = strlen(token);
    token[length ] = ch;
}

void clearToken()
{
    memset(token, 0, 256);
}

void getsym()
{
    int symbolNum;

    clearToken();

    while (isSpace() || isNewLine() || isTab())
    {
        getch();
    }

    if (ifLetter())
    {
        while (ifLetter() || isDigit())
        {
            addToken();
            getch();
        }
        symbolNum = reserverWords();
        symbol = (enum symbol) symbolNum;
    }
    else if (isDigit())
    {
        while (isDigit())
        {
            addToken();
            getch();
        }
        number = changeNumber();
        symbol = INTCON;
    }
    else if (ch == '\'')
    {
        getch();
        if (isDigit() || isLetter())
        {
            addToken();
            getch();
			if (isDigit() || isLetter())
			{
				Error(2);
			}
            else if (ch != '\'')
            {
                Error(1);
            }
            else
            {
                symbol = CHARCON;
                getch();
            }
        }
        else
        {
            Error(2);
        }
    }
    else if (ch == '"')
    {
        getch();
        while (isStr() || ch == '"')
        {
            if (ch == '"')
            {
                symbol = STRTK;
                break;
            }
            else
            {
                addToken();
                getch();
            }
        }
        if (ch == '"')
        {
            getch();
        }
        else
        {
            Error(3);
        }
    }
    else if (ch == ':')
    {
        addToken();
        getch();
        if (ch == '=')
        {
            addToken();
            symbol = ASSIGN;
            getch();
        }
        else
        {
            symbol = COLON;
        }
    }
    else if (ch == '=')
    {
        addToken();
        symbol = EQL;
        getch();
    }
    else if (ch == '<')
    {
        addToken();
        getch();
        if (ch == '=')
        {
            addToken();
            symbol = LEQ;
            getch();
        }
		else if (ch == '>')
		{
			addToken();
			symbol = NEQ;
			getch();
		}
        else
        {
            symbol = LSS;
        }
    }
    else if (ch == '>')
    {
        addToken();
        getch();
        if (ch == '=')
        {
            addToken();
            symbol = GEQ;
            getch();
        }
        else
        {
            symbol = GRE;
        }
    }
    else if (ch == '+')
    {
        addToken();
        symbol = PLUS;
        getch();
    }
    else if (ch == '-')
    {
        addToken();
        symbol = MINUS;
        getch();
    }
    else if (ch == '*')
    {
        addToken();
        symbol = MULT;
        getch();
    }
    else if (ch == '/')
    {
        addToken();
        symbol = DIV;
        getch();
    }
    else if (ch == '(')
    {
        addToken();
        symbol = LPARENT;
        getch();
    }
    else if (ch == ')')
    {
        addToken();
        symbol = RPARENT;
        getch();
    }
    else if (ch == '[')
    {
        addToken();
        symbol = LBRACK;
        getch();
    }
    else if (ch == ']')
    {
        addToken();
        symbol = RBRACK;
        getch();
    }
    else if (ch == ',')
    {
        addToken();
        symbol = COMMA;
        getch();
    }
    else if (ch == ';')
    {
        addToken();
        symbol = SEMICN;
        getch();
    }
    else if (ch == '.')
    {
        addToken();
        symbol = PERIOD;
        getch();
    }
    else
    {
        getch();
    }

}

bool isSpace()
{
    if (ch == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isNewLine()
{
    if (ch == '\n' || ch == '\r')
    {

        return true;
    }
    else
    {
        return false;
    }
}

bool isTab()
{
    if (ch == '\t')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isLetter()
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ifLetter()
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {

        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - 'A' + 'a';
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool isDigit()
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isStr()
{
    int chNum = ch;

    if (chNum == 32 || chNum == 33 || (chNum >= 35 && chNum <= 126))
        return true;
    else
        return false;
}

int reserverWords()
{
    if (strcmp(token, "begin") == 0)
        return BEGINTK;
    else if (strcmp(token, "end") == 0)
        return ENDTK;
    else if (strcmp(token, "if") == 0)
        return IFTK;
    else if (strcmp(token, "then") == 0)
        return THENTK;
    else if (strcmp(token, "else") == 0)
        return ELSETK;
    else if (strcmp(token, "case") == 0)
        return CASETK;
    else if (strcmp(token, "of") == 0)
        return OFTK;
    else if (strcmp(token, "for") == 0)
        return FORTK;
    else if (strcmp(token, "to") == 0)
        return TOTK;
    else if (strcmp(token, "downto") == 0)
        return DOWNTK;
    else if (strcmp(token, "do") == 0)
        return DOTK;
    else if (strcmp(token, "read") == 0)
        return READTK;
    else if (strcmp(token, "write") == 0)
        return WRITETK;
    else if (strcmp(token, "const") == 0)
        return CONSTTK;
    else if (strcmp(token, "var") == 0)
        return VARTK;
    else if (strcmp(token, "array") == 0)
        return ARRAYTK;
    else if (strcmp(token, "procedure") == 0)
        return PROCEDURETK;
    else if (strcmp(token, "function") == 0)
        return FUNCTIONTK;
    else if (strcmp(token, "integer") == 0)
        return INTTK;
    else if (strcmp(token, "char") == 0)
        return CHARTK;
    else
        return IDENT;
}

int changeNumber()
{
    int number;

    number = atoi(token);
    return number;
}
