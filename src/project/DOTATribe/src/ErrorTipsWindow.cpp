#include "../include/ErrorTipsWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/ErrorTipsDataManager.h"
#include "../include/CPublicVarReader.h"
#include <cocos2d.h>

 
ErrorTipsWindow::ErrorTipsWindow()
{
	m_WindowType   = _TYPED_WINDOW_ERRORTIPSWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZOREDR_TOP_;	 
	m_ErrorTipsManagerList.clear();
	m_pErrorTipsData=ErrorTipsDataManager::get_instance2()->GetErrorTipsData();
	m_vCacheContent.clear();
}

ErrorTipsWindow::~ErrorTipsWindow()
{
	
}

bool ErrorTipsWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_ERRORTIPSWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_ERRORTIPSWINDOW_, true);
	RegisterEvent(_TYPEF_EVENT_UPDATE_ERRPRTIPSWINDOW_, true);


	return IWindow::Init();
}

bool ErrorTipsWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		return true;
	} 
	while (false);

	return false;
}

void ErrorTipsWindow::Tick()
{ 
	//若在战斗流程，加载前 不进行Tick
	bool m_bPauseLeapTips=false;
	GET_WEAK_TIPS_SYSTEM(m_bPauseLeapTips)
	if(!m_bPauseLeapTips)
	{ 
		if(!m_vCacheContent.empty())
		{
			size_t contentCount=m_vCacheContent.size();
			for(size_t index=0;index<contentCount;index++)
			OnShowTipsContent(m_vCacheContent.at(index));
			m_vCacheContent.clear();
		}
	}  
	std::list<AutoFadeOutLabelManager * >::iterator  label_iter=m_ErrorTipsManagerList.begin();
	while(label_iter!=m_ErrorTipsManagerList.end())
	{
		if(!(*label_iter)->GetIsValid())
		{
			(*label_iter)->Destroy();
			delete (*label_iter);
			m_ErrorTipsManagerList.erase(label_iter++);
			continue;
		}
		++label_iter;
	}
    if(m_ErrorTipsManagerList.empty())
	{
		Destroy();
		return ;
	}
	IWindow::Tick();
}

void ErrorTipsWindow::Destroy()
{ 
	DestroyAllAction();
	IWindow::Destroy();
}


cocos2d::CCNode *  ErrorTipsWindow::GetErrorTipsRoorNode()
{
	 return m_pRootNode;
}


void   ErrorTipsWindow::DestroyAllAction()
{
	std::list<AutoFadeOutLabelManager * >::iterator  label_iter=m_ErrorTipsManagerList.begin();
	while(label_iter!=m_ErrorTipsManagerList.end())
	{
		(*label_iter)->Destroy();
		delete (*label_iter);
		++label_iter;
	}
	m_ErrorTipsManagerList.clear();

} 

void ErrorTipsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_ERRORTIPSWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_ERRORTIPSWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPEF_EVENT_UPDATE_ERRPRTIPSWINDOW_)
	{
	    OnUpdateUITextEventHandler(paramList);
	}
}

void ErrorTipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if(paramList.empty())
		return;
	bool m_bPauseLeapTips=false;
	GET_WEAK_TIPS_SYSTEM(m_bPauseLeapTips)
	if(m_bPauseLeapTips)
	{
		m_vCacheContent.push_back(*(paramList.begin()));
		return ;
	}
	OnShowTipsContent(*(paramList.begin()));
}


void  ErrorTipsWindow::OnShowTipsContent(std::string tipsContent)
{
	if(tipsContent.empty())
	return ;

	//显示Pop
	//判断当前的列表数目
	size_t  countSize=m_ErrorTipsManagerList.size();
	if(countSize>=(size_t)m_pErrorTipsData->errorMaxLevel)
	{
		if(m_pErrorTipsData->errorMaxLevel<=1)
		{
			std::list<AutoFadeOutLabelManager * >::iterator iter=m_ErrorTipsManagerList.begin();
			if(iter!=m_ErrorTipsManagerList.end())
			{
				(*iter)->Destroy();
				delete (*iter);
			}
			m_ErrorTipsManagerList.clear();
			AutoFadeOutLabelManager *  pAutoFadeManager=AutoFadeOutLabelManager::CreateAutoFadeOutLabelManager(GetErrorTipsRoorNode(),1,tipsContent);
			m_ErrorTipsManagerList.push_back(pAutoFadeManager);
		}
		else
		{ 
			std::list<AutoFadeOutLabelManager * >::iterator iter=m_ErrorTipsManagerList.begin();
			while (iter!=m_ErrorTipsManagerList.end())
			{
				if((*iter)->GetIndex()== m_pErrorTipsData->errorMaxLevel)
				{
					(*iter)->Destroy();
					delete (*iter);
					m_ErrorTipsManagerList.erase(iter++);
					continue;
				}
				++iter;
			}
			std::list<AutoFadeOutLabelManager * >::iterator iter_second=m_ErrorTipsManagerList.begin();
			while (iter_second!=m_ErrorTipsManagerList.end())
			{ 
				(*iter_second)->SetIndex((*iter_second)->GetIndex()+1);
				++iter_second;
			} 
			AutoFadeOutLabelManager *  pAutoFadeManager=AutoFadeOutLabelManager::CreateAutoFadeOutLabelManager(GetErrorTipsRoorNode(),1,tipsContent);
			m_ErrorTipsManagerList.push_back(pAutoFadeManager);
		} 
	}
	else
	{ 
		std::list<AutoFadeOutLabelManager * >::iterator iter=m_ErrorTipsManagerList.begin();
		while (iter!=m_ErrorTipsManagerList.end())
		{ 
			(*iter)->SetIndex((*iter)->GetIndex()+1);
			++iter;
		}  
		AutoFadeOutLabelManager *  pAutoFadeManager=AutoFadeOutLabelManager::CreateAutoFadeOutLabelManager(GetErrorTipsRoorNode(),1,tipsContent);
		m_ErrorTipsManagerList.push_back(pAutoFadeManager);

	}  
	if(!m_pRootNode->isVisible())
	{
		Show(true);
	}
}


void ErrorTipsWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{

} 