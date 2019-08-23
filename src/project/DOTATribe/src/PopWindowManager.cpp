//Name：PopWindowManager
//Function：弹窗管理器
//Author：尹强

#include "../include/PopWindowManager.h"
#include "../include/LoggerSystem.h"

using namespace std;

PopWindowManager::PopWindowManager(){
	_resetAllParams();
}

bool PopWindowManager::Init(){
	_resetAllParams();

	return true;
}
void PopWindowManager::Tick(){
	if (isPaused)return;
	if (m_vecPopWindowList.size()>0)
	{
		IPopWindow* popwin=m_vecPopWindowList.front();
		popwin->ShowPopWindow();
	}
}
void PopWindowManager::Destroy(){
	_resetAllParams();
}

void PopWindowManager::AddPopWindow(IPopWindow* popwin){
	m_vecPopWindowList.push_back(popwin);
	//优先级从高到低排序
	for (int i=1; i<(int)m_vecPopWindowList.size();i++){
		for (int j=0;j<i;j++){
			IPopWindow* tmp=m_vecPopWindowList[i];
			int priority_i=tmp->priority_;
			int priority_j=m_vecPopWindowList[j]->priority_;
			if (priority_i>priority_j){
				m_vecPopWindowList[i]=m_vecPopWindowList[j];
				m_vecPopWindowList[j]=tmp;
			}
		}
	}

	LOGGERSYSTEM->LogInfo("=======PopWindowManager::AddPopWindow=========count:%d",m_vecPopWindowList.size());
}
void PopWindowManager::RemovePopWindow(IPopWindow* popwin){
	vector<IPopWindow*>::iterator it;
	for (it=m_vecPopWindowList.begin();it<m_vecPopWindowList.end();it++)
	{
		if (*it==popwin){
			m_vecPopWindowList.erase(it);
			break;
		}
	}

	LOGGERSYSTEM->LogInfo("=======PopWindowManager::RemovePopWindow=========count:%d",m_vecPopWindowList.size());
}

void PopWindowManager::ClearPopWindowList(){
	_resetAllParams();

	LOGGERSYSTEM->LogInfo("=======PopWindowManager::ClearPopWindowList=========");
}

void PopWindowManager::_resetAllParams(){
	isPaused=false;
	m_vecPopWindowList.clear();
}


