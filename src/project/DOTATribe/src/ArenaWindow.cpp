#include "../include/ArenaWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/ArenaInfoDataHandler.h"
#include "../include/TimeSystem.h"
#include "../include/C2SChallengePacket.h"
#include "../include/C2SBattleRecordPacket.h"
#include "../include/C2SAddChallengeCountPacket.h"
#include "../include/AddChallengeDataHandler.h"
#include "../include/IProcedure.h"
#include "../include/C2SArenaRankPacket.h"
#include "../Include/C2SArenaGifPacket.h"
#include "../include/C2SArenaInfoPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/GuideSystem.h"
#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/config_HomeWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/C2SArenaInfoPacket.h"


using  namespace  cocos2d;
using namespace cocos2d::extension;

  ////////////////////////////////////////////////////////////////
  //Name:	 ArenaWindow
  //Auchor: 	xiaobo.wu
  //Func:	 竞技场窗口
  //Maintainer: 	xiaobo.wu
  //date:   2014/01/03
  ////////////////////////////////////////////////////////////////

#define   _REWARD_PRESTIGE_VALUE_			460
#define   _ARENA_RANK_VALUE_				462
#define   _ARENE_FIGHT_ABILITY_				463
#define   _LEVEL_CONETNTE_TET_ID_			464
#define   _ARENE_COLL_TIME_VALUE_			465
#define   _TODAY_CAN_CHALLENGE_NUM_			466
#define   _ENMEY_NAME_CONTENT_				467
#define   _ARENA_HISTORY_BATTLE_1_			468			//刚刚
#define   _ARENA_HISTORY_BATTLE_2_			469			//昨天
#define   _ARENA_HISTORY_BATTLE_3_			470			//%d天前
#define	  _ARENA_BATTLE_PLAY_LOST_			471			//你战败了！		
#define	  _ARENA_HISTORY_PLAY_WIN_			472			//你战胜了！
#define   _ARENA_HISTORY_PLAY_NO_CHANGE_	473			//排名不变
#define   _ARENA_HISTORY_PLAY_RANK_UP_		474		 	//排名上升
#define   _ARENA_HISTORY_PLAY_RANK_DOWN_	475			//排名下降
#define   _ARENA_HISTORY_BATTLE_PLAY_		476			//挑战了你
#define   _ARENA_HISTORY_PALY_BATTLE_		478			//你挑战了
 
#define   _WIN_IMAGE_RESOURCE_ID_    558
#define   _LOST_IMAGE_RESOURCE_ID_   559
 
#define   _MAX_CHALLENGE_NUM_		5
 

ArenaWindow::ArenaWindow()
{
	m_WindowType   = _TYPED_WINDOW_ARENAWINDOW_;
	m_bModelWindow = false;
	m_SubType      = 0;
	preWidnowEnumType=0;   //之前窗口的枚举类型
	m_pBaseNode=NULL;
	m_pTable=NULL;
	isNeedToUpdateTimeForReward=false; 
	tmpPlayInstanceID=0;
	m_historyArenaVec.clear();

	m_bIsInitlayout=false;
	m_iBackWindow = 0;
	m_iBackSubview = "0";
	m_mStaticBtnMap.clear();
}

ArenaWindow::~ArenaWindow()
{

}

bool ArenaWindow::Init()
{ 
	RegisterEvent(_TYPEF_EVENT_SHOW_ARENAWINDOW_);
	RegisterEvent(_TYPEF_EVENT_SEND_ARENAREQUEST_);
	RegisterEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_, true);
	RegisterEvent(_TYPEF_EVENT_UPDATE_ARENEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);
	RegisterEvent(_TYPEF_EVENT_UPDATE_ADDCHALLENGE_,true);
	RegisterEvent(_TYPEF_EVENT_UPDATE_REWARDDISTANCE_,true);
	RegisterEvent(_TYPEF_EVENT_HINT_ARENAWINDOW_AWARD_,true);
	return IWindow::Init();
}

bool ArenaWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break; 
	} 
	while (false);

	return false;
}

	/*
		检查新功能开启
	*/
