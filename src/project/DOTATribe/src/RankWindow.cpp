#include "../include/RankWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h" 
#include "../include/EngineSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/FriendDataHandler.h"
#include "../include/NFAnimationController.h"
#include "../include/CPriorityLayerColor.h"
 
using namespace std;
 
#define  _START_NUMBER_INDEX_		547
#define  _END_NUMBER_INDEX_			550
#define  _NORMAL_NUNBER_BG_INDEX_   551
#define  _DEFAULT_NUMBER_ICON_NUM_   3


//#define  _RANK_HEAD_ICON_SCALE_  0.37f

//////////////////////////////////////////////////////////////////////////
//文字ID
#define  _LV_TXT_ID_    612
#define  _LV_FIGHT_ID_  463
#define  _LV_FLOOR_ID_	615
#define  _LV_SCORE_ID_	2060

USING_NS_CC;

RankWindow::RankWindow()
{
	m_WindowType  =  _TYPED_WINDOW_RANK_WINDOW_;
	m_pTable=NULL;
	m_szCELL=CCSizeZero;
	m_pViewRoot=NULL;

	m_tRankType = -1;
	m_pArenaRankData = NULL;
	m_pTowerRankList = NULL;
	m_pBossRankList = NULL;
}

bool RankWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_RANKWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_RANKWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_RANKWINDOW_, true);

	return IWindow::Init();
}



bool RankWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
		 break;
		 if(!m_pRootNode->isVisible())
	     LoadUIControl();  
		return true;
	} 
	while (false);

	return false;
}

void RankWindow::Tick()
{ 
	IWindow::Tick();
}


void RankWindow::Destroy()
{
	m_tRankType = -1;
	if(m_pRootNode!=NULL)
	{
		m_pViewRoot=NULL;
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}
	DestroyData();
	IWindow::Destroy();
}

void RankWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_RANKWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_RANKWINDOW_)
	{ 
		Destroy();
	}
	else if(iEventType==_TYPED_EVENT_UPDATE_RANKWINDOW_)
	{

	}
}

void   RankWindow::CallBackBtnClickHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
		case  _RANKINGLIST_CLOSE_BTN_TAG_:
			{ 
				PushEvent(_TYPED_EVENT_HIDE_RANKWINDOW_);
				break; 
			}
		default: 
			break;
		}
	}
}


void   RankWindow::LookOverRoleInfoSelector(cocos2d::CCObject * pSender)
{
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem)
	{   
		if(m_tRankType==_RANK_TYPE_AREANA_)
		{
			if(pMenuItem->getIDX()<m_pArenaRankData->rankListVec.size())
			{
				FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(m_pArenaRankData->rankListVec.at(pMenuItem->getIDX())->roleID,m_WindowType);
			}
		}
		else if(m_tRankType==_RANK_TYPE_TOWER_)
		{
			if(pMenuItem->getIDX()<m_pTowerRankList->rankVector.size())
			{
				FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(m_pTowerRankList->rankVector.at(pMenuItem->getIDX())->playerId,m_WindowType);
			}
		}
		else if(m_tRankType == _RANK_TYPE_BOSS_)
		{
			if(pMenuItem->getIDX()<m_pBossRankList->rankVector.size())
			{
				FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(m_pBossRankList->rankVector.at(pMenuItem->getIDX())->playerId,m_WindowType);
			}
		}
	}
}



void RankWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
    if(m_pRootNode->isVisible())
	return ;

	if(paramList.size() == 1)
	{
		std::string rtype = *(paramList.begin());
		sscanf(rtype.c_str(), "%d", &m_tRankType);
	}
	else
	{
		m_tRankType = _RANK_TYPE_AREANA_;
	}
	InitData();
	Show(true);
	NFC_Action_fallDown(m_pViewRoot);
}  


void    RankWindow::LoadUIControl()
{   
	InitLayout(); 
} 

  
void    RankWindow::InitLayout()
{
	if(m_pRootNode!=NULL)
	{
		m_pViewRoot=cocos2d::CCNode::create();
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::KARENARANKLISTVIEW,m_pViewRoot);    
		m_pRootNode->addChild(m_pViewRoot,1);
		CPriorityLayerColor * pPriorityColorLayer=(CPriorityLayerColor *)m_pViewRoot->getChildByTag(_RANKINGLIST_GRAPLAYER_TAG_);
		pPriorityColorLayer->removeFromParent();
		m_pRootNode->addChild(pPriorityColorLayer,-1);
	}
	InitStaticMapBtn();
	SetTableView();
}

