#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <math.h>

enum TTypes
{
    SPACE,
    TAB,
    LEFTFIGURE,
    RIGHTFIGURE,
    LEFTBRACKET,
    RIGHTBRACKET,
    LEFTSQUAREBRACKET,
	RIGHTSQUAREBRACKET,
    STRINGCONST,
    ENDOFLINE,
    E,
    IDENTIFICATOR,
    NUMBER,
    REMARK,
    CMP,
    PRINT,
    INPUTe,
    ASSIGN,
    IFSTAT,
    THENSTAT,
    ELSESTAT,
    COLON,
    PLUS,
    MINUS,
    STAR,
    DIVIDE,
    MOD,
    COMMA,
    BITNOT,
    LOGICALNOT,
    INC,
    DEC,
    AMPERSAND,
    LOGICALAND,
    BITOR,
    LOGICALOR,
    EXCEPTOR,
    SHIFT,
    COMPLEX,
    CHOOSE,
    POINTe,
    QUESTION,
    SIZEOF,
    CAST,
    SWITCHSTAT,
    CASESTAT,
    DEFAULTSTAT,
    WHILESTAT,
    DOSTAT,
    FORSTAT,
    GOTOSTAT,
	CONTINUESTAT,
	BREAKSTAT,
	DATATYPE,
	INCLUDESTAT,
    DEFINESTAT,
	RETURNSTAT,
	CHARCONST,
	CLASSSTAT,
	STRUCTSTAT,
	USINGSTAT,
    NAMESPACESTAT,
	ERRORe
};

const std::regex space(R"( )");
const std::regex tab(R"(\t)");
const std::regex leftFigure(R"([{])");
const std::regex rightFigure(R"([}])");
const std::regex leftBracket(R"([(])");
const std::regex rightBracket(R"([)])");
const std::regex leftSquareBracket(R"(\[)");
const std::regex rightSquareBracket(R"(\])");
const std::regex stringConst(R"(".*")");
const std::regex endOfLine(R"(\n)");
const std::regex e(R"(;)");
const std::regex identificator(R"(([A-Z]|[a-z]|_)+([A-Z]|[a-z]|_|[0-9])*)");
const std::regex number(R"([0-9]+)");
const std::regex remark(R"((//.*))");
const std::regex cmp(R"(!=|==|>=|<=|>|<)");
const std::regex print(R"(cout|std::cout)");
const std::regex input(R"(cin|std::cin)");//������ ����� ������ cout, �������������� �� ������ ����� ������������� std - �������������, : - ���������, : - ���������, cout - print
const std::regex assign(R"(=)");
const std::regex ifStat(R"(if)");
const std::regex thenStat(R"(then)");
const std::regex elseStat(R"(else)");
const std::regex colon(R"(:)");
const std::regex plus(R"(\+)");
const std::regex minus(R"(-)");
const std::regex star(R"(\*)");
const std::regex divide(R"(/)");
const std::regex mod(R"(%)");
const std::regex comma(R"(,)");
const std::regex bitNot(R"(~)");
const std::regex logicalNot(R"(!)");
const std::regex inc(R"(\+\+)");
const std::regex dec(R"(\-\-)");
const std::regex ampersand(R"(&)");
const std::regex logicalAnd(R"(&&)");
const std::regex bitOr(R"(\|)");
const std::regex logicalOr(R"(\|\|)");
const std::regex exceptOr(R"(\^)");
const std::regex shift(R"(<<|>>)");
const std::regex complex(R"(\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<=|>>=)");
const std::regex choose(R"(->)");
const std::regex point(R"(\.)");
const std::regex question(R"(\?)");
const std::regex sizeOf(R"(sizeof)");
const std::regex cast(R"(\(int\))");
const std::regex switchStat(R"(switch)");
const std::regex caseStat(R"(case)");
const std::regex defaultStat(R"(default)");
const std::regex whileStat(R"(while)");
const std::regex doStat(R"(do)");
const std::regex forStat(R"(for)");
const std::regex goToStat(R"(goto)");
const std::regex continueStat(R"(continue)");
const std::regex breakStat(R"(break)");
//const std::regex dataType(R"(int\**|bool\**|char\**|void\**)");
const std::regex dataType(R"(int|bool|char|void)");
const std::regex includeStat(R"(#include +<.+>)");
const std::regex defineStat(R"(#define +([A-Z]|[a-z])+ +-*[0-9]+)");
const std::regex returnStat(R"(return)");
const std::regex charConst(R"('.'|'\\.')");
const std::regex classStat(R"(class)");
const std::regex structStat(R"(struct)");
const std::regex usingStat(R"(using)");
const std::regex namespaceStat(R"(namespace)");