void ArenaWindow::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_2_AREANA)){
		//======显示帮助界面======
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,_to_event_param_(UIViewDataManager::kARENA_HELP_));
		NFC_setNodeVisable(_ARENA_ARROW_MOVE_TAG_,m_pBaseNode,true);
		//=======结束新功能开启=========
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_2_AREANA);
	}
}

void ArenaWindow::Tick()
{
	IWindow::Tick();
	 
}

  


void ArenaWindow::Destroy()
{ 
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
	//判断是否经过初始化
	if(m_bIsInitlayout)
	{
		m_bIsInitlayout=false;
		DestroyData();
		if(m_pBaseNode!=NULL)
		{
			m_pBaseNode->removeAllChildrenWithCleanup(true); 
			m_pBaseNode->removeFromParentAndCleanup(true);
		}

		m_pRootNode->removeAllChildrenWithCleanup(true);
		UIVIEWDATAMANAGER->clearData();
	}  
	IWindow::Destroy();
}




void ArenaWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPEF_EVENT_SHOW_ARENAWINDOW_ )
	{
		LoadUIControl();
		OnShowWindowEventHandler(paramList);
		_checkAwardHint();
	}
	else if(iEventType==_TYPEF_EVENT_SEND_ARENAREQUEST_)
	{
		//发送数据请求
		C2SArenaInfoPacket  requestArenaInfo(0);
		requestArenaInfo.Send();	
		Destroy();
		return ;
	}
	else if (iEventType == _TYPEF_EVENT_HIDE_ARENAWINDOW_ )
	{
		PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		Destroy();
	}
	else if (iEventType == _TYPEF_EVENT_UPDATE_ARENEWINDOW_ )
	{
		OnUpdateEventHandler(paramList);
	}
	else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		OnUpdateEventHandler(paramList);
	}
	else if(iEventType==_TYPEF_EVENT_UPDATE_ADDCHALLENGE_)
	{
	    //增加挑战次数
		cocos2d::CCLabelTTF * pLabelValue=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(_ARENA_ADD_LABEL_TAG_);
		if(pLabelValue!=NULL)
		{
			 ArenaInfoDataHandler::get_instance2()->PArenaInfoData->leftChallengeCount=AddChallengeDataHandler::get_instance2()->addChallenegeCount;
			 char  labelValue[32]={0}; 
			 sprintf(labelValue,SysLangDataManager::get_instance2()->GetSysLangById(_TODAY_CAN_CHALLENGE_NUM_).c_str(),
				 ArenaInfoDataHandler::get_instance2()->PArenaInfoData->leftChallengeCount);
			 pLabelValue->setString(labelValue);
		}
		return ;
	}
	else if(iEventType==_TYPEF_EVENT_HINT_ARENAWINDOW_AWARD_)
	{
		_checkAwardHint();
	} 
} 


void  ArenaWindow::InitLayout()
{  
	 m_pBaseNode=cocos2d::CCNode::create();
	 if(m_pRootNode!=NULL)
	 {
		 m_pRootNode->addChild(m_pBaseNode,2);
	 }
	 UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kARENAVIEW,m_pBaseNode);    

	 CCNode* cc=m_pBaseNode->getChildByTag(_ARENA_RECORD_CELL_TAG_);
	 m_szCELL=cc->getContentSize();

	 m_mStaticBtnMap.clear();
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Index_0_,0));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Index_1_,1));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Index_2_,2));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Index_3_,3));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Index_4_,4));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Fight_0_,0));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Fight_1_,1));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Fight_2_,2));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Fight_3_,3));
	 m_mStaticBtnMap.insert(std::map<int,int>::value_type(_Arena_ChangleRole_Fight_4_,4));
	  
}

void  ArenaWindow::LoadUIControl()
{ 
   m_bIsInitlayout=true;
   InitLayout();			 //UI初始化		
   InitStaticMapBtn();       //绑定静态按钮数据
   SetTableView();			 //设置TabView
   InitData();				 //初始化UI数据
   _checkNewFunc();
} 
 

