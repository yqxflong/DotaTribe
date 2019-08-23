#include "../include/ArenaRewardWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h" 
#include "../include/EngineSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFAnimationController.h"
#include "../include/NFControlsManager.h"
#include "../include/ArenaInfoDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/NetObjectTipsDataHandler.h"

#include "../include/CTimeLabel.h"
#include "../include/C2SArenaGifPacket.h"
#include "../include/C2SArenaInfoPacket.h"
 

#define  _GOT_REWARD_TXTID_				2014			//已领取
#define  _GET_REWARD_TXTID_				174				//领取
#define  _DURATION_TXTID_				7010			//进行中
#define  _PLAYER_RECORD_TXTID_			7004			//战绩
#define  _CHALLENEGE_REWARD_TXTID_		7008			//奖励内容格式
#define  _CHALLENEGE_TASK_TXTID_		134			    //任务格式
#define  _TASK_OFFSET_					5				//任务偏移
#define  _NO_IN_RANK_					614				//未上榜

ArenaRewardWindow::ArenaRewardWindow()
{
	m_WindowType  =  _TYPED_WINDOW_ARENAREWARDWINDOW_;
	m_pTable = NULL;
	m_szCELL = CCSizeZero; 
	m_bScrollEnd = false;
	m_pViewRoot = NULL;
	m_pArenaRewardData = NULL;
	m_nMaxRewardSize = 0;
	m_nLastRequestCellIndex = 0;
}

ArenaRewardWindow::~ArenaRewardWindow()
{ 
}

bool ArenaRewardWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_ARENAREWARDWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_ARENAREWARDWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ARENAREWARDWINDOW_, true); 
	RegisterEvent(_TYPEF_EVENT_UPDATE_REWARDDISTANCE_, true);  
	 
	return IWindow::Init();
}



bool ArenaRewardWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		LoadUIControl(); 
		return true;
	} 
	while (false);

	return false;
}

void ArenaRewardWindow::Tick()
{ 
	IWindow::Tick();
}


void ArenaRewardWindow::Destroy()
{  
	m_nLastRequestCellIndex = 0;
	m_bScrollEnd = false;
	m_pViewRoot->removeFromParentAndCleanup(true);
	DestroyData();
	IWindow::Destroy();
}

void ArenaRewardWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_ARENAREWARDWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_ARENAREWARDWINDOW_)
	{ 
		Destroy();
	}
	else if(iEventType==_TYPED_EVENT_UPDATE_ARENAREWARDWINDOW_)
	{ 
		int receiptCode=atoi(paramList.begin()->c_str());
		dispatchReceiptCode(receiptCode);
	}
	else if(iEventType==_TYPEF_EVENT_UPDATE_REWARDDISTANCE_)
	{
		 int  rewardDistance= ArenaRewardDataHandler::get_instance2()->getArenaRewardDatas()->getArenaGetRewardDistance();
		 NFC_setTimeLabel(_ARENAREWARD_RIGHT_REWARD_TIME_TAG_,m_pViewRoot,this,rewardDistance);
		 if(rewardDistance!=0)
		 {
			 NFC_setMenuEnable(_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,m_pViewRoot,false);
		 }
		 else
		 { 
			 NFC_setMenuEnable(_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,m_pViewRoot,true);
		 } 
	}
}

/*
绑定内存数据
*/
void    ArenaRewardWindow::InitData()
{
	m_pArenaRewardData = ArenaRewardDataHandler::get_instance2()->getArenaRewardDatas();
	if(m_pArenaRewardData)
	{
		m_nMaxRewardSize = m_pArenaRewardData->getArenaChallengeRewardVector().size();  
	}
	updateUIWithData();
}

/*
销毁内存数据
*/
void    ArenaRewardWindow::DestroyData()
{  
	//to do
}


