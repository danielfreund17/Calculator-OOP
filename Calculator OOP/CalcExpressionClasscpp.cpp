#define _CRT_SECURE_NO_WARNINGS
#include "CalcExpressionClass.h"

bool CalcExpressionClass::Validation()
{
	bool validate;
	this->initialize();
	validate = firstValidation();
	if (validate)
	{
		validate = checkParentheses();
	}
	if (validate)
	{
		validate = checkOperators();
	}

	return validate;
}

void CalcExpressionClass::initialize()
{
	m_NumOfParentheses = 0;
}

bool CalcExpressionClass::checkOperators()
{
	bool valid = true;
	bool minusProblem = false;
	if ((isOperator(0) && m_Expression[0] != '-') || isOperator(m_Expression.length() - 1))
	{
		valid = false;
	}
	for (int i = 1; i < (m_Expression.length() - 1) && valid; i++)
	{
		minusProblem = false;
		if (isOperator(i))
		{
			minusProblem = minusProblemValidation(i);
			if (!minusProblem && isOperator(i + 1) && m_Expression[i+1])
			{
				valid = false;
			}
			if (m_Expression[i - 1] == '.' || m_Expression[i + 1] == '.')
			{
				valid = false;
			}
		}
	}

	return valid;
}

bool CalcExpressionClass::minusProblemValidation(int i_Pos)
{
	bool minusProblem = false;
	if (m_Expression[i_Pos + 1] == '-')
	{
		if ((i_Pos + 2) < m_Expression.length() && this->isNumber(i_Pos + 2))
		{
			minusProblem = true;
		}
	}

	return minusProblem;
}

bool CalcExpressionClass::firstValidation()
{
	bool valid = true;
	char* arr = "().";
	string str(arr);
	map<char, Operation*>::iterator iter;
	for (iter = m_MapOfOperations.begin(); iter != m_MapOfOperations.end(); iter++)
	{
		str += iter->second->GetSign();
	}
	if (m_Expression == "")
	{
		valid = false;
	}
	for (int i = 0; i < m_Expression.length(); i++)
	{
		if (!isNumber(i) && !isValidSign(i, str))
		{
			valid = false;
			break;
		}
	}

	return valid;
}

bool CalcExpressionClass::isValidSign(int i_Pos, string &i_Str)
{
	bool valid = false;
	for (int i = 0; i < i_Str.length(); i++)
	{
		if (m_Expression[i_Pos] == i_Str[i])
		{
			valid = true;
			break;
		}
	}

	return valid;
}

bool CalcExpressionClass::isNumber(int i_Pos)
{
	return m_Expression[i_Pos] >= '0' && m_Expression[i_Pos] <= '9';
}

bool CalcExpressionClass::checkParentheses()
{
	int balance = 0;
	bool valid = true;
	for (int i = 0; i < m_Expression.length(); i++)
	{
		if (m_Expression[i] == '(')
		{
			if (i != 0 && !this->isOperator(i - 1) && m_Expression[i - 1] != '(')
			{
				valid = false;
				break;
			}
			if (i != m_Expression.length() - 1 && m_Expression[i + 1] == ')')
			{
				valid = false;
				break;
			}
			balance++;
		}
		if (m_Expression[i] == ')')
		{
			if (i != m_Expression.length() - 1 && !this->isOperator(i + 1) && m_Expression[i + 1] != ')')
			{
				valid = false;
				break;
			}
			balance--;
		}

		if (balance < 0)
		{
			valid = false;
			break;
		}
	}
	if (valid != false)
	{
		valid = balance == 0;
	}
	
	return valid;
}

void CalcExpressionClass::Calculate()
{
	this->calculateByParentheses(); //handle paretheses calculation.
	this->doCalculate(); //last calculate after handling paretheses.
	this->clearCounts(); //clear counts and release memory.
}

void CalcExpressionClass::doCalculate()
{
	this->countPriority();
	vector<int>::iterator itr;
	for (itr = m_PriorityVec.begin(); itr != m_PriorityVec.end(); itr++)
	{		
		this->doCalculationByPriority(*itr);
	}
}

