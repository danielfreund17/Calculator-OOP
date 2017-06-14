#ifndef _ADD_CLASS_H
#define _ADD_CLASS_H

#include "Operation.h"
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

class AddClass : public Operation
{
	
public:
	AddClass() : Operation('+', 2) {}
	virtual double Perform(double A, double B);
};
#endif