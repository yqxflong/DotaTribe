//Name��PopWindowManager
//Function������������
//Author����ǿ

#ifndef  _DOTA_PopWindowManager_H_
#define  _DOTA_PopWindowManager_H_

#include <include/common/Singleton.h>
#include <vector>
#include "../include/IPopWindow.h"

class PopWindowManager : public cobra_win::Singleton2<PopWindowManager>
{
public:
	bool isPaused;		//��ͣ�������ڱ�ʾ
	std::vector<IPopWindow*> m_vecPopWindowList;
public:
	PopWindowManager();
	virtual ~PopWindowManager(){}
	bool Init();
	void Tick();
	void Destroy();
	//
	void AddPopWindow(IPopWindow* popwin);
	void RemovePopWindow(IPopWindow* popwin);
	void ClearPopWindowList();
private:
	void _resetAllParams();

};
#endif