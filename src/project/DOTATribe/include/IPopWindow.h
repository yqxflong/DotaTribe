//Name：IPopWindow
//Function：所有弹窗的基类
//Author：尹强

#ifndef  _DOTA_IPopWindow_H_
#define  _DOTA_IPopWindow_H_

#include "../include/IPopDef.h"
#include <string>

class IPopWindow{
public:
	int priority_;
public:
	IPopWindow();
	virtual ~IPopWindow();
	/*
		需要子类继承并重写
	*/
	//显示弹窗
	virtual void ShowPopWindow();
	//弹窗已经隐藏
	virtual void PopWindowDidHide();

	int GetPriorityByCurWindowDef(std::string key);
};

#endif