#include "../../include/logger/UDPLogger.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
using  namespace  cobra_win;



UDPLogger::UDPLogger()
{

}

UDPLogger::~UDPLogger()
{
	destroy_logger();
}

bool   UDPLogger::init_logger(char* pIP, unsigned short port)
{
	assert(pIP!=NULL && strlen(pIP)>0);

	return true;
}

void   UDPLogger::destroy_logger()
{
	
}

bool   UDPLogger::write(char* pPtr)
{
	assert(pPtr != NULL);

	return true;
}