void  ArenaRewardWindow::dispatchReceiptCode(int receiptCode)
{
	NFC_showCommunicationWating(false);
	if(receiptCode==0)
	{      
		m_pArenaRewardData->getArenaChallengeRewardVector().at(m_nLastRequestCellIndex)->rewardHadGot = false; 
		cocos2d::extension::CCTableViewCell * pTableCell = (cocos2d::extension::CCTableViewCell *) m_pTable->cellAtIndex(m_nLastRequestCellIndex);
		if(pTableCell)
		{ 
			NFC_setLabelString(_CHALLENEGE_REWARD_LABEL_TAG_,pTableCell,SysLangDataManager::get_instance2()->GetSysLangById(_GET_REWARD_TXTID_).c_str(),true);
			NFC_setMenuEnable(_CHALLENEGE_REWARD_BTN_TAG_,pTableCell,true); 
		} 
	}
}


void  ArenaRewardWindow::updateUIWithData()
{   
	if(m_pArenaRewardData->getLastArenaRank()!=-1&&m_pArenaRewardData->getLastArenaRank()!=0)
	NFC_setLabelStringInt(_ARENAREWARD_RIGHT_RANK_VALUE_TAG_,m_pViewRoot,m_pArenaRewardData->getLastArenaRank());
	else
	NFC_setLabelString(_ARENAREWARD_RIGHT_RANK_VALUE_TAG_,m_pViewRoot,SysLangDataManager::get_instance2()->GetSysLangById(_NO_IN_RANK_));
	char  lableString[32]={0};
	sprintf(lableString,SysLangDataManager::get_instance2()->GetSysLangById(_PLAYER_RECORD_TXTID_).c_str(),
		ArenaInfoDataHandler::get_instance2()->PArenaInfoData->winCount,
		ArenaInfoDataHandler::get_instance2()->PArenaInfoData->loseCount);
	NFC_setLabelString(_ARENAREWARD_RIGHT_COMBAT_RECORD_CONTENT_TAG_,m_pViewRoot,lableString);
	if(ArenaInfoDataHandler::get_instance2()->PArenaInfoData->loseCount==0)
	NFC_setLabelString(_ARENAREWARD_RIGHT_ODDS_CONTENT_TAG_,m_pViewRoot,"0%");
	else
	{
		int winRate=(int)(100*ArenaInfoDataHandler::get_instance2()->PArenaInfoData->winCount*1.0f/ArenaInfoDataHandler::get_instance2()->PArenaInfoData->loseCount);
		sprintf(lableString,"%d%%",winRate); 
		NFC_setLabelString(_ARENAREWARD_RIGHT_ODDS_CONTENT_TAG_,m_pViewRoot,lableString);
	} 
	//to do 
	updateRankRewardData();

	//倒计时标签 
	CTimeLabel * pCountDownLabel = (CTimeLabel *)m_pViewRoot->getChildByTag(_ARENAREWARD_RIGHT_REWARD_TIME_TAG_);
	if(pCountDownLabel)
	{
		pCountDownLabel->setTimerEventDelegate(this);
	}

	//领取按钮 
	if(ArenaRewardDataHandler::get_instance2()->getArenaRewardDatas()->getArenaGetRewardDistance()!=0)
	{
		 //不能领取
		 NFC_setMenuEnable(_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,m_pViewRoot,false);
		 pCountDownLabel->StartTimer(ArenaRewardDataHandler::get_instance2()->getArenaRewardDatas()->getArenaGetRewardDistance());
	}
	else
	{
		NFC_setMenuEnable(_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,m_pViewRoot,true);
		//领取
		pCountDownLabel->StopTimer(true);
	}
}


void  ArenaRewardWindow::TimerEventHandler(int eventType,std::string attachParam)
{
	if(eventType==CTimerEventProtocol::_COUNTDONW_END_TYPE_)
	{
		//to do
		CCLOG("ArenaRewardWindow  Count Donw Handler!" );
		NFC_setMenuEnable(_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,m_pViewRoot,true);
	}
}