void CalcExpressionClass::doCalculationByPriority(int i_Priority)
{
	vector<Operation*>::iterator it = m_VectorsOfOperations.begin();
	while(it != m_VectorsOfOperations.end())
	{
		Operation *operation = *it;
		if (operation->GetPriority() == i_Priority)
		{
			this->calculateByPriority(operation->GetSign());
			it = m_VectorsOfOperations.erase(it);
			delete operation;
		}
		else
		{
			it++;
		}
	}
}

void CalcExpressionClass::calculateByParentheses()
{
	int openParentheses;
	int closeParentheses;
	int startExpressionPos, endExpressionPos;
	string localExpression;
	int length;
	this->countParentheses();
	for (int i = 0; i < this->m_NumOfParentheses; i++)
	{
		openParentheses = findFirstParentheses();
		closeParentheses = findCloseParentheses(openParentheses);
		startExpressionPos = openParentheses + 1;
		endExpressionPos = closeParentheses - 1;
		length = endExpressionPos - startExpressionPos + 1;
		localExpression = this->m_Expression;
		m_Expression = localExpression.substr(startExpressionPos, length);
		this->doCalculate();
		localExpression.replace(openParentheses, closeParentheses - openParentheses + 1, m_Expression);
		m_Expression = localExpression;
	}
}

int CalcExpressionClass::findCloseParentheses(int i_OpenPos)
{
	int pos;
	for (int i = i_OpenPos; i < m_Expression.length(); i++)
	{
		if (m_Expression[i] == ')')
		{
			pos = i;
			break;
		}
	}

	return pos;
}

int CalcExpressionClass::findFirstParentheses()
{
	int pos = 0;
	for (int i = 0; i < this->m_Expression.length(); i++)
	{
		if (m_Expression[i] == '(')
		{
			pos = i;
		}
	}

	return pos;
}

void CalcExpressionClass::countParentheses()
{
	for (int i = 0; i < this->m_Expression.length(); i++)
	{
		if (m_Expression[i] == '(')
		{
			this->m_NumOfParentheses++;
		}
	}
}


void CalcExpressionClass::countPriority()
{
	clearCounts();
	for (int i = 0; i < m_Expression.length(); i++)
	{
		if (isOperator(i))
		{
			incAmount(m_Expression[i]);
		}
	}

	std::sort(m_PriorityVec.begin(), m_PriorityVec.end());
}

void CalcExpressionClass::clearCounts()
{
	vector<Operation*>::iterator itr = m_VectorsOfOperations.begin();
	for (; itr != m_VectorsOfOperations.end(); itr++)
	{
		delete *itr;
	}
	m_VectorsOfOperations.clear();
	m_PriorityVec.clear();
}

void CalcExpressionClass::incAmount(char i_Sign)
{
	Operation *operation = m_OperationCreator.CreateOperation(i_Sign);
	int priority = operation->GetPriority();
	m_VectorsOfOperations.push_back(operation);
	vector<int>::iterator it = std::find(m_PriorityVec.begin(), m_PriorityVec.end(), priority);
	if (it == m_PriorityVec.end())
	{
		m_PriorityVec.push_back(priority);
	}
}



void CalcExpressionClass::calculateByPriority(char i_Op)
{
	int counter = 0;
	int length;
	int startFirstNumber, endFirstNumber;
	int startSecondNumber, endSecondNumber;
	int startExpressionPos, endExpressionPos;
	int operatorPos;
	double firstNum, secondNum, answer;
	string answerString;
	bool minusProblem;
	length = this->m_Expression.length();
	operatorPos = findOperatorPos(i_Op, length, counter);
	if (operatorPos != length)
	{
		endFirstNumber = operatorPos - 1;
		startSecondNumber = operatorPos + 1;
		startFirstNumber = findFirstNumberStartPos(endFirstNumber);
		endSecondNumber = findSecondNumberEndPos(startSecondNumber);
		firstNum = getNumFromString(startFirstNumber, endFirstNumber);
		secondNum = getNumFromString(startSecondNumber, endSecondNumber);
		answer = calcTwoNumbersExpression(firstNum, secondNum, m_Expression[operatorPos]);
		answerString = doubleToString(answer);
		replaceString(startFirstNumber, endSecondNumber, answerString);
	}
}


