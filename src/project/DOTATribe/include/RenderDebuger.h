#ifndef  _DOTATRIBE_RENDERDEBUGER_H_
#define  _DOTATRIBE_RENDERDEBUGER_H_


#include "IDebuger.h"

class RenderDebuger : public IDebuger
{
public:
	RenderDebuger();
	virtual ~RenderDebuger();

public:
	/*
		初始化调试器
	*/
	virtual  bool  Init();
	/*
		逻辑桢更新
	*/
	virtual  void  Tick();
	/*
		销毁调试器
	*/
	virtual  void  Destroy();
};


#endif