void  ArenaWindow::InitStaticMapBtn()
{
	/*绑定UI按钮事件*/
	NFC_bindSelectorForBtn(_ARENA_HELP_BTN_TAG_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_ARENA_CLOSE_BTN_TAG_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_ARENA_RANK_BTN_TAG_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_ARENA_REWARD_BTN_TAG_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_ARENA_ADD_BTN_TAG_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_ARENA_PRESTIGE_SHOP_BTN_TAG_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
  
	/*
	绑定头像按钮事件
	*/
	NFC_bindSelectorForTouchSprite(_Arena_ChangleRole_Index_0_,m_pBaseNode,this);
	NFC_bindSelectorForTouchSprite(_Arena_ChangleRole_Index_1_,m_pBaseNode,this);
	NFC_bindSelectorForTouchSprite(_Arena_ChangleRole_Index_2_,m_pBaseNode,this);
	NFC_bindSelectorForTouchSprite(_Arena_ChangleRole_Index_3_,m_pBaseNode,this);
	NFC_bindSelectorForTouchSprite(_Arena_ChangleRole_Index_4_,m_pBaseNode,this);

	/*
	绑定角色挑战按钮事件
	*/
	NFC_bindSelectorForBtn(_Arena_ChangleRole_Fight_0_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_Arena_ChangleRole_Fight_1_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_Arena_ChangleRole_Fight_2_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_Arena_ChangleRole_Fight_3_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	NFC_bindSelectorForBtn(_Arena_ChangleRole_Fight_4_,m_pBaseNode,this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
	 
}




void ArenaWindow::rangeTouched(cocos2d::CCObject* pSender)
{
	  CTouchSprite * pTouchSprite=(CTouchSprite *)pSender;
	  if(pTouchSprite)
	  {   
		  std::map<int,int>::iterator  btn_iter=m_mStaticBtnMap.find(pTouchSprite->getIDX());
		  if(btn_iter!=m_mStaticBtnMap.end())
		  {  
			  if((*btn_iter).second<(int)ArenaInfoDataHandler::get_instance2()->PArenaInfoData->challgeList.size())
			  {
				   FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(ArenaInfoDataHandler::get_instance2()->PArenaInfoData->challgeList.at((*btn_iter).second)->sourceID,_TYPED_WINDOW_ARENAWINDOW_);
			  }
		  } 
		  CCLOG("Touch %d",pTouchSprite->getIDX());
	  } 
}
 

void    ArenaWindow::InitData()
{   
	UpdateUIWithData();
  
}


float  ArenaWindow::GetCurSysMinuteTime()
{
	unsigned long  long timeStamp=time(NULL);
	struct tm * pTm=localtime((time_t *)&timeStamp);
	return GetMinuteFromSecond(pTm->tm_hour*60*60+pTm->tm_min*60+pTm->tm_sec);
}



float ArenaWindow::GetMinuteFromSecond(int second)
{
     int secondLast=second%60;
	 float minuteTime=second/60+secondLast*1.0f/60;
     return  minuteTime;
}

int   ArenaWindow::GetDelayDayCountFromArena(float curMinute,float distanceMinute)
{
	if(distanceMinute<=curMinute)
	{
		return 0;
	}
	else
	{
		return   (int)(distanceMinute-curMinute)/(24*60)+1;
	} 
}

 

void    ArenaWindow::UpdateUIWithData()
{    
	_checkAwardHint();

	tmpPlayInstanceID=RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_;

	//导入竞技内存数据列表
	if(ArenaInfoDataHandler::get_instance2()->PArenaInfoData!=NULL)
	{
		//清空之前滴数据
		m_historyArenaVec.clear();
		m_historyArenaVec=ArenaInfoDataHandler::get_instance2()->PArenaInfoData->historyArenaList;
	} 
	//获取各种内存数据更新UI 
	if(RoleInfoDataHandler::get_instance2()!=NULL&&RoleInfoDataHandler::get_instance2()!=NULL)
	{  
		//显示基础信息 
		//我的声望
		NFC_setLabelStringInt(_ARENA_PRESITGE_VALUE_TAG_,m_pBaseNode,RoleInfoDataHandler::get_instance2()->m_pRIData->prestige_);
		 
		//我的排名
		NFC_setLabelStringInt(_ARENA_PLAYER_RANK_NUM_TAG_,m_pBaseNode,RoleInfoDataHandler::get_instance2()->m_pRIData->pvpRank_); 

		//我的战绩
		char  labelValue[32]={0};
		sprintf(labelValue,SysLangDataManager::get_instance2()->GetSysLangById(7004).c_str(),
			ArenaInfoDataHandler::get_instance2()->PArenaInfoData->winCount,
			ArenaInfoDataHandler::get_instance2()->PArenaInfoData->loseCount);
		NFC_setLabelString(_AERNA_PLAYER_RECORD_NUMBER_TAG_,m_pBaseNode,labelValue);
		 
		//更新剩余挑战次数
		UpdateLastArenaTime();
	
		/*
		刷新挑战队列UI
		*/
		UpdateChallengeListUI();

		/*
		刷新历史记录UI
		*/
		_refreshTableView(m_pTable);
	} 
}



void	ArenaWindow::UpdateChallengeListUI()
{ 
	size_t chanelCount=ArenaInfoDataHandler::get_instance2()->PArenaInfoData->challgeList.size();
	if(chanelCount>_MAX_CHALLENGE_NUM_)
	{
		chanelCount=_MAX_CHALLENGE_NUM_;
	}
	for(size_t startIndex=_Arena_Start_Challenge_Tag_;startIndex<=_Arena_End_Challenege_Tag_;startIndex++)
	{
		cocos2d::CCNode * pNode=m_pBaseNode->getChildByTag(startIndex);
		if(pNode!=NULL)
		{
			pNode->setVisible(false);
		}
	} 
	int startIndexTag=_Arena_Start_Challenge_Tag_;
	int i=0;
	PChallgeNode pChallgeNode=NULL;
	char  commonStr[128]={0};
    for(size_t changelIndex=0;changelIndex<chanelCount;changelIndex++)
	{
		i=0;
		pChallgeNode=ArenaInfoDataHandler::get_instance2()->PArenaInfoData->challgeList.at(changelIndex);
		if(pChallgeNode!=NULL)
		{
			cocos2d::CCLabelTTF * pLabel=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pLabel)
			{
				pLabel->setString(pChallgeNode->name.c_str());
				pLabel->setVisible(true);
			}
			cocos2d::CCSprite  * pSprite=(cocos2d::CCSprite *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pSprite)
			{
				pSprite->setVisible(true);
			}
			pLabel=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pLabel)
			{
				sprintf(commonStr,SysLangDataManager::get_instance2()->GetSysLangById(_LEVEL_CONETNTE_TET_ID_).c_str(),pChallgeNode->level);
				pLabel->setString(commonStr);
				pLabel->setVisible(true);
			}
			pSprite=(cocos2d::CCSprite *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pSprite)
			{
				pSprite->setVisible(true);
			}
			CTouchSprite * pTouchSprite=(CTouchSprite *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pTouchSprite)
			{ 
				pTouchSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(pChallgeNode->iconID).c_str());
				pTouchSprite->setVisible(true);
			}
			pSprite=(cocos2d::CCSprite *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pSprite)
			{
				pSprite->setVisible(true);
			}
			pLabel=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pLabel)
			{
				sprintf(commonStr,SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_RANK_VALUE_).c_str(),pChallgeNode->rank);
				pLabel->setString(commonStr);
				pLabel->setVisible(true);
			} 
			pLabel=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pLabel)
			{
				sprintf(commonStr,SysLangDataManager::get_instance2()->GetSysLangById(_ARENE_FIGHT_ABILITY_).c_str(),pChallgeNode->btlCapacity);
				pLabel->setString(commonStr);
				pLabel->setVisible(true);
			} 
			CMenuItemSprite * pMenuItem=(CMenuItemSprite *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pMenuItem)
			{
				pMenuItem->setVisible(true);
			}
			pLabel=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(startIndexTag+(i++));
			if(pLabel)
			{
				pLabel->setVisible(true);
			}
		} 
		startIndexTag+=_Arena_Challenege_Unit_Count_;
	}
 
}
   

