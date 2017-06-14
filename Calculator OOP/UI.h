#ifndef _UI_H
#define _UI_H
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "CalcExpressionClass.h"

class UI {
	bool m_IsValid = true;
	string m_Str;
	CalcExpressionClass m_CalcManager;
	vector<string> m_HistoryList;
public:
	void RunUI();
private:
	void runCalculation();
	void calculateExpression();
	void exitCalculator();
	int mainMenu();
	bool doAction(int);
	void showHistory();
	void clearCinBuffer();
	void clearScreen();
	void printMainMenu();
	bool checkMainMenuInputValidation(int);
	void holdScreen();
};
#endif