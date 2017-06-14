#ifndef _DIVIDE_CLASS_H
#define _DIVIDE_CLASS_H

#include "Operation.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

class DivideClass : public Operation
{
public:
	DivideClass() : Operation('/', 1) {}
	virtual double Perform(double A, double B);
};
#endif