void	ArenaWindow::DestroyData() 
{
	m_mStaticBtnMap.clear();
	m_historyArenaVec.clear();	 
}


void  ArenaWindow::SetTableView()
{
	m_pTable =(cocos2d::extension::CCTableView *)m_pBaseNode->getChildByTag(_ARENA_RECORD_CONTAIN_TAG_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);

}

 
void    ArenaWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::KARENAVIEWCELL,pTableCell);
}
 

/*
 复仇按钮点击事件
*/
void   ArenaWindow::CallBackFuChouBtn(cocos2d::CCObject * pSender)
{
	CMenuItemSprite  * pFuChouBtn=(CMenuItemSprite *)pSender;
	if(pFuChouBtn!=NULL&&pFuChouBtn->getIDX()<m_historyArenaVec.size())
	{
		 PHistoryArenaNode pHistoryArenaNode=m_historyArenaVec.at(pFuChouBtn->getIDX());
		 if(pHistoryArenaNode!=NULL)
		 {
			 int  challengeRoleID=0;
			 if(pHistoryArenaNode->targetID==tmpPlayInstanceID)
			 {
				 challengeRoleID=pHistoryArenaNode->sourceID;
			 }
			 else
			 {
				 challengeRoleID=pHistoryArenaNode->targetID;
			 }
			 C2SChallengePacket challengeRequestPacket(challengeRoleID);
			 challengeRequestPacket.Send();
		 } 
	}
}