void    RankWindow::InitStaticMapBtn()
{
	cocos2d::CCMenu * pMemu=(cocos2d::CCMenu *)m_pViewRoot->getChildByTag(_RANKINGLIST_CLOSE_BTN_TAG_);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(_RANKINGLIST_CLOSE_BTN_TAG_);
			pMenuItem->setTarget(this,menu_selector(RankWindow::CallBackBtnClickHandler));
		}
	} 
}

void    RankWindow::SetTableView()
{
	CCNode* cc=m_pViewRoot->getChildByTag(_RANKINGLIST_TABLE_CELL_TAG_);
	m_szCELL=cc->getContentSize();

	m_pTable =(cocos2d::extension::CCTableView *)m_pViewRoot->getChildByTag(_RANKINGLIST_TABLE_TAG_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);

}

void    RankWindow::InitData()
{ 
	if(m_tRankType == _RANK_TYPE_AREANA_)
	{
		if(ArenaRankDataHandler::get_instance2()->m_pArenaRankData!=NULL)
		{
			m_pArenaRankData=ArenaRankDataHandler::get_instance2()->m_pArenaRankData;
		}
	}
	else if(m_tRankType == _RANK_TYPE_TOWER_)
	{
		if(CLIMBTOWERDATAHANDLER->m_pRankList != NULL)
		{
			m_pTowerRankList = CLIMBTOWERDATAHANDLER->m_pRankList;
		}
	}
	else if(m_tRankType == _RANK_TYPE_BOSS_)
	{
		if(BOSSSCOREDATAHANDLER->m_pRankList)
		{
			m_pBossRankList = BOSSSCOREDATAHANDLER->m_pRankList;
		}
	}

	m_pTable = (cocos2d::extension::CCTableView *)m_pViewRoot->getChildByTag(_RANKINGLIST_TABLE_TAG_);
	_refreshTableView(m_pTable);
}


void	RankWindow::DestroyData()
{
	m_pArenaRankData=NULL;
	m_pTowerRankList=NULL;
	m_pBossRankList=NULL;
}

void    RankWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::KARENARANKCELL,pTableCell);
}