bool CalcExpressionClass::handleMinusProblem(int i_OperatorPos)
{
	bool minusProblem = false;
	//minusProblem = this->minusProblemValidation(i_OperatorPos);
	if (m_Expression[i_OperatorPos] == '-')
	{
		if (i_OperatorPos == 0)
		{
			minusProblem = true;
		}
		else if (!this->isNumber(i_OperatorPos - 1))
		{
			minusProblem = true;
		}
	}

	return minusProblem;
}


int CalcExpressionClass::findOperatorPos(char i_Op, int i_Length, int &i_NumOfOps)
{
	int pos = i_Length;
	for (int i = 0; i < i_Length; i++)
	{
		if (m_Expression[i] == i_Op)
		{
			if (!this->handleMinusProblem(i))
			{
				pos = i;
				break;
			}
			else
			{
				i_NumOfOps++;
			}
		}
	}

	return pos;
}

void CalcExpressionClass::replaceString(int i_StartPos, int i_EndPos, string & i_Str)
{
	int length = i_EndPos - i_StartPos + 1;
	this->m_Expression.replace(i_StartPos, length, i_Str);
}

string CalcExpressionClass::doubleToString(double i_Answer)
{
	stringstream convertor;
	convertor << i_Answer;
	return convertor.str();
}

int CalcExpressionClass::findFirstNumberStartPos(int  i_Pos)
{
	int returnPos;
	while (i_Pos >= 0 && !isOperator(i_Pos))
	{
		i_Pos--;
	}
	if (i_Pos >= 1 && m_Expression[i_Pos] == '-' && !this->isNumber(i_Pos - 1))
	{
		returnPos = i_Pos;
	}
	else if (i_Pos == 0 && m_Expression[i_Pos] == '-')
	{
		returnPos = i_Pos;
	}
	else
	{
		returnPos = i_Pos + 1;
	}
	
	return returnPos;
}

int CalcExpressionClass::findSecondNumberEndPos(int i_Pos)
{
	i_Pos++;
	while (i_Pos <= this->m_Expression.length() - 1 && !isOperator(i_Pos))
	{
		i_Pos++;
	}

	return i_Pos - 1;
}

bool CalcExpressionClass::isOperator(int i_Pos)
{
	bool isOperator = false;
	if (m_MapOfOperations.find(m_Expression[i_Pos]) != m_MapOfOperations.end())
	{
		isOperator = true;
	}

	return isOperator;
}

double CalcExpressionClass::getNumFromString(int i_StartPos, int i_EndPos)
{
	int lengthOfNum = i_EndPos - i_StartPos + 1;
	string strNum = this->m_Expression.substr(i_StartPos, lengthOfNum);

	return atof(strNum.c_str());
}

double CalcExpressionClass::calcTwoNumbersExpression(double i_FirstNum, double i_SecondNum, char i_Op)
{
	return this->m_MapOfOperations[i_Op]->Perform(i_FirstNum, i_SecondNum);
}


CalcExpressionClass::CalcExpressionClass()
{
	m_MapOfOperations[ADD] = new AddClass();
	m_MapOfOperations[SUBTRACT] = new SubtractClass();
	m_MapOfOperations[MULTIPLY] = new MultiplyClass();
	m_MapOfOperations[DIVIDE] = new DivideClass();
}

CalcExpressionClass::~CalcExpressionClass()
{
	delete m_MapOfOperations[ADD];
	delete m_MapOfOperations[SUBTRACT];
	delete m_MapOfOperations[MULTIPLY];
	delete m_MapOfOperations[DIVIDE];
}

