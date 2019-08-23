#include "../include/ForcePushTaskRewardWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/WindowManager.h"
#include "../include/NFControlsManager.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/MainTaskPacket.h"
#include "../include/RoleInfoDataHandler.h"
#include <cocos2d.h>
#include "../include/PopWindowManager.h"

////////////////////////////////////////////////////////////////
//Name:	 ForcePushTaskRewardWindow
//Auchor: 	xiaobo.wu
//Func:	 强制推送任务奖励窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

using  namespace  cocos2d;


#define   TASK_NAME_FONT_STYLE_ID	    84
#define   TASK_COMPLETE_FONT_STYLE_ID	83
#define   TASK_FINIS_TXT_ID			    915



#define    _REWARD_OBJECT_TIPS_(index)		if(m_pActiveRewardItem!=NULL) \
{\
	if(m_pActiveRewardItem->rewardVector.size()>index)\
	{\
		MainTaskReward * pTaskItem=m_pActiveRewardItem->rewardVector.at(index); \
		if(pTaskItem->type==kDT_AWARD_OBJECT) \
		{ \
			NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pTaskItem->templateId, _TYPED_WINDOW_FORCEPUSHTASKREWARD_WINDOW_); \
		}\
	}\
}\



ForcePushTaskRewardWindow::ForcePushTaskRewardWindow()
{
	m_WindowType   = _TYPED_WINDOW_FORCEPUSHTASKREWARD_WINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
	m_pActiveRewardItem=NULL;
	m_bIsShowingReward=false;
	m_getReward = true;
}

ForcePushTaskRewardWindow::~ForcePushTaskRewardWindow()
{  
}

bool ForcePushTaskRewardWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_FORCEPUSHTASKREWARDWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_FORCEPUSHTASKREWARDWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_FORCEPUSHTASKWORDWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_CLEAR_FORCEPUSHTASKWORDWINDOW_, true);
	 
	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_TASK_AWARD);
	return IWindow::Init();
}

bool ForcePushTaskRewardWindow::Load()
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

void ForcePushTaskRewardWindow::Tick()
{    
	IWindow::Tick();
}

void ForcePushTaskRewardWindow::Destroy()
{    
	//
	PopWindowDidHide();
	//
	MainTaskDataHandler::get_instance2()->PopPromptRewardItem();
	m_pActiveRewardItem=NULL;
	IWindow::Destroy();
	m_bIsShowingReward=false;
	m_getReward = true;
	if(MainTaskDataHandler::get_instance2()->IsHadNextRewardItem())
	{
		PushEvent(_TYPED_EVENT_SHOW_FORCEPUSHTASKREWARDWINDOW_);
	}
}

//显示弹窗
void ForcePushTaskRewardWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
//弹窗已经隐藏
void ForcePushTaskRewardWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void  ForcePushTaskRewardWindow::DestroyWinAndMemData(bool isNeedToClear)
{
	if(isNeedToClear)
	{ 
		Destroy();
		return ;
	} 
	m_pActiveRewardItem=NULL;
	m_bIsShowingReward=false;
	IWindow::Destroy();
}
void ForcePushTaskRewardWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_FORCEPUSHTASKREWARDWINDOW_)
	{ 
		 PopWindowManager::get_instance2()->AddPopWindow(this);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_FORCEPUSHTASKREWARDWINDOW_)
	{
		if (!willLevelUp() && !LevelUpDataHandler::get_instance2()->LevelUpDataList.size()>0)
			PushEvent(_TYPED_EVENT_SHOW_MISSIONMESSAGEBOX_);
		Destroy();
		LevelUpDataHandler::get_instance2()->m_showFlag=true; 
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_FORCEPUSHTASKWORDWINDOW_)
	{ 
	}
	else if( iEventType==_TYPED_EVENT_CLEAR_FORCEPUSHTASKWORDWINDOW_)
	{
		MainTaskDataHandler::get_instance2()->DestroyAllRewardItem();
		DestroyWinAndMemData(false);
	}
	 
}

void ForcePushTaskRewardWindow::OnShowWindowEventHandler()
{
 
}

void ForcePushTaskRewardWindow::ShowWindow(){
	if(!m_pRootNode->isVisible())
	{
		initUIAndData();
		Show(true);
	}
}
 
 

void    ForcePushTaskRewardWindow::initUILayout()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kFORCEPUSHREWARDWINDOW,GetWindowRootLayer());    
	bindStaticBtn();
}


void    ForcePushTaskRewardWindow::initUIAndData()
{ 
	if(attachMemData())
	{
		m_bIsShowingReward=true;
		initUILayout();
		updateUIWithMemData();
		Show(true);
	}
	else
	{
		Destroy();
	}
}

