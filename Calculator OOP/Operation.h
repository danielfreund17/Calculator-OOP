#ifndef _OPERATION_H
#define _OPERATION_H
using namespace std;

class Operation
{
protected:
	const char m_Sign;
	const int m_Priority;
public:
	Operation(const char sign, const int priority) : m_Sign(sign), m_Priority(priority) {}
	virtual double Perform(double A, double B) = 0;
	char GetSign() { return m_Sign; } 
	int GetPriority() { return m_Priority; }
};
#endif