void    RankWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(m_tRankType == _RANK_TYPE_AREANA_)
	{
		if(m_pArenaRankData == NULL)
			return;
	}
	else if(m_tRankType == _RANK_TYPE_TOWER_)
	{
		if(m_pTowerRankList == NULL)
			return;
	}
	else if(m_tRankType == _RANK_TYPE_BOSS_)
	{
		if(m_pBossRankList == NULL)
			return;
	}

	SetRankNumber(pTableCell,cellIndex);
	SetRankRoleIconID(pTableCell,cellIndex);
	SetRankRoleName(pTableCell,cellIndex);
	SetRankRoleLevel(pTableCell,cellIndex);
	SetRankRoleBltValue(pTableCell,cellIndex);
	SetRankRoleLookOverBtn(pTableCell,cellIndex);

}
void    RankWindow::SetRankNumber(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(pTableCell!=NULL)
	{ 
		std::string  numberName="";
		bool    isNoramlNumber=false;
		int     rankNumber=0;
		if(m_tRankType == _RANK_TYPE_AREANA_)
		{
			if(cellIndex<m_pArenaRankData->rankListVec.size())
			{ 
				rankNumber=m_pArenaRankData->rankListVec.at(cellIndex)->roleRankScore;
				if(rankNumber<=_DEFAULT_NUMBER_ICON_NUM_)
				{
					numberName=ResourceIDDataManager::get_instance2()->getDataByID(rankNumber+_START_NUMBER_INDEX_);
				}
				else
				{
					isNoramlNumber=true;
					numberName=ResourceIDDataManager::get_instance2()->getDataByID(_NORMAL_NUNBER_BG_INDEX_);
				}
			}
		}
		else if(m_tRankType == _RANK_TYPE_TOWER_)
		{

			if(cellIndex<m_pTowerRankList->rankVector.size())
			{ 
				rankNumber=m_pTowerRankList->rankVector.at(cellIndex)->score;
				if(rankNumber<=_DEFAULT_NUMBER_ICON_NUM_)
				{
					numberName=ResourceIDDataManager::get_instance2()->getDataByID(rankNumber+_START_NUMBER_INDEX_);
				}
				else
				{
					isNoramlNumber=true;
					numberName=ResourceIDDataManager::get_instance2()->getDataByID(_NORMAL_NUNBER_BG_INDEX_);
				}
			}
		} 
		else if(m_tRankType == _RANK_TYPE_BOSS_)
		{
			if(cellIndex<m_pBossRankList->rankVector.size())
			{ 
				rankNumber=m_pBossRankList->rankVector.at(cellIndex)->rank;
				if(rankNumber<=_DEFAULT_NUMBER_ICON_NUM_)
				{
					numberName=ResourceIDDataManager::get_instance2()->getDataByID(rankNumber+_START_NUMBER_INDEX_);
				}
				else
				{
					isNoramlNumber=true;
					numberName=ResourceIDDataManager::get_instance2()->getDataByID(_NORMAL_NUNBER_BG_INDEX_);
				}
			}
		} 
		cocos2d::CCSprite * pImageSprite=(cocos2d::CCSprite *)pTableCell->getChildByTag(_RANKCELL_RANK_NUMBER_BG_TAG_);
		if(pImageSprite!=NULL&&!numberName.empty())
		{   
			pImageSprite->setProperty("File",numberName.c_str());
		}
		cocos2d::CCLabelTTF * pNumberTTF=(cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_RANKCELL_RANK_NUMBER_VALUE_TAG_);
		if(isNoramlNumber)
		{		
			char numberValue[16]={0};
			sprintf(numberValue,"%d",rankNumber);
			pNumberTTF->setString(numberValue);
			pNumberTTF->setVisible(true);	 
		}
		else
		{
			pNumberTTF->setVisible(false);
		}
	} 
}
void    RankWindow::SetRankRoleIconID(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(pTableCell!=NULL)
	{
		cocos2d::CCSprite * pImageSprite=(cocos2d::CCSprite *)pTableCell->getChildByTag(_RANKCELL_RANK_ROLE_HEAD_TAG_);
		if(pImageSprite!=NULL)
		{
			if(m_tRankType == _RANK_TYPE_AREANA_)
			{
				if(cellIndex<m_pArenaRankData->rankListVec.size())
				{
					int roleIconID=m_pArenaRankData->rankListVec.at(cellIndex)->roleIconID;
					std::string  roleIconIDName=ResourceIDDataManager::get_instance2()->getDataByID(roleIconID);	
					if(!roleIconIDName.empty())
					pImageSprite->setProperty("File",roleIconIDName.c_str());
				}
			}
			else if(m_tRankType == _RANK_TYPE_TOWER_)
			{
				if(cellIndex < m_pTowerRankList->rankVector.size())
				{
					int roleIconID=m_pTowerRankList->rankVector.at(cellIndex)->iconId;
					std::string  roleIconIDName=ResourceIDDataManager::get_instance2()->getDataByID(roleIconID);
					if(!roleIconIDName.empty())
						pImageSprite->setProperty("File",roleIconIDName.c_str());
				}
			}
			else if(m_tRankType == _RANK_TYPE_BOSS_)
			{
				if(cellIndex < m_pBossRankList->rankVector.size())
				{
					int roleIconID=m_pBossRankList->rankVector.at(cellIndex)->iconId;
					std::string  roleIconIDName=ResourceIDDataManager::get_instance2()->getDataByID(roleIconID);
					if(!roleIconIDName.empty())
						pImageSprite->setProperty("File",roleIconIDName.c_str());
				}
			}
		}
	} 
}
void    RankWindow::SetRankRoleName(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(pTableCell!=NULL)
	{
		cocos2d::CCLabelTTF * pNode=(cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_RANKCELL_RANK_ROLENAME_);
		if(pNode!=NULL)
		{  
			if(m_tRankType == _RANK_TYPE_AREANA_)
			{
				if(cellIndex<m_pArenaRankData->rankListVec.size())
				{
					pNode->setString(m_pArenaRankData->rankListVec.at(cellIndex)->roleName.c_str());
				}
			}
			else if(m_tRankType == _RANK_TYPE_TOWER_)
			{
				if(cellIndex<m_pTowerRankList->rankVector.size())
				{
					pNode->setString(m_pTowerRankList->rankVector.at(cellIndex)->name.c_str());
				}
			}
			else if(m_tRankType == _RANK_TYPE_BOSS_)
			{
				if(cellIndex<m_pBossRankList->rankVector.size())
				{
					pNode->setString(m_pBossRankList->rankVector.at(cellIndex)->name.c_str());
				}
			}
		}
	} 
}
void    RankWindow::SetRankRoleLevel(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(pTableCell!=NULL)
	{
		cocos2d::CCLabelTTF * pNode=(cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_RANKCELL_RANK_ROLELEVEL_);
		if(pNode!=NULL)
		{  
			if(m_tRankType == _RANK_TYPE_AREANA_)
			{
				if(cellIndex<m_pArenaRankData->rankListVec.size())
				{
					char levelStr[32]={0};
					sprintf(levelStr,SysLangDataManager::get_instance2()->GetSysLangById(_LV_TXT_ID_).c_str(),m_pArenaRankData->rankListVec.at(cellIndex)->roleLevel);
					pNode->setString(levelStr);
				}
			}
			else if(m_tRankType == _RANK_TYPE_TOWER_)
			{
				if(cellIndex<m_pTowerRankList->rankVector.size())
				{
					char levelStr[32]={0};
					sprintf(levelStr,SysLangDataManager::get_instance2()->GetSysLangById(_LV_TXT_ID_).c_str(),m_pTowerRankList->rankVector.at(cellIndex)->level);
					pNode->setString(levelStr);
				}
			}
			else if(m_tRankType == _RANK_TYPE_BOSS_)
			{
				if(cellIndex<m_pBossRankList->rankVector.size())
				{
					char levelStr[32]={0};
					sprintf(levelStr,SysLangDataManager::get_instance2()->GetSysLangById(_LV_TXT_ID_).c_str(),m_pBossRankList->rankVector.at(cellIndex)->level);
					pNode->setString(levelStr);
				}
			}

		}
	} 
}