void  ArenaRewardWindow::updateRankRewardData()
{ 
	NFC_setNodeVisable(_ARENAREWARD_RIGHT_OBJ_1_TAG_,m_pViewRoot,false);
	NFC_setNodeVisable(_ARENAREWARD_RIGHT_NUM_1_TAG_,m_pViewRoot,false); 
	NFC_setNodeVisable(_ARENAREWARD_RIGHT_OBJ_2_TAG_,m_pViewRoot,false);
	NFC_setNodeVisable(_ARENAREWARD_RIGHT_NUM_2_TAG_,m_pViewRoot,false); 
	//////////////////////////////////////////////////////////////////////////
	size_t rankRewardSize=m_pArenaRewardData->getArenaRankRewardVector().size();
	char  labelStr[32]={0};
	if(rankRewardSize>0)
	{
		PRewardItemNode pRewardItem = m_pArenaRewardData->getArenaRankRewardVector().at(0);
		if(pRewardItem)
		{ 
			showRewardMenuItem(-1,_ARENAREWARD_RIGHT_OBJ_1_TAG_,m_pViewRoot,pRewardItem); 
			NFC_setNodeVisable(_ARENAREWARD_RIGHT_OBJ_1_TAG_,m_pViewRoot,true);
			sprintf(labelStr,"%d",pRewardItem->rewardItemCount);
			NFC_setLabelString(_ARENAREWARD_RIGHT_NUM_1_TAG_,m_pViewRoot,labelStr,true); 
		}
		if(rankRewardSize>1)
		{
			PRewardItemNode pRewardItem = m_pArenaRewardData->getArenaRankRewardVector().at(1);
			if(pRewardItem)
			{  
				showRewardMenuItem(-1,_ARENAREWARD_RIGHT_OBJ_2_TAG_,m_pViewRoot,pRewardItem);  
				NFC_setNodeVisable(_ARENAREWARD_RIGHT_OBJ_2_TAG_,m_pViewRoot,true);
				sprintf(labelStr,"%d",pRewardItem->rewardItemCount);
				NFC_setLabelString(_ARENAREWARD_RIGHT_NUM_2_TAG_,m_pViewRoot,labelStr,true); 
			}
		}
	}  
}



 
void   ArenaRewardWindow::CommonMenuSelector(cocos2d::CCObject * pSender)
{
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem)
	{
		switch(pMenuItem->getIDX())
		{
		case  _ARENAREWARD_CLOSE_BTN_TAG_:
			{ 
				CCLOG("ArenaRewardWindow : Close  Handler!");
				PushEvent(_TYPED_EVENT_HIDE_ARENAREWARDWINDOW_);
				break; 
			}
		case _ARENAREWARD_RIGHT_REWARD_TBN_TAG_:
			{
				//to do 
				C2SArenaGifPacket arenaGigPacket;
				arenaGigPacket.Send();
				break;
			}
		case _ARENAREWARD_RIGHT_OBJ_1_TAG_:
			{ 
				if(m_pArenaRewardData->getArenaRankRewardVector().size()>0)
				{
					if(m_pArenaRewardData->getArenaRankRewardVector().at(0)->rewardItemType==0)
					{
						NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pArenaRewardData->getArenaRankRewardVector().at(0)->rewardTemplateID, _TYPED_WINDOW_ARENAREWARDWINDOW_);
					}
				}
				break;
			}
		case _ARENAREWARD_RIGHT_OBJ_2_TAG_:
			{
				if(m_pArenaRewardData->getArenaRankRewardVector().size()>1)
				{
					if(m_pArenaRewardData->getArenaRankRewardVector().at(1)->rewardItemType==0)
					{
						NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pArenaRewardData->getArenaRankRewardVector().at(1)->rewardTemplateID, _TYPED_WINDOW_ARENAREWARDWINDOW_);
					}
				}
				break;
			}
		default: 
			break;
		}
	}
}

void	ArenaRewardWindow::CommonCellMenuSelector(cocos2d::CCObject * pSender)
{
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem&&pMenuItem->getIDX()<(unsigned int)m_nMaxRewardSize)
	{
		CCLOG("Arena Reward Cell Index Clik: %d",pMenuItem->getIDX());  
		short  rewardChallenegeCount = m_pArenaRewardData->getArenaChallengeRewardVector().at(pMenuItem->getIDX())->rewardChanllengeCount;
		if(m_pArenaRewardData->getArenaChallengeCount() >= rewardChallenegeCount) 
		{
			m_nLastRequestCellIndex = pMenuItem->getIDX();
			C2SChallengeCountRewardPacket  challengeRewardPacket(m_pArenaRewardData->getArenaChallengeRewardVector().at(pMenuItem->getIDX())->rewardChanllengeCount);
			challengeRewardPacket.Send();  

			m_pArenaRewardData->getArenaChallengeRewardVector().at(pMenuItem->getIDX())->rewardHadGot=true; 
			cocos2d::extension::CCTableViewCell * pTableCell = (cocos2d::extension::CCTableViewCell *) m_pTable->cellAtIndex(pMenuItem->getIDX());
			if(pTableCell)
			{ 
				NFC_setMenuEnable(_CHALLENEGE_REWARD_BTN_TAG_,pTableCell,false); 
				NFC_setLabelString(_CHALLENEGE_REWARD_LABEL_TAG_,pTableCell,SysLangDataManager::get_instance2()->GetSysLangById(_GOT_REWARD_TXTID_).c_str(),true);
			}
		} 
	}
}

 
void ArenaRewardWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	if(m_pRootNode->isVisible())
	return ;   
	Show(true);
	NFC_Action_fallDown(m_pViewRoot);
}  


