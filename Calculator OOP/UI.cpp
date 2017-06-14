#include "UI.h"
#include <stdlib.h>

void UI::RunUI()
{
	
	bool keepRunning = true;
	int userChoice;
	while (keepRunning)
	{
		userChoice = mainMenu();
		keepRunning = doAction(userChoice);
	}

	exitCalculator();
}

bool UI::doAction(int i_UserChoice)
{
	bool userWantsToContinue = true;
	switch (i_UserChoice)
	{
		case 1:
			runCalculation();
			break;
		case 2:
			showHistory();
			break;
		case 3:
			userWantsToContinue = false;
			break;
	}

	return userWantsToContinue;
}

void UI::showHistory()
{
	if (m_HistoryList.empty())
	{
		cout << "You didn't calculate anything yet!" << endl;
	}
	else
	{
		vector<string>::iterator itr = m_HistoryList.begin();
		for (; itr < m_HistoryList.end(); itr++)
		{
			cout << *itr << endl;
		}
	}	
	holdScreen();
}


int UI::mainMenu()
{
	bool validChoose = false;
	int userInput;
	this->clearScreen();
	while (!validChoose)
	{
		printMainMenu();
		cin >> userInput;
		validChoose = checkMainMenuInputValidation(userInput);
		if(!validChoose)
		{
			cout << "Please insert a number between 1 to 3" << endl;
			holdScreen();
		}
		this->clearScreen();
	}	
	clearCinBuffer();
	return userInput;
}

bool UI::checkMainMenuInputValidation(int io_UserInput)
{
	return io_UserInput >= 1 && io_UserInput <= 3;
}

void UI::printMainMenu()
{
	cout << "----------------------------------------------" << endl;
	cout << "Please choose one of the following:" << endl;
	cout << "1. Calculate Expression." << endl;
	cout << "2. Show History." << endl;
	cout << "3. Exit" << endl;
	cout << "----------------------------------------------" << endl;
}

void UI::clearScreen()
{
	system("cls");
}

void UI::runCalculation()
{
	clearCinBuffer();
	cout << "Please enter expression, without writing '=' at the end:" << endl;
	getline(cin, m_Str);
	calculateExpression();
}

void UI::calculateExpression()
{
	m_CalcManager.SetExpression(m_Str);
	m_IsValid = m_CalcManager.Validation();
	if (m_IsValid)
	{
		m_CalcManager.Calculate();
		m_Str.append("=");
		m_Str.append(m_CalcManager.GetExpression());
		cout << "The calculation is:" << endl;
		cout << m_Str << endl;
		m_HistoryList.push_back(m_Str);
	}
	else
	{
		cout << "Not valid expression." << endl;
	}

	holdScreen();	
}

void UI::holdScreen()
{
	cout << "Press Enter key to continue" << endl;
	clearCinBuffer();
	cin.get();
	clearCinBuffer();
}

void UI::clearCinBuffer()
{
	cin.clear();//clear errors/bad flags on cin
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
}

void UI::exitCalculator()
{
	cout << "Thanks for using my calculator!" << endl;
	cout << "Made by Daniel Freund" << endl;
	cin.get();
}