/*
 查看历史竞技记录事件
*/
void   ArenaWindow::CallBackShowArenaBtn(cocos2d::CCObject * pSender)
{	
	
	CMenuItemSprite  * pShowArenaBtn=(CMenuItemSprite *)pSender;
	if(pShowArenaBtn!=NULL)
	{ 
		if(pShowArenaBtn->getIDX()<m_historyArenaVec.size())
		{
			PHistoryArenaNode pHistoryArenaNode=m_historyArenaVec.at(pShowArenaBtn->getIDX());
			if(pHistoryArenaNode!=NULL)
			{ 
				C2SBattleRecordPacket historyBattleRequest(pHistoryArenaNode->battleID);
				historyBattleRequest.Send();
			}
		} 
	}

}


void    ArenaWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{   
	if(cellIndex<m_historyArenaVec.size())
	{
		PHistoryArenaNode  pHistoryArenaNode=m_historyArenaVec.at(cellIndex);
		if(pHistoryArenaNode==NULL)
			return ;
 	  
        bool  isPlayAsTarget=false;
		bool  isShowFuChouBtn=false;
		bool  isPlayerWinBattle=false;
		char  isPlayRankChange=_Arena_Play_Rank_UnChange_;
		int   curPlayRank=0;
		if(pHistoryArenaNode->targetID==tmpPlayInstanceID)
		{
			isPlayAsTarget=true;
		} 
		std::string  arenaDiscription="";
		std::string  TargetName=NFC_getRichTextCSSByFontStyleID(6,SysLangDataManager::get_instance2()->GetSysLangById(_ENMEY_NAME_CONTENT_));	
		std::string  commonTime="";
 
		char  commonName[128]={0};
		char  commonRank[128]={0};  
		
		int  delayDayCount=GetDelayDayCountFromArena(GetCurSysMinuteTime(),GetMinuteFromSecond(pHistoryArenaNode->distime));
		if(delayDayCount==0)
		{ 
			commonTime=SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_BATTLE_1_);
			 
		}
		else if(delayDayCount==1)
		{
			commonTime=SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_BATTLE_2_);
		}
		else
		{
			sprintf(commonName,SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_BATTLE_3_).c_str(),delayDayCount);
			commonTime=commonName;
		}
 
		if(isPlayAsTarget)
		{ 
			if(pHistoryArenaNode->isWin==_Arena_Win_Type_)
			{
				isPlayerWinBattle=false;
				if(pHistoryArenaNode->targetRank>=pHistoryArenaNode->sourceRank)
				{ 
					//排名不变
					isShowFuChouBtn=true;
					isPlayRankChange=_Arena_Play_Rank_UnChange_;
					//XXX 挑战了你, 你战败了， 排名不变
					sprintf(commonName,TargetName.c_str(),pHistoryArenaNode->sourceName.c_str());
					arenaDiscription=commonTime+" ";
					arenaDiscription+=commonName+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_BATTLE_PLAY_)
						+","+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_BATTLE_PLAY_LOST_)+" "+ SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_NO_CHANGE_);
					 
					//////////////////////////////////////////////////////////////////////////
				}
				else
				{
					//名次降低
					isPlayRankChange=_Arena_Play_Rank_Low_;
					curPlayRank=pHistoryArenaNode->sourceRank;
					isShowFuChouBtn=true;
					//XXX 挑战了你，你战败了，排名降至 curPlayRank
					sprintf(commonName,TargetName.c_str(),pHistoryArenaNode->sourceName.c_str());
					sprintf(commonRank,SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_RANK_UP_).c_str(),curPlayRank);
					arenaDiscription=commonTime+" ";
					arenaDiscription+=commonName+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_BATTLE_PLAY_)+","+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_BATTLE_PLAY_LOST_)+" "+ commonRank;

				}  
			}
			else
			{
					isPlayerWinBattle=true;
					isPlayRankChange=_Arena_Play_Rank_UnChange_;
					sprintf(commonName,TargetName.c_str(),pHistoryArenaNode->sourceName.c_str());
				    //XXX 挑战了你，你战胜了，排名不变
					arenaDiscription=commonTime+" ";
					arenaDiscription+=commonName+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_BATTLE_PLAY_)+","+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_WIN_)+" "+ SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_NO_CHANGE_);
			}
		} 
		else
		{ 
			if(pHistoryArenaNode->isWin==_Arena_Win_Type_)
			{
				isPlayerWinBattle=true;
				if(pHistoryArenaNode->targetRank>=pHistoryArenaNode->sourceRank)
				{
					//排名不变
					isPlayRankChange=_Arena_Play_Rank_UnChange_;
					//你挑战了XXX ，你战胜了，排名不变
					sprintf(commonName,TargetName.c_str(),pHistoryArenaNode->targetName.c_str());
					arenaDiscription=commonTime+" ";
					arenaDiscription+=SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PALY_BATTLE_)+commonName+","+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_WIN_)+" "+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_NO_CHANGE_);

				}
				else
				{
					//名次上升
					isPlayRankChange=_Arena_Play_Rank_Hight_;
					curPlayRank=pHistoryArenaNode->targetRank;
					//你挑战了XXX，你战胜了，排名上升至 curPlayRank
					sprintf(commonName,TargetName.c_str(),pHistoryArenaNode->targetName.c_str());
					sprintf(commonRank,SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_RANK_DOWN_).c_str(),curPlayRank);
					arenaDiscription=commonTime+" ";
					arenaDiscription+=SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PALY_BATTLE_)+commonName+","+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_WIN_)+" "+commonRank;
				}
			}
			else
			{
				isPlayerWinBattle=false;
				isPlayRankChange=_Arena_Play_Rank_UnChange_;
				//你挑战了XXX，你战败了 排名不变
				sprintf(commonName,TargetName.c_str(),pHistoryArenaNode->targetName.c_str());
				arenaDiscription=commonTime+" ";
				arenaDiscription+=SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PALY_BATTLE_)+commonName+","+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_BATTLE_PLAY_LOST_)+" "+SysLangDataManager::get_instance2()->GetSysLangById(_ARENA_HISTORY_PLAY_NO_CHANGE_);
			}
		}
		
		SetCellImage(pTableCell,isPlayerWinBattle);
		SetCellDescription(pTableCell,arenaDiscription);
		SetCellDequeueBtn(pTableCell,cellIndex);
	}

} 