#define countOfRegex 62
std::regex regexes[countOfRegex] = { space, tab, leftFigure, rightFigure, leftBracket, rightBracket, leftSquareBracket, rightSquareBracket, stringConst,
                                    endOfLine, e, identificator, number, remark, cmp, print, input, assign, ifStat, thenStat, elseStat, colon, plus, minus,
                                    star, divide, mod, comma, bitNot, logicalNot, inc, dec, ampersand, logicalAnd, bitOr, logicalOr, exceptOr, shift,
									complex, choose, point, question, sizeOf, cast, switchStat, caseStat, defaultStat,  whileStat, doStat, forStat, goToStat,
									continueStat, breakStat, dataType, includeStat, defineStat, returnStat, charConst, classStat, structStat, usingStat, namespaceStat };

struct Lexem
{
    enum TTypes type;
    std::string lexemStr;
};

std::ifstream in;
std::ofstream out;
std::vector<struct Lexem> terms;
int next = 0;
bool errorFlag = false;
std::unordered_map<std::string, int> operators;
std::unordered_map<std::string, int> operands;
int operatorsVocabulary = 0;
int operandsVocabulary = 0;
int operatorsCount = 0;
int operandsCount = 0;
int programVocabulary = 0;
int programLength = 0;
int programVolume = 0;

//������ ������ ����� ������������ ���������� �����, ����� �������� ��� � ������
bool getTerms(void)
{
    int strNum = 0;
    std::string str;
    char c;

    std::string line;
    getline(in, line);
    strNum++;

    std::string lex = "";

    enum TTypes lastTerm = SPACE;
    enum TTypes newTerm = ERRORe;
    bool flag = false;
    int count, length;
    while (!in.eof())
    {
        length = line.length();
        std::string lineCopy = line;
        for (int i = 0; i < length; i++)
        {
            c = line.front();
            lex.push_back(c);
            newTerm = ERRORe;
            for (int j = 0; j < countOfRegex; j++)
            {
                if (regex_match(lex, regexes[j]))
                    newTerm = (enum TTypes)j;
            }
            if (newTerm == ERRORe && flag)
            {
                if (lastTerm != SPACE && lastTerm != TAB)
                {
                    if (newTerm != REMARK)
                        terms.push_back({ lastTerm, lex.substr(0, lex.length() - 1) });
                }
                lex = "";
                flag = false;
                i--;
            }
            else
            {
                if (newTerm != ERRORe)
                    flag = true;
                lastTerm = newTerm;
                line.erase(0, 1);
            }
        }
        if (newTerm != ERRORe)
        {
            if (newTerm != SPACE && newTerm != TAB)
            {
                if (newTerm != REMARK)
                    terms.push_back({ lastTerm,  lex });

                lex = "";
                flag = false;
            }
            terms.push_back({ ENDOFLINE, "\n" });
        }
        else
        {
            if (!errorFlag)
            {
                printf("����������� ������ � ������: %d\n", strNum);
                out << "����������� ������ � ������: " << strNum << "\n";
                errorFlag = true;
            }
            return false;
        }
        getline(in, line);
        strNum++;
    }
    return true;
}

