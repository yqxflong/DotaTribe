//Name��IPopWindow
//Function�����е����Ļ���
//Author����ǿ

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
		��Ҫ����̳в���д
	*/
	//��ʾ����
	virtual void ShowPopWindow();
	//�����Ѿ�����
	virtual void PopWindowDidHide();

	int GetPriorityByCurWindowDef(std::string key);
};

#endif