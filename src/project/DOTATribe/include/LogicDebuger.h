#ifndef  _DOTATRIBE_LOGICDEBUGER_H_
#define  _DOTATRIBE_LOGICDEBUGER_H_


#include "IDebuger.h"

class LogicDebuger : public IDebuger
{
public:
	LogicDebuger();
	virtual ~LogicDebuger();

public:
	//@标配
	virtual  bool  Init();
	virtual  void  Tick();
	virtual  void  Destroy();
};


#endif
