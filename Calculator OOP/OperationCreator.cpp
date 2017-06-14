#include "OperationCreator.h"

Operation * OperationCreator::CreateOperation(char i_Sign)
{
	Operation *operation = NULL;
	switch (i_Sign)
	{
	case ADD:
		operation = new AddClass();
		break;
	case SUBTRACT:
		operation = new SubtractClass();
		break;
	case MULTIPLY:
		operation = new MultiplyClass();
		break;
	case DIVIDE:
		operation = new DivideClass();
		break;
	}

	return operation;
}