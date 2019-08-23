
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器通信等待窗口  公共接口
//date:   2013/09/13
///////////////////////////////////////////////// 
#include "../include/CommunicationWaittingWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/TimeSystem.h"
#include "../include/EngineSystem.h"
#include "../include/ClientConstDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/NFControlsManager.h"

#define   WAITTING_ANIMATION_ID   2013		  //通信等待动画ID
#define   TIME_OUT_TXT_ID		  15		  //超时提示文本ID


using namespace std;

USING_NS_CC;

CommnunicationWattingWindow::CommnunicationWattingWindow()
{
	m_WindowType  =  _TYPED_WINDOW_COMMUNICATIONWAITTINGWINDOW_;
	waitTimeDuration=0.0f;
	isStartTimer=false;
	m_fTimerSecond = 0;
	m_bCheckTimeOut = false;
	m_bIsForceClearUnUseTex=false;
	m_bIsForceClearAnimation=false;
}

bool CommnunicationWattingWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_);
	RegisterEvent(_TYPED_EVENT_HIDE_COMMUNICATIONWAITTINGWIN_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_COMMUNICATIONWAITINGWIN_, true);
	 
	return IWindow::Init();
}

 

bool CommnunicationWattingWindow::Load()
{
	do 
	{
 		if (!IWindow::Load())
			break;
		
		m_fTimerSecond = (float)CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_COMMUNICATION_TIMEOUT) / Millisecond_TIME_UNIT;
		m_bCheckTimeOut = true;
		//
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCOMMUNICATINGWINDOW,m_pRootNode);
		return true;
	} 
	while (false);

	return false;
}

void CommnunicationWattingWindow::Tick()
{
	if(isStartTimer)
	{
		waitTimeDuration = 1.0*(TimeSystem::get_instance2()->GetCurrentMicroSecond() - startTimerCount)/Microsecond_TIME_UNIT;
	}

	if(waitTimeDuration >= m_fTimerSecond && m_bCheckTimeOut)
	{
		m_bCheckTimeOut = false;
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_COMMUNICATIONWAITTINGWIN_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_COMMUNICATION_TIMEOUT_);

		/*std::string timeOutStr=SysLangDataManager::get_instance2()->GetSysLangById(TIME_OUT_TXT_ID); 
		NFC_showErrorTips_2(timeOutStr);*/
	}

	IWindow::Tick();
}
 

void CommnunicationWattingWindow::Destroy()
{
	IWindow::Destroy();
}

void CommnunicationWattingWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_)
	{
		if(m_pRootNode->isVisible())
		return ;
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_COMMUNICATIONWAITTINGWIN_)
	{
		OnStopTimer();
		Destroy();
	}
	else if(iEventType==_TYPED_EVENT_UPDATE_COMMUNICATIONWAITINGWIN_)
	{

	}
}

void CommnunicationWattingWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if(paramList.size() == 1)
	{
		std::string time = *paramList.begin();
		if(time == "-1")
		{
			m_bCheckTimeOut = false;
		}
		else
		{
			m_bCheckTimeOut = true;
			sscanf(time.c_str(), "%f", &m_fTimerSecond);
		}
	}

	cocos2d::CCNode * pWaittingLayer=NFC_getNode(kGRAYLAYER,m_pRootNode);
	if(pWaittingLayer!=NULL)
	{
		cocos2d::CCSprite *  commonicationNode=(cocos2d::CCSprite *)NFC_getNode(kANISPRITE,m_pRootNode);
		if(commonicationNode)
		{ 
			cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(WAITTING_ANIMATION_ID);
			if(pAnimation!=NULL)
			{
				CCAnimationEffect   *  pAnimationEffect=CCAnimationEffect::create(commonicationNode,pAnimation);
				if(pAnimationEffect!=NULL)
				{ 
					cocos2d::CCRepeatForever * foreverAction=cocos2d::CCRepeatForever::create(pAnimationEffect);
					commonicationNode->runAction(foreverAction);
				}
			}
		}
		pWaittingLayer->setVisible(true);
	}
	//开始计时
	OnStartTimer();
	Show(true);
}



void   CommnunicationWattingWindow::OnStartTimer() 	//开始计时
{
	waitTimeDuration=0.0f;
	isStartTimer=true;
	startTimerCount=TimeSystem::get_instance2()->GetCurrentMicroSecond();
}

void  CommnunicationWattingWindow::OnStopTimer() 	//结束计时
{
	isStartTimer=false;
	startTimerCount=0l;
}