bool checkTerm(const enum TTypes expected)
{
    bool result;
    if (next < terms.size())
        result = (expected == terms[next].type);
    else
        result = false;
    next++;
    return result;
}

bool remarkBlock()
{
    if (!checkTerm(REMARK))
        return false;
    return true;
}
void incInMap(std::unordered_map<std::string, int>& map, const std::string& key, int count = 1)
{
    if (map.find(key) == map.end())
        map.emplace(key, count);
    else
        map.find(key)->second += count;
}

void decInMap(std::unordered_map<std::string, int>& map, const std::string& key, int count = -1)
{
    if (map.find(key) == map.end())
        map.emplace(key, count);
    else
        map.find(key)->second += count;
}

bool functionDeclaration()
{
    int save;
    if (!checkTerm(DATATYPE))
        return false;
    save = next;
    if (!checkTerm(IDENTIFICATOR))
        return false;
    save = next;
    if (!checkTerm(LEFTBRACKET))
        return false;
    save = next;
    if (!checkTerm(DATATYPE))
    {
        next = save;
        if (!checkTerm(RIGHTBRACKET))
            return false;
    }
    else
	{
        while (terms[next].type == STAR) {++next;}
        save = next;
        if (!checkTerm(IDENTIFICATOR))
            return false;
        save = next;
        while (checkTerm(COMMA))
		{
            if (!checkTerm(DATATYPE))
				return false;
			while (terms[next].type == STAR) {++next;}
            save = next;
            if (!checkTerm(IDENTIFICATOR))
                return false;
            save = next;
        }
        next = save;
        if (!checkTerm(RIGHTBRACKET))
            return false;
        save = next;
    }
    return true;
}

bool functionCall()
{
    std::unordered_map<std::string, int> identificators;
    int commasCount = 0;
    std::string functionName = terms[next].lexemStr;
    int save;
    if (!checkTerm(IDENTIFICATOR))
        return false;
    save = next;
    if (!checkTerm(LEFTBRACKET))
        return false;
    save = next;
    if (!checkTerm(IDENTIFICATOR))
    {
        next = save;
        if (!checkTerm(RIGHTBRACKET))
            return false;
    }
    else
    {
        incInMap(identificators, terms[next - 1].lexemStr);
        save = next;
        while (checkTerm(COMMA))
        {
            ++commasCount;
            if (!checkTerm(IDENTIFICATOR))
                return false;
            save = next;
            incInMap(identificators, terms[next - 1].lexemStr);
        }
        next = save;
        if (!checkTerm(RIGHTBRACKET))
            return false;
        save = next;
    }
    for (const auto& elem : identificators)
        incInMap(operands, elem.first, elem.second);
    incInMap(operators, ",", commasCount);
    incInMap(operators, functionName + "()");
    return true;
}

bool namespaceDeclaration()
{
    int save;
	if (!checkTerm(USINGSTAT))
		return false;
    save = next;
	if (!checkTerm(NAMESPACESTAT))
		return false;
    save = next;
	if (!checkTerm(IDENTIFICATOR))
		return false;
    save = next;
	if (!checkTerm(E))
		return false;
	return true;
}

void deleteEndsOfLine()
{
	while (next < terms.size() && ENDOFLINE == terms[next].type)
		next++;
}

void clearAll()
{
	terms.clear();
	next = 0;
	operators.clear();
	operands.clear();
	operatorsVocabulary = 0;
	operandsVocabulary = 0;
	operatorsCount = 0;
	operandsCount = 0;
	programVocabulary = 0;
	programLength = 0;
	programVolume = 0;
}

