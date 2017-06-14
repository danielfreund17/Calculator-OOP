#ifndef _SUBTRACT_CLASS_H
#define _SUBTRACT_CLASS_H

#include "Operation.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

class SubtractClass : public Operation
{
public:
	SubtractClass() : Operation('-', 2) {}
	virtual double Perform(double A, double B);
};
#endif