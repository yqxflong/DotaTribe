#include "../include/AnnouncementWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/VariableSystem.h"
#include "../include/CPublicVarReader.h"
#include "../include/SysLangDataManager.h"
#include "../include/AutoScrollLabelManager.h"
#include "../include/ClientConstDataManager.h"
#include "../include/DOTATribeApp.h"
#include "../include/IProcedure.h"
#include <cocos2d.h>
using  namespace  cocos2d;
 
#define   FOR_EACH_ANNOUCE_BEIGIN(count)   for(size_t annouceIndex=0;annouceIndex<count;annouceIndex++) {
#define   FOR_EACH_ANNOUCE_END			   }

  
AnnouncementWindow::AnnouncementWindow()
{
	m_WindowType   = _TYPED_WINDOW_ANNOUNCEMENT_WINDOW_;
	m_bModelWindow = true;
	m_SubType      = 0;
	m_bIsForceClearAnimation=false;
	m_bIsForceClearUnUseTex=false;
	m_bIsDurationWaitting=false;
	m_pBackGroundImage=NULL;
	m_vAutoScrollManagerList.clear();
	m_fAnnouceWaittingDuration=ClientConstDataManager::get_instance2()->getValueByKey(ANNOUNCEMENT_WATTING_DURING)/Millisecond_TIME_UNIT;
	m_nAnnoucementBGID=ClientConstDataManager::get_instance2()->getValueByKey(ANNOUCEMENT_BG_ID);
}

AnnouncementWindow::~AnnouncementWindow()
{

}

bool AnnouncementWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_ANNOUNCEMENTWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_ANNOUNCEMENTWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ANNOUNCEMENTWINDOW_, true);

	return IWindow::Init();
}

bool AnnouncementWindow::Load()
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

void AnnouncementWindow::Tick()
{  
	//侦测滚动管理是否到达生命周期
	if(!m_bIsDurationWaitting)
	{ 
		if(!AnnoucementDataHandler::get_instance2()->IsAnnoucementQueueEmpty())
		{   
			OnActiveCallHandler();
		}
	} 

	std::vector<AutoScrollLabelManager * >::iterator  annouce_iter=m_vAutoScrollManagerList.begin();
	while(annouce_iter!=m_vAutoScrollManagerList.end())
	{
		if(!(*annouce_iter)->GetValid())
		{
			(*annouce_iter)->Destroy();
			delete (*annouce_iter);
			annouce_iter=m_vAutoScrollManagerList.erase(annouce_iter);
			OnBackGroundDestroy();
			cocos2d::CCDelayTime * pDelayToActive=cocos2d::CCDelayTime::create(m_fAnnouceWaittingDuration);
			cocos2d::CCCallFunc  * pActiveCall=cocos2d::CCCallFunc::create(this,callfunc_selector(AnnouncementWindow::OnActiveCallHandler));
			cocos2d::CCActionInterval *pActionSequence=cocos2d::CCSequence::createWithTwoActions(pDelayToActive,pActiveCall);
			m_pRootNode->runAction(pActionSequence);
			continue;
		}
		++annouce_iter;
	}
	 
	 if(m_vAutoScrollManagerList.empty()&&AnnoucementDataHandler::get_instance2()->IsAnnoucementQueueEmpty())
	{
		Destroy();
		return ;
	}  
  
	IWindow::Tick();
}


void   AnnouncementWindow::OnBackGroundDestroy()
{ 
	if(m_pBackGroundImage!=NULL)
	{
		m_pBackGroundImage->removeFromParentAndCleanup(true);
		m_pBackGroundImage=NULL;
	}
}


void AnnouncementWindow::Destroy()
{
	//////////////////////////////////////////////////////////////////////////
	m_bIsDurationWaitting=false;
	m_pBackGroundImage=NULL;
	std::vector<AutoScrollLabelManager * >::iterator  annouce_iter=m_vAutoScrollManagerList.begin();
	while(annouce_iter!=m_vAutoScrollManagerList.end())
	{  
		(*annouce_iter)->Destroy();
	    delete   (*annouce_iter);
		++annouce_iter;
	}
	m_vAutoScrollManagerList.clear();
	 
	GetAnnouncementRootNode()->removeAllChildrenWithCleanup(true);

	//////////////////////////////////////////////////////////////////////////
	m_bIsForceClearUnUseTex=false;
	/*if(IsInAthleticsProcedure())
	m_bIsForceClearUnUseTex=false;*/

	IWindow::Destroy();
}

void AnnouncementWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_ANNOUNCEMENTWINDOW_)
	{  
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_ANNOUNCEMENTWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_ANNOUNCEMENTWINDOW_)
	{
		//to do
	}
}
 

void AnnouncementWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}


void    AnnouncementWindow::OnBackGroundInit()
{
	if(m_pBackGroundImage==NULL)
	{
		m_pBackGroundImage=cocos2d::CCSprite::create();
		m_pBackGroundImage->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(m_nAnnoucementBGID));
		m_pRootNode->addChild(m_pBackGroundImage,0);
	}
}



cocos2d::CCNode *   AnnouncementWindow::GetAnnouncementRootNode()
{ 
	return m_pRootNode;
}


void    AnnouncementWindow::OnActiveCallHandler()
{
	m_bIsDurationWaitting=false;
	 
	if(!AnnoucementDataHandler::get_instance2()->IsAnnoucementQueueEmpty())
	{
		 AnnoucementMemData tmpMemData;
		 AnnoucementDataHandler::get_instance2()->TopAnnoucementItem(tmpMemData);
		 if(!tmpMemData.getAnnoucementContent().empty())
		 {
			 m_bIsDurationWaitting=true;
			 AutoScrollLabelManager * pAutoScrollLabelManager=AutoScrollLabelManager::CreateAutoScrollLabelManager(GetAnnouncementRootNode(),tmpMemData.getAnnoucementCSSType(),tmpMemData.getAnnoucementContent());
			 if(pAutoScrollLabelManager)
			 {
				 OnBackGroundInit();
				 m_pBackGroundImage->setPosition(pAutoScrollLabelManager->GetBackGroundImagePos());
				 m_vAutoScrollManagerList.push_back(pAutoScrollLabelManager);
			 } 
		 }
		 AnnoucementDataHandler::get_instance2()->PopAnnoucementItem();
	} 
}


bool   AnnouncementWindow::IsInAthleticsProcedure()
{
	if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_ATHLETICS_PROCEDURE_)
	return true;
	return false;
}