//Parser main part, above represented some functions to implement it, but currently it's not fully working parser, but just Holsted metrics counter
bool mainBlock2() {
//operators.clear();
//operands.clear();
//operatorsVocabulary = 0;
// operandsVocabulary = 0;
// operatorsCount = 0;
// operandsCount = 0;
// programVocabulary = 0;
// programLength = 0;
// programVolume = 0;
	while (next < terms.size())
	{
		int save = next;
		int counter = 0;
		if (!functionDeclaration())
		{
			next = save;
			counter++;
		}
		else
			save = next;

		deleteEndsOfLine();

		if (!functionCall())
		{
			next = save;
            counter++;
        }
		else
			save = next;

		deleteEndsOfLine();

		if (!namespaceDeclaration())
		{
			next = save;
            counter++;
        }
		else
			save = next;

		deleteEndsOfLine();

        if (next < terms.size())
		{
			if (terms[next].type == IDENTIFICATOR || terms[next].type == NUMBER || terms[next].type == STRINGCONST || terms[next].type == CHARCONST)
            {
				incInMap(operands, terms[next].lexemStr);
			}
            else if (terms[next].type == QUESTION)
            {
                incInMap(operators, "?...:");
				decInMap(operators, ":");
            }
            else if (terms[next].type == LEFTFIGURE)
            {
				incInMap(operators, "{}");
            }
            else if (terms[next].type == IFSTAT)
            {
				incInMap(operators, "if...else");
                decInMap(operators, "()");
            }
            else if (terms[next].type == SWITCHSTAT)
			{
                incInMap(operators, "switch()...case...default");
				decInMap(operators, "()");
            }
			else if (terms[next].type == DOSTAT)
            {
                incInMap(operators, "do...while()");
                decInMap(operators, "()");
			}
            else if (terms[next].type == WHILESTAT)
            {
                incInMap(operators, "while()");
				decInMap(operators, "()");
            }
            else if (terms[next].type == FORSTAT)
            {
				incInMap(operators, "for()");
                decInMap(operators, "()");
            }
            else if (terms[next].type == GOTOSTAT)
			{
                incInMap(operators, "goto");
            }
            else if (terms[next].type == LEFTBRACKET)
			{
                incInMap(operators, "()");
            }
            else if (terms[next].type == LEFTSQUAREBRACKET)
			{
                incInMap(operators, "[]");
            }
            else if (terms[next].type == PRINT)
			{
                incInMap(operators, "cout <<");
                decInMap(operators, "<<");
            }
			else if (terms[next].type == INPUTe)
            {
                incInMap(operators, "cin >>");
                decInMap(operators, ">>");
			}
			else if (terms[next].type != RIGHTFIGURE && terms[next].type != RIGHTBRACKET && terms[next].type != RIGHTSQUAREBRACKET &&
                terms[next].type != ENDOFLINE && terms[next].type != THENSTAT && terms[next].type != ELSESTAT && terms[next].type != CASESTAT &&
				terms[next].type != DEFAULTSTAT && terms[next].type != DATATYPE && terms[next].type != INCLUDESTAT && terms[next].type != ERRORe &&
				terms[next].type != DEFINESTAT && terms[next].type != CLASSSTAT && terms[next].type != STRUCTSTAT)
			{
				incInMap(operators, terms[next].lexemStr);
			}
			++next;
		}

		deleteEndsOfLine();

		//if (counter >= 1)
			//return false;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	bool flag;
	if (in.is_open())         //out.is_open()
	{

		next = 0;
		if (getTerms())
			if (!mainBlock2())
			{
				printf("ERROR\n");
				out << "ERROR\n";
			}
			else
			{
				printf("OPERATORS:\n");
				for (const auto& elem : operators)
					if (elem.second)
						std::cout << elem.first << "\t" << elem.second << "\n";
				printf("\n\n\n");
				printf("OPERANDS:\n");
				for (const auto& elem : operands)
					std::cout << elem.first << "\t" << elem.second << "\n";
				//printf("SUCCESS\n");
				//out << "SUCCESS\n";
			}
		in.close();
		out.close();
		return 0;
	}
}