void    ArenaRewardWindow::LoadUIControl()
{    
	if(m_pRootNode)
	{
		m_pViewRoot=cocos2d::CCNode::create();
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kARENAREWARDWINDOW,m_pViewRoot);    
		m_pRootNode->addChild(m_pViewRoot,1);
		CPriorityLayerColor * pPriorityColorLayer=(CPriorityLayerColor *)m_pViewRoot->getChildByTag(_ARENAREWARD_GRAP_COLOR_TAG_);
		pPriorityColorLayer->removeFromParent();
		m_pRootNode->addChild(pPriorityColorLayer,-1);
	}
	InitBindMenuSelector();
	InitData();
	SetTableView();
} 


void	ArenaRewardWindow::InitBindMenuSelector()
{
	NFC_bindSelectorForBtn(_ARENAREWARD_CLOSE_BTN_TAG_,m_pViewRoot, this,menu_selector(ArenaRewardWindow::CommonMenuSelector));
	NFC_bindSelectorForBtn(_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,m_pViewRoot,this,menu_selector(ArenaRewardWindow::CommonMenuSelector)); 
	DTAwardBoard* dd=(DTAwardBoard*)m_pViewRoot->getChildByTag(_ARENAREWARD_RIGHT_OBJ_1_TAG_);
	dd->setIDX(_ARENAREWARD_RIGHT_OBJ_1_TAG_);
	dd->setTarget(this,menu_selector(ArenaRewardWindow::CommonMenuSelector));
	dd=(DTAwardBoard*)m_pViewRoot->getChildByTag(_ARENAREWARD_RIGHT_OBJ_2_TAG_);
	dd->setIDX(_ARENAREWARD_RIGHT_OBJ_2_TAG_);
	dd->setTarget(this,menu_selector(ArenaRewardWindow::CommonMenuSelector));
}
 
 
void    ArenaRewardWindow::SetTableView()
{
	CCNode* cc=m_pViewRoot->getChildByTag(_ARENAREWARD_LEFT_CELL_TAG_);
	m_szCELL=cc->getContentSize();

	m_pTable =(cocos2d::extension::CCTableView *)m_pViewRoot->getChildByTag(_ARENAREWARD_LEFT_TABLE_TAG_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	_refreshTableView(m_pTable);

}
 
 
void    ArenaRewardWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kARENAREWARDCELL,pTableCell);
}

