#ifndef _OPERATION_CREATOR_H
#define _OPERATION_CREATOR_H
#include "Operation.h";
#include "AddClass.h"
#include "DivideClass.h"
#include "SubtractClass.h"
#include "MultiplyClass.h"
#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'

class OperationCreator
{
public:
	Operation * CreateOperation(char);
};
#endif