void    ArenaWindow::SetCellImage(cocos2d::extension::CCTableViewCell * pTableCell,bool isWinResult)
{
   if(pTableCell!=NULL)
   {
	   cocos2d::CCSprite * pImageSprite=(cocos2d::CCSprite *)pTableCell->getChildByTag(_ArenaCell_WINOrFAILL_BG_TAG_);
	   if(pImageSprite!=NULL)
	   {
		   if(isWinResult)
		   { 
			   pImageSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(_WIN_IMAGE_RESOURCE_ID_));
		   }
		   else
		   {
			   pImageSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(_LOST_IMAGE_RESOURCE_ID_));
		   }
	   }
   } 
}

void    ArenaWindow::SetCellDescription(cocos2d::extension::CCTableViewCell * pTableCell,std::string discription)
{
	if(pTableCell!=NULL)
	{
		cocos2d::CCLabelTTF  * pArenaLabel=(cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_ArenaCell_Description_Label_TAG_);
		if(pArenaLabel!=NULL)
		{
			pArenaLabel->setString(discription.c_str());
		}
	}
}
  
void    ArenaWindow::SetCellDequeueBtn(cocos2d::extension::CCTableViewCell * pTableCell,int cellIndex)
{
   //显示查看按钮
	if(pTableCell!=NULL)
	{
		CImmovableMenu  * pShowArenaBtn=(CImmovableMenu *)pTableCell->getChildByTag(_ArenaCell_Dequeue_Btn_TAG_);
		if(pShowArenaBtn!=NULL)
		{
			CMenuItemSprite  * pShowArenaRecord=(CMenuItemSprite *)pShowArenaBtn->getChildByTag(0);
			if(pShowArenaRecord!=NULL)
			{
				pShowArenaRecord->setTarget(this,menu_selector(ArenaWindow::CallBackShowArenaBtn));
				pShowArenaRecord->setIDX(cellIndex);
			} 
		} 
	}
}

 
void ArenaWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	if(paramList.size() > 0)
	{
		std::list<std::string>::iterator it = paramList.begin();
		std::string str = *it;
		m_iBackWindow = atoi(str.c_str());
		it++;
		if(it != paramList.end())
		{
			str = *it;
			m_iBackSubview = str;
		}
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_,_to_event_param_(_TYPED_WINDOW_ARENAWINDOW_));
	PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
}

