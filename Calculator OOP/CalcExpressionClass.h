#ifndef _CalcExpressionClass_H
#define _CalcExpressionClass_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include "Operation.h";
#include "AddClass.h"
#include "DivideClass.h"
#include "SubtractClass.h"
#include "MultiplyClass.h"
#include "OperationCreator.h"

class CalcExpressionClass
{
	string m_Expression;
	vector<Operation*> m_VectorsOfOperations;
	map<char, Operation*> m_MapOfOperations;
	vector<int> m_PriorityVec;
	int m_NumOfParentheses = 0;
	OperationCreator m_OperationCreator;
public:
	CalcExpressionClass();
	~CalcExpressionClass();
	void Calculate(); //calculates the expression
	bool Validation(); //validate the expression.
	void SetExpression(string i_Expression) { m_Expression = i_Expression; }
	string GetExpression() { return m_Expression; }
private:
	void countPriority(); //count operators by priority.
	void doCalculationByPriority(int); //calculating by priority
	void calculateByPriority(char); //calculating by priority
	int findFirstNumberStartPos(int i_Pos); //starting index of first number
	int findSecondNumberEndPos(int i_Pos); 
	bool isOperator(int i_Pos); //returns true if m_Expression[i_Pos] is an operator sign
	double getNumFromString(int, int); //converts string to dobule
	double calcTwoNumbersExpression(double, double, char); //calculates two numbers by the sign (char).
	string doubleToString(double); //converts from double to string
	void replaceString(int, int, string &); //replace a part in a string by the string given in the method.
	void incAmount(char); //increments the amount of specific operator, by searching in the expression.
	int findOperatorPos(char, int, int&); //returns the index of an operator.
	void calculateByParentheses(); //method for giving priority to parentheses expressions.
	void clearCounts(); //clear the previews counts.
	int findFirstParentheses(); //finding parentheses
	int findCloseParentheses(int i_OpenPos); //finding parentheses
	void countParentheses(); //counting parentheses 
	void doCalculate(); //private helper of the Public Calculate method.
	bool checkParentheses();//check validation of paratheses.
	bool firstValidation();//first validation input- check if all signs are legal.
	bool isNumber(int); //returns true if the char in m_Expression at the index given is a number.
	bool isValidSign(int, string &);//returns true if the sign is legal
	bool checkOperators(); //checking operators validations.
	void initialize();//initilizing values.
	bool handleMinusProblem(int i_OperatorPos); //handling the minus problem (minus number but not subtract operation).
	bool minusProblemValidation(int); //validating minus problem.
};

#endif