void    RankWindow::SetRankRoleBltValue(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(pTableCell!=NULL)
	{
		cocos2d::CCLabelTTF * pNode=(cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_RANKCELL_RANK_ROLEBLT_);
		if(pNode!=NULL)
		{  
			if(m_tRankType == _RANK_TYPE_AREANA_)
			{
				if(cellIndex<m_pArenaRankData->rankListVec.size())
				{
					char btlScore[32]={0};
					sprintf(btlScore,SysLangDataManager::get_instance2()->GetSysLangById(_LV_FIGHT_ID_).c_str(),m_pArenaRankData->rankListVec.at(cellIndex)->roleBltScore);
					pNode->setString(btlScore);
				}
			}
			else if(m_tRankType == _RANK_TYPE_TOWER_)
			{
				if(cellIndex < m_pTowerRankList->rankVector.size())
				{
					char btlScore[32]={0};
					sprintf(btlScore,SysLangDataManager::get_instance2()->GetSysLangById(_LV_FLOOR_ID_).c_str(),m_pTowerRankList->rankVector.at(cellIndex)->floor);
					pNode->setString(btlScore);
				}
			}
			else if(m_tRankType == _RANK_TYPE_BOSS_)
			{
				if(cellIndex < m_pBossRankList->rankVector.size())
				{
					char btlScore[32]={0};
					sprintf(btlScore,SysLangDataManager::get_instance2()->GetSysLangById(_LV_SCORE_ID_).c_str(),m_pBossRankList->rankVector.at(cellIndex)->score);
					pNode->setString(btlScore);
				}
			}
		}
	} 
}

void	   RankWindow::SetRankRoleLookOverBtn(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	if(pTableCell)
	{ 
		cocos2d::CCMenu * pMenu=(cocos2d::CCMenu *)pTableCell->getChildByTag(_RANLCELL_RANK_LOOKOVER_BTN_);
		CMenuItemSprite * pMenuItem=(CMenuItemSprite *)pMenu->getChildByTag(0);
		pMenuItem->setIDX(cellIndex);
		pMenuItem->setTarget(this,menu_selector(RankWindow::LookOverRoleInfoSelector));
	}
}




cocos2d::CCSize RankWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return   m_szCELL;
}

cocos2d::extension::CCTableViewCell*  RankWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int RankWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(m_tRankType == _RANK_TYPE_AREANA_)
	{
		if(m_pArenaRankData!=NULL)
		{
			return m_pArenaRankData->rankListVec.size();
		}
	}
	else if(m_tRankType == _RANK_TYPE_TOWER_)
	{
		if(m_pTowerRankList!=NULL)
		{
			return m_pTowerRankList->rankVector.size();
		}
	}
	else if(m_tRankType == _RANK_TYPE_BOSS_)
	{
		if(m_pBossRankList!=NULL)
		{
			return m_pBossRankList->rankVector.size();
		}
	}

	return 0;

}


