#include "../../include/logger/ConsoleLogger.h"
#include <stdio.h>
#include <assert.h>
using  namespace  cobra_win;



ConsoleLogger::ConsoleLogger()
{

}

ConsoleLogger::~ConsoleLogger()
{

}

bool   ConsoleLogger::write(char* pPtr)
{
	assert(pPtr != NULL);

	printf("%s", pPtr);

	return true;
}