void ArenaWindow::OnUpdateEventHandler(std::list<std::string>& paramList)
{ 
	if(!paramList.empty())
	{
		int  receciptCode = atoi(paramList.begin()->c_str());
		switch(receciptCode)
		{
		case 0:
			//更新剩余次数
			UpdateLastArenaTime();
			break;
		default:
			UpdateUIWithData();
			break;
		} 
	}
	else
	{
		UpdateUIWithData();
	}
 }



void  ArenaWindow::UpdateLastArenaTime()
{
	//可挑战次数
	cocos2d::CCLabelTTF *  pCanChallengeCount=(cocos2d::CCLabelTTF *)m_pBaseNode->getChildByTag(_ARENA_ADD_LABEL_TAG_);
	char labelValue[128]={0};
	if(pCanChallengeCount!=NULL)
	{
		sprintf(labelValue,SysLangDataManager::get_instance2()->GetSysLangById(_TODAY_CAN_CHALLENGE_NUM_).c_str(),ArenaInfoDataHandler::get_instance2()->PArenaInfoData->leftChallengeCount);
		pCanChallengeCount->setString(labelValue);

	} 
}
 

void  ArenaWindow::SetGifBoxEnableState(bool isEnableTouch)
{
	cocos2d::CCMenu * pMemu=NULL;

	pMemu=(cocos2d::CCMenu *)m_pBaseNode->getChildByTag(_ARENA_REWARD_BTN_TAG_);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			if(isEnableTouch)
			{
				pMenuItem->setEnabled(true);
				pMenuItem->setIDX(_ARENA_REWARD_BTN_TAG_);
				pMenuItem->setTarget(this,menu_selector(ArenaWindow::CallBackBtnClickHandler));
			}
			else
			{
				pMenuItem->setEnabled(false);
			}
		} 
	}
}