bool    ForcePushTaskRewardWindow::attachMemData()
{
	m_pActiveRewardItem=MainTaskDataHandler::get_instance2()->FrontPromptRewardItem();
	if(m_pActiveRewardItem)
	{
		return true;
	}
	return false;
}

 
void    ForcePushTaskRewardWindow::updateUIWithMemData()
{      
	std::string taskNameRichStr=NFC_getRichTextCSSByFontStyleID(TASK_NAME_FONT_STYLE_ID,"");
	char taskName[256]={0};
	sprintf(taskName,taskNameRichStr.c_str(),m_pActiveRewardItem->taskName.c_str());
	std::string  taskComplete=taskName;
	taskComplete+=SysLangDataManager::get_instance2()->GetSysLangById(TASK_FINIS_TXT_ID).c_str();
	cocos2d::CCMultiLineLabelTTF * pTaskCompleteLabel=(cocos2d::CCMultiLineLabelTTF *)GetWindowRootLayer()->getChildByTag(_UI_TASK_TILE_TAG_);
	pTaskCompleteLabel->setString(taskComplete.c_str());
	ShowTaskRewardInfo();
}


void    ForcePushTaskRewardWindow::detachMemData()
{

}

cocos2d::CCNode * ForcePushTaskRewardWindow::GetWindowRootLayer()
{
	return m_pRootNode;
}


void    ForcePushTaskRewardWindow::bindStaticBtn()
{
	 bindSelectorForBtn(_UI_CLOSE_BTN_TAG_);
	 bindSelectorForBtn(_UI_TASK_REWARD_BTN_TAG_);
	 bindSelectorForTouchSprite(_UI_TASK_ITEM1_OBJ_TAG_);
	 bindSelectorForTouchSprite(_UI_TASK_ITEM2_OBJ_TAG_);
	 bindSelectorForTouchSprite(_UI_TASK_ITEM3_OBJ_TAG_);

}
void    ForcePushTaskRewardWindow::bindSelectorForBtn(int btnUIIndex)
{
	cocos2d::CCMenu * pMemu=(cocos2d::CCMenu *)GetWindowRootLayer()->getChildByTag(btnUIIndex);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(btnUIIndex);
			pMenuItem->setTarget(this,menu_selector(ForcePushTaskRewardWindow::btnSelectorHandler));
		}
	} 
}
void    ForcePushTaskRewardWindow::bindSelectorForTouchSprite(int spriteUIIndex)
{
	DTAwardBoard * pTouchSprite=(DTAwardBoard *)GetWindowRootLayer()->getChildByTag(spriteUIIndex);
	if(pTouchSprite!=NULL)
	{
		pTouchSprite->setIDX(spriteUIIndex);
		pTouchSprite->setTarget(this,menu_selector(ForcePushTaskRewardWindow::OnAwardClicked));
	}
}


void    ForcePushTaskRewardWindow::setNodeVisiableByTag(bool isVisiable,int nodeUIIndex)
{
	cocos2d::CCNode * pSubNode=(cocos2d::CCNode *)GetWindowRootLayer()->getChildByTag(nodeUIIndex);
	if(pSubNode)
	{
		pSubNode->setVisible(isVisiable);
	}
}



void   ForcePushTaskRewardWindow::btnSelectorHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
		case _UI_CLOSE_BTN_TAG_:
			{   
				/*
				关闭按钮
				*/
				m_getReward = false;
				PushEvent(_TYPED_EVENT_HIDE_FORCEPUSHTASKREWARDWINDOW_);
				break;
			}
		case _UI_TASK_REWARD_BTN_TAG_:
			{ 
				/*
				领取奖励
				*/		 
				rewardHandler();
				break;
			}
		default:
			break;
		}
	}
}

void ForcePushTaskRewardWindow::OnAwardClicked(cocos2d::CCObject* pSender){
	CMenuItemSprite * pTouchSprite=(CMenuItemSprite *)pSender;
	if(pTouchSprite)
	{
		switch(pTouchSprite->getIDX())
		{
		case _UI_TASK_ITEM1_OBJ_TAG_:
			{
				_REWARD_OBJECT_TIPS_(0)	
					break;
			}
		case _UI_TASK_ITEM2_OBJ_TAG_:
			{
				_REWARD_OBJECT_TIPS_(1)	
					break;
			}
		case _UI_TASK_ITEM3_OBJ_TAG_:
			{
				_REWARD_OBJECT_TIPS_(2)	
					break;
			}
		default:
			break;
		}
	}
}

 void  ForcePushTaskRewardWindow::ShowTaskRewardInfo()
{
	/*
	 隐藏当前奖励内容
	*/  
	bindSelectorForTouchSprite(_UI_TASK_ITEM1_OBJ_TAG_);
	bindSelectorForTouchSprite(_UI_TASK_ITEM2_OBJ_TAG_);
	bindSelectorForTouchSprite(_UI_TASK_ITEM3_OBJ_TAG_);

	DTAwardBoard* award=(DTAwardBoard*)GetWindowRootLayer()->getChildByTag(_UI_TASK_ITEM1_OBJ_TAG_);
	award->ChangeObject();
	setNodeVisiableByTag(false,_UI_TASK_ITEM1_NUM_TAG_);

	award=(DTAwardBoard*)GetWindowRootLayer()->getChildByTag(_UI_TASK_ITEM2_OBJ_TAG_);
	award->ChangeObject();
	setNodeVisiableByTag(false,_UI_TASK_ITEM2_NUM_TAG_);

	award=(DTAwardBoard*)GetWindowRootLayer()->getChildByTag(_UI_TASK_ITEM3_OBJ_TAG_);
	award->ChangeObject();
	setNodeVisiableByTag(false,_UI_TASK_ITEM3_NUM_TAG_);
 
	if(m_pActiveRewardItem!=NULL)
	{ 
		size_t  rewardCount=m_pActiveRewardItem->rewardVector.size();
		int  bgIndex=-1;
		int  iconIndex=-1;
		int  numIndex=-1;
		char  commonStr[32]={0};
		COMMON_BEGIN_VECTOR(rewardCount)
		   getRewardBgAndIconTagByIndex(index,bgIndex,iconIndex,numIndex);
		    MainTaskReward * pRewardItem=m_pActiveRewardItem->rewardVector.at(index);
			award=(DTAwardBoard*)GetWindowRootLayer()->getChildByTag(iconIndex);
			setNodeVisiableByTag(true,iconIndex);
			int quality=-1;
			int iconid=-1;
			bool isEnabled=false;
		    switch (pRewardItem->type)
		    {
			case  kDT_AWARD_OBJECT:
				{     
					quality=pRewardItem->quality;
					iconid=pRewardItem->iconId;
					isEnabled=true;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,GetWindowRootLayer(),commonStr,true);
					break;
				}
			case   kDT_AWARD_MONEY:
				{   
					quality=_GOLD_QUALITY_RESID_;
					iconid=_GOLD_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,GetWindowRootLayer(),commonStr,true);
					break;
				}
			case  kDT_AWARD_EXP:
				{
					quality=_EXP_QUALITY_RESID_;
					iconid=_EXP_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,GetWindowRootLayer(),commonStr,true);
					break;
				}
				case  kDT_AWARD_DIAMOND:
				{
					quality=_DIAMOND_QUALITY_RESID_;
					iconid=_DIAMOND_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,GetWindowRootLayer(),commonStr,true);
					break;
				}
				case kDT_AWARD_PRESTIGE:
				{
					quality=_PREGIST_QUALITY_RESID_;
					iconid=_PREGIST_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,GetWindowRootLayer(),commonStr,true);
					break;
				}
				case kDT_AWARD_POWER:
				{
					quality=_POWER_QUALITY_RESID_;
					iconid=_POWER_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,GetWindowRootLayer(),commonStr,true);
					break;
				}
		    }
			award->ChangeObject(quality,iconid);
			award->setEnabled(isEnabled);
 		COMMON_END_ARRAY
 	}
}



 void  ForcePushTaskRewardWindow::getRewardBgAndIconTagByIndex(size_t & index,int & bgIconTag,int & IconTag,int & numTag)
 {
	 switch(index)
	 {
	 case  0:
		 {
			 bgIconTag=-1;
			 IconTag=_UI_TASK_ITEM1_OBJ_TAG_;
			 numTag=_UI_TASK_ITEM1_NUM_TAG_;
			 break;
		 }
	 case 1:
		 {
			 bgIconTag=-1;
			 IconTag=_UI_TASK_ITEM2_OBJ_TAG_;
			 numTag=_UI_TASK_ITEM2_NUM_TAG_;
			 break;
		 }
	 case  2:
		 {
			 bgIconTag=-1;
			 IconTag=_UI_TASK_ITEM3_OBJ_TAG_;
			 numTag=_UI_TASK_ITEM3_NUM_TAG_;
			 break;
		 }
	 default:
		 {
			 bgIconTag=-1;
			 IconTag=-1;
			 numTag=-1;
			 break;
		 }
	 }
 }

 void    ForcePushTaskRewardWindow::rewardHandler()
 { 
	 //to do
	 if(m_pActiveRewardItem!=NULL)
	 {    
		 CCLOG("ForcePushTaskRewardWindow RewardHandler!");
		 CSGetTaskRewardSinglePacket  singleRewardRequest(m_pActiveRewardItem->taskID);
		 singleRewardRequest.Send();
		 PushEvent(_TYPED_EVENT_HIDE_FORCEPUSHTASKREWARDWINDOW_);
	 }
 }
  
 bool    ForcePushTaskRewardWindow::willLevelUp()
 { 
	 //to do
	 int exp = 0;
	 if (MainTaskDataHandler::get_instance2()->m_promptRewardDeque.size()>0&&m_getReward)
	 {
		 PromptRewardInfoData* pData = MainTaskDataHandler::get_instance2()->m_promptRewardDeque[0];
		 for (int i=0;i<pData->rewardVector.size();i++)
		 {
			 MainTaskReward* rewardData = pData->rewardVector[i];
			 if (rewardData->type == kDT_AWARD_EXP)
			 {
				 exp += rewardData->num;
			 }
		 }

		
		 if (ROLEINFODATAHANDLER->m_pRIData->exp_+ exp >= ROLEINFODATAHANDLER->m_pRIData->maxExp_)
			return true;
	 }
	 m_getReward = true;
	 return false;
 }
