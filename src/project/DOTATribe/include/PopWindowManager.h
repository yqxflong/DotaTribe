//Name：PopWindowManager
//Function：弹窗管理器
//Author：尹强

#ifndef  _DOTA_PopWindowManager_H_
#define  _DOTA_PopWindowManager_H_

#include <include/common/Singleton.h>
#include <vector>
#include "../include/IPopWindow.h"

class PopWindowManager : public cobra_win::Singleton2<PopWindowManager>
{
public:
	bool isPaused;		//暂停弹出窗口标示
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