/*公共按钮回调接口*/
void  ArenaWindow::CallBackBtnClickHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
		case  _ARENA_CLOSE_BTN_TAG_:		 
			{
				if(m_iBackWindow <= 0)
				{
					if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_HOME_PROCEDURE_)
					{
						char athleticsProcedure[8]={0};
						sprintf(athleticsProcedure,"%d",IProcedure::_TYPED_HOME_PROCEDURE_);
						EventSystem::get_instance2()->PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
						NFC_showCommunicationWating(false);
						EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,athleticsProcedure);
						return ;
					} 
					else
					{
						PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
						PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
					} 
				}
				else
				{
					PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
					EVENTSYSTEM->PushEvent(m_iBackWindow, m_iBackSubview);
				}
				break; 
			}
		case  _ARENA_RANK_BTN_TAG_:
			{
				C2SArenaRankPacket arenaRankPacket(0);
				arenaRankPacket.Send();
				break;
			}
		case  _ARENA_REWARD_BTN_TAG_:
			{ 
				CCLOG("_ArenaUI_Box_Btn_ Click Handlder!");
				C2SArenaRewardPacket arenaRewardPacket;
				arenaRewardPacket.Send();
				break;
			}
		case  _ARENA_ADD_BTN_TAG_:
			{
				C2SAddChallenegeCountPacket addChallengePacket;
				addChallengePacket.Send();
				break;
			}
		case  _ARENA_HELP_BTN_TAG_:
			{
				char type[128] = "";
				sprintf(type,"%d",UIViewDataManager::kARENA_HELP_);
				PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,type);
				CCLOG("_ArenaUI_ Help Btn_ Handler!");
				break;
			}
		case  _Arena_ChangleRole_Fight_0_:
		case  _Arena_ChangleRole_Fight_1_:
		case  _Arena_ChangleRole_Fight_2_:
		case  _Arena_ChangleRole_Fight_3_:
		case  _Arena_ChangleRole_Fight_4_:
			{
				OnSendFightRequestHandler(pMenuItem->getIDX());
				break;
			} 
		case  _ARENA_PRESTIGE_SHOP_BTN_TAG_:
			{   
				PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
				EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_SHOPWINDOW_,_to_event_param_(1),_to_event_param_(_TYPEF_EVENT_SHOW_ARENAWINDOW_));
				break;
			}
		default: 
			break;
		}
	}
}

	/*
		检查奖励提示
	*/
void ArenaWindow::_checkAwardHint()
{
	NFC_setNodeVisable(_ARENA_REWARD_HINT_TAG_,m_pBaseNode,ROLEINFODATAHANDLER->m_pRIData->arena_awardCanReceive_);
}

void   ArenaWindow::OnSendFightRequestHandler(int index)
{
	std::map<int,int>::iterator  btn_iter=m_mStaticBtnMap.find(index);
	if(btn_iter!=m_mStaticBtnMap.end())
	{  
		if((*btn_iter).second<(int)ArenaInfoDataHandler::get_instance2()->PArenaInfoData->challgeList.size())
		{
			C2SChallengePacket challengePacket(ArenaInfoDataHandler::get_instance2()->PArenaInfoData->challgeList.at((*btn_iter).second)->sourceID);
			challengePacket.Send();
		}
	} 
}
 

cocos2d::CCSize ArenaWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return m_szCELL;
}

cocos2d::extension::CCTableViewCell* ArenaWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	cocos2d::extension::CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new cocos2d::extension::CCTableViewCell();
		cell->autorelease();
		CreateTableCell(cell);
	}
	SetTableCell(cell,idx);
 	return cell;
}


unsigned int ArenaWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return  m_historyArenaVec.size();
}