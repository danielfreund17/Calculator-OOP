#ifndef MULTIPLY_CLASS_H
#define MULTIPLY_CLASS_H

#include "Operation.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

class MultiplyClass : public Operation
{
public:
	MultiplyClass() : Operation('*', 1){}
	virtual double Perform(double A, double B);
};
#endif