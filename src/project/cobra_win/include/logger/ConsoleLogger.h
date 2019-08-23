#ifndef  _LC_COBRA_WIN_CONSOLELOGGER_H
#define  _LC_COBRA_WIN_CONSOLELOGGER_H


#include "ILogger.h"

namespace  cobra_win
{


class  ConsoleLogger : public ILogger
{
public:
	ConsoleLogger();
	virtual  ~ConsoleLogger();

public:
	/*
		打印到控制台
	*/
	virtual   bool   write(char* pPtr);
};


}



#endif