void    ArenaRewardWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{    
	if(cellIndex<(unsigned int)m_nMaxRewardSize)
	{
		PChallengeRewardData pChallengeRewardData = m_pArenaRewardData->getArenaChallengeRewardVector().at(cellIndex);
		char labelStr[64]={0};
		if(pChallengeRewardData)
		{ 
			showRewardSpriteItem(-1,_CHALLENEGE_REWARD_OBJ_TAG_,pTableCell,pChallengeRewardData->rewardItemData);  
			switch(pChallengeRewardData->rewardItemData->rewardItemType)
			{ 
			case kDT_AWARD_MONEY:
				pChallengeRewardData->rewardItemData->rewardRewardName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_MONEY_TID);
				break;
			case kDT_AWARD_EXP:
				pChallengeRewardData->rewardItemData->rewardRewardName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_EXP_TID);
				break;
			case kDT_AWARD_DIAMOND:
				pChallengeRewardData->rewardItemData->rewardRewardName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_DIAMOND_TID);
				break;
			case kDT_AWARD_PRESTIGE:
				pChallengeRewardData->rewardItemData->rewardRewardName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_PRESTIGE_TID);
				break;
			case kDT_AWARD_POWER:
				pChallengeRewardData->rewardItemData->rewardRewardName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_POWER_TID);
				break;
			default:
				break;
			}
			sprintf(labelStr,SysLangDataManager::get_instance2()->GetSysLangById(_CHALLENEGE_REWARD_TXTID_).c_str(),
				pChallengeRewardData->rewardItemData->rewardRewardName.c_str(),pChallengeRewardData->rewardItemData->rewardItemCount);
			NFC_setLabelString(_CHALLENEGE_REWARD_CONTENT_TAG_,pTableCell,labelStr,true); 
			sprintf(labelStr,SysLangDataManager::get_instance2()->GetSysLangById(_CHALLENEGE_TASK_TXTID_).c_str(),
				m_pArenaRewardData->getArenaChallengeCount(),pChallengeRewardData->rewardChanllengeCount); 
			NFC_setLabelString(_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_,pTableCell,labelStr,true);

			cocos2d::CCLabelTTF * pBeforTaskConent = (cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_);
			cocos2d::CCLabelTTF * pFollowTaskConent = (cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_CHALLENEGE_TASK_CONTENT_FOLLOW_TAG_);
			pFollowTaskConent->setPositionX(pBeforTaskConent->getPositionX()+pBeforTaskConent->getContentSize().width+_TASK_OFFSET_);
			 
			//to do
			UIViewDataManager::get_instance2()->loadData(UIViewDataManager::kARENAREWARDCELL);
			if(m_pArenaRewardData->getArenaChallengeCount()>=pChallengeRewardData->rewardChanllengeCount)
			{  
				//to do
				NFC_setLabelByFontID(_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_,pTableCell,UIViewDataManager::get_instance2()->getControlDataByID(_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_)->m_nFontStyleID);
				if(pChallengeRewardData->rewardHadGot)
				{
				   NFC_setMenuEnable(_CHALLENEGE_REWARD_BTN_TAG_,pTableCell,false); 
				   NFC_setLabelString(_CHALLENEGE_REWARD_LABEL_TAG_,pTableCell,SysLangDataManager::get_instance2()->GetSysLangById(_GOT_REWARD_TXTID_).c_str(),true);
				}
				else
				{
					NFC_bindSelectotForCellBtn(_CHALLENEGE_REWARD_BTN_TAG_,cellIndex,pTableCell,this,menu_selector(ArenaRewardWindow::CommonCellMenuSelector));
					NFC_setMenuEnable(_CHALLENEGE_REWARD_BTN_TAG_,pTableCell,true);
					NFC_setLabelString(_CHALLENEGE_REWARD_LABEL_TAG_,pTableCell,SysLangDataManager::get_instance2()->GetSysLangById(_GET_REWARD_TXTID_).c_str(),true);
				} 
			}
			else
			{ 
				NFC_setLabelByFontID(_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_,pTableCell,
					(int)UIViewDataManager::get_instance2()->getControlDataByID(_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_)->width_);
				NFC_bindSelectotForCellBtn(_CHALLENEGE_REWARD_BTN_TAG_,cellIndex,pTableCell,this,menu_selector(ArenaRewardWindow::CommonCellMenuSelector));
				NFC_setMenuEnable(_CHALLENEGE_REWARD_BTN_TAG_,pTableCell,true);
				NFC_setLabelString(_CHALLENEGE_REWARD_LABEL_TAG_,pTableCell,SysLangDataManager::get_instance2()->GetSysLangById(_DURATION_TXTID_).c_str(),true);
			}
		}  
	} 
} 

cocos2d::CCSize ArenaRewardWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return   m_szCELL;
}

