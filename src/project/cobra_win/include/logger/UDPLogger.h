#ifndef  _LC_COBRA_WIN_UDPLOGGER_H
#define  _LC_COBRA_WIN_UDPLOGGER_H


#include "ILogger.h"

namespace  cobra_win
{


class  UDPLogger : public ILogger
{
public:
	UDPLogger();
	virtual  ~UDPLogger();

public:
	/*
		初始化UDPLogger
	*/
	bool    init_logger(char* pIP, unsigned short port);
	/*
		销毁UDPLogger
	*/
	void    destroy_logger();

public:
	/*
		UDP发送
	*/
	virtual   bool   write(char* pPtr);
};


}


#endif
