#ifndef  _LC_COBRA_WIN_ILOGGER_H
#define  _LC_COBRA_WIN_ILOGGER_H


#include "../common/NonCopyable.h"

namespace  cobra_win
{


class  ILogger : public NonCopyable
{
public:
	ILogger();
	virtual  ~ILogger();

public:
	/*
		记录
	*/
	virtual   bool   write(char* pPtr)         =         0;
};


}



#endif