cocos2d::extension::CCTableViewCell*  ArenaRewardWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int ArenaRewardWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{ 
	return  m_nMaxRewardSize;
}

  
void ArenaRewardWindow::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	  if(m_pTable)
	 { 
		 if(!m_pTable->cellAtIndex(m_nMaxRewardSize-1))
		 {
			 if(m_bScrollEnd)
			 {
				 m_bScrollEnd=false;
				 //显示
				 
				 NFC_setNodeVisable(_ARENAREWARD_GROW_TAG_ARROWMOVE_,m_pViewRoot,true);
				 NFC_setNodeVisable(_ARENAREWARD_GROW_TAG_,m_pViewRoot,false);				
				 //((CCGrapSprite *)m_pViewRoot->getChildByTag(_ARENAREWARD_GROW_TAG_))->setGrapTexture(false);
			 }
		 }
		 else
		 { 
			 if(!m_bScrollEnd)
			 {
				 m_bScrollEnd=true;
				 //置灰
				 NFC_setNodeVisable(_ARENAREWARD_GROW_TAG_ARROWMOVE_,m_pViewRoot,false);
				 NFC_setNodeVisable(_ARENAREWARD_GROW_TAG_,m_pViewRoot,true);	
				 //((CCGrapSprite *)m_pViewRoot->getChildByTag(_ARENAREWARD_GROW_TAG_))->setGrapTexture(true);
			 } 
		 }
	 } 
}

//////////////////////////////////////////////////////////////////////////
void   ArenaRewardWindow::showRewardMenuItem(int bgIndex,int iconIndex,cocos2d::CCNode * pParent,PRewardItemNode pRewardItemNode)
{
	int quality=-1;
	int iconid=-1;
	bool enabled=false;
	switch (pRewardItemNode->rewardItemType)
	{
	case  kDT_AWARD_OBJECT:
		{     
			quality=pRewardItemNode->rewardQuality;
			iconid=pRewardItemNode->rewardIconID;
			enabled=true;
			break;
		}
	case   kDT_AWARD_MONEY:
		{   
			quality=_GOLD_QUALITY_RESID_;
			iconid=_GOLD_ICON_RESID_;
			break;
		}
	case  kDT_AWARD_EXP:
		{
			quality=_EXP_QUALITY_RESID_;
			iconid=_EXP_ICON_RESID_;
			break;
		}
	case  kDT_AWARD_DIAMOND:
		{
			quality=_DIAMOND_QUALITY_RESID_;
			iconid=_DIAMOND_ICON_RESID_;
			break;
		}
	case kDT_AWARD_PRESTIGE:
		{
			quality=_PREGIST_QUALITY_RESID_;
			iconid=_PREGIST_ICON_RESID_;
			break;
		}
	case kDT_AWARD_POWER:
		{
			quality=_POWER_QUALITY_RESID_;
			iconid=_POWER_ICON_RESID_;
			break;
		}
	default:
		break;
	}	
	DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
	dd->ChangeObject(quality,iconid);
	dd->setEnabled(enabled);
}

void   ArenaRewardWindow::showRewardSpriteItem(int bgIndex,int iconIndex,cocos2d::CCNode * pParent,PRewardItemNode pRewardItemNode)
{
	switch (pRewardItemNode->rewardItemType)
	{
	case  kDT_AWARD_OBJECT:
		{     
			DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
			dd->ChangeObject(pRewardItemNode->rewardQuality,pRewardItemNode->rewardIconID);
			break;
		}
	case   kDT_AWARD_MONEY:
		{   
			DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
			dd->ChangeObject(_GOLD_QUALITY_RESID_,_GOLD_ICON_RESID_);
			break;
		}
	case  kDT_AWARD_EXP:
		{
			DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
			dd->ChangeObject(_EXP_QUALITY_RESID_,_EXP_ICON_RESID_);
			break;
		}
	case  kDT_AWARD_DIAMOND:
		{
			DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
			dd->ChangeObject(_DIAMOND_QUALITY_RESID_,_DIAMOND_ICON_RESID_);
			break;
		}
	case kDT_AWARD_PRESTIGE:
		{
			DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
			dd->ChangeObject(_PREGIST_QUALITY_RESID_,_PREGIST_ICON_RESID_);
			break;
		}
	case kDT_AWARD_POWER:
		{
			DTAwardBoard* dd=(DTAwardBoard*)pParent->getChildByTag(iconIndex);
			dd->ChangeObject(_POWER_QUALITY_RESID_,_POWER_ICON_RESID_);
			break;
		}
	default:
		break;
	}	
}


