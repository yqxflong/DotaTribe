#include "../include/LevelUpRewardActivityWindow.h"
#include "../include/UIViewDataManger.h"
#include "../include/IDStringDataManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NetSystem.h" 
#include "../include/DOTATribeApp.h"
#include "../include/ActivityPacket.h"
#include "../include/ActivityDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"
#include "../include/WindowManager.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/NFAnimationController.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/TimeSystem.h"


//////////////////////////////////////////////////////////////////////////
const  int   maxCellCount = 4;


LevelUpRewardActivityWindow::LevelUpRewardActivityWindow()
{
	m_WindowType = _TYPED_WINDOW_LEVELUPREWARDACTIVITYWINDOW_;
	m_pTable = NULL;
	m_szCELL = cocos2d::CCPointZero;
	m_offsetPoint = cocos2d::CCPointZero;
	m_pLevelUpRewardData = NULL;
	m_nLastPlayerLevel = 0;
	m_nLastRewardLevel = 0;
	m_CurWindowActiviId = 0;
}

LevelUpRewardActivityWindow::~LevelUpRewardActivityWindow()
{ 

}

bool   LevelUpRewardActivityWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LEVELUPREWARDACTIVITYWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LEVELUPREWARDACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LEVELUPREWARDACTIVITYWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);

	return IWindow::Init();
}

bool    LevelUpRewardActivityWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;  
		LoadUILayer();
		return true;
	} 
	while (false); 

	return false;
}


void   LevelUpRewardActivityWindow::LoadUILayer()
{ 
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLEVELUPREWARDACTIVITYWINDOW,m_pRootNode); 
	UpdateUIHandler();
}

 void    LevelUpRewardActivityWindow::Tick()
{
	IWindow::Tick();
}

void    LevelUpRewardActivityWindow::Destroy()
{ 
	m_offsetPoint = cocos2d::CCPointZero;
	m_nLastPlayerLevel = 0;
	m_nLastRewardLevel = 0;
	m_pRootNode->removeAllChildrenWithCleanup(true);
	LevelUpRewardActivityDataHandler::get_instance2()->DestroyData();
	m_pLevelUpRewardData = NULL;
    IWindow::Destroy();
}

void	LevelUpRewardActivityWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LEVELUPREWARDACTIVITYWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LEVELUPREWARDACTIVITYWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LEVELUPREWARDACTIVITYWINDOW_)
	{
		OnUpdateUIHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		//判断等级是否有变化
		int curPlayerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
		if(curPlayerLevel != m_nLastPlayerLevel)
		{  
			if(m_pLevelUpRewardData)
			{
				m_pLevelUpRewardData->updateRewardData(curPlayerLevel);
				_refreshTableView(m_pTable);
			}
		}
	}
}


void	LevelUpRewardActivityWindow::UpdateUIHandler()
{
	 BindSelectorForBtn();
	 SetTableView();
}
 
void   LevelUpRewardActivityWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	if (paramList.size()>0)
	{
		m_CurWindowActiviId = atoi(paramList.begin()->c_str());
		LEVELUPREWARDDATAHANDLER->setLevelUpRewardActiviId(m_CurWindowActiviId);
	}
	if(m_pRootNode->isVisible())
	 return ;
	Show(true);
}
 
void  LevelUpRewardActivityWindow::OnUpdateUIHandler(std::list<std::string>& paramList)
{
    int  receiptCode = atoi(paramList.begin()->c_str());
	dispatchReceiptCode(receiptCode);
}


void  LevelUpRewardActivityWindow::CommonSelectorHandler(cocos2d::CCObject * pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_LEVELUPREWARDACTIVITYWINDOW_);
}

void   LevelUpRewardActivityWindow::BindSelectorForBtn()
{
	//NFC_bindSelectorForBtn(_LURAW_REWARD_BTN_TAG_,m_pRootNode,this,menu_selector(LevelUpRewardActivityWindow::CommonSelectorHandler));
} 

//////////////////////////////////////////////////////////////////////////

void	LevelUpRewardActivityWindow::SetTableView()
{
	cocos2d::CCNode * pCellNode = m_pRootNode->getChildByTag(_LURAW_REWARD_CELL_TAG_);
	if( pCellNode )
	{
		m_szCELL = pCellNode->getContentSize();
	}
	m_pTable =(cocos2d::extension::CCTableView *)m_pRootNode->getChildByTag(_LURAW_REWARD_TABEL_TAG_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	_refreshTableView(m_pTable);
}

void	LevelUpRewardActivityWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLEVELUPREWARDACTIVITYCELL,pTableCell);
}

void	LevelUpRewardActivityWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{  
    if(cellIndex < getRewardItemCount() )
	{
		//等级
		NFC_setLabelStringInt(_LURAW_CELL_LEVEL_TAG_,pTableCell,m_pLevelUpRewardData->getRewardInfoVector().at(cellIndex)->getRewardLevel(),7012,true);
		size_t rewardSize = m_pLevelUpRewardData->getRewardInfoVector().at(cellIndex)->getRewardVector().size();
		int rewardOBJIndexArray[] = {_LURAW_CELL_REWARD_OBJ_1_TAG_,_LURAW_CELL_REWARD_OBJ_2_TAG_,_LURAW_CELL_REWARD_OBJ_3_TAG_,_LURAW_CELL_REWARD_OBJ_4_TAG_};

		COMMON_BEIGIN_ARRAY(size_t,maxCellCount)
			if(index < rewardSize)
			{
				PRewardItemNode pRewardItemNode = m_pLevelUpRewardData->getRewardInfoVector().at(cellIndex)->getRewardVector().at(index);
				if(pRewardItemNode)
				{
					//绑定事件 
					int key=rewardOBJIndexArray[index];
					DTAwardBoard* dd=(DTAwardBoard*)pTableCell->getChildByTag(key);
					dd->setIDX(key);
					dd->setAttachParam(cellIndex,index);
					dd->setTarget(this,menu_selector(LevelUpRewardActivityWindow::rewardInfoSelectorHandler));
					dd->setVisible(true);
					switch (pRewardItemNode->rewardItemType)
					{
					case  kDT_AWARD_OBJECT:
						{     
							dd->ChangeObject(pRewardItemNode->rewardQuality,pRewardItemNode->rewardIconID,pRewardItemNode->rewardItemCount);
							dd->setEnabled(true);
							break;
						}
					case   kDT_AWARD_MONEY:
						{    
							int quality=_GOLD_QUALITY_RESID_;
							dd->ChangeObject(quality,_GOLD_ICON_RESID_,pRewardItemNode->rewardItemCount);
							dd->setEnabled(true);
							break;
						}
					case  kDT_AWARD_EXP:
						{
							int quality=_EXP_QUALITY_RESID_;
							dd->ChangeObject(quality,_EXP_ICON_RESID_,pRewardItemNode->rewardItemCount);
							dd->setEnabled(true);
							break;
						}
					case  kDT_AWARD_DIAMOND:
						{
							int quality=_DIAMOND_QUALITY_RESID_;
							dd->ChangeObject(quality,_DIAMOND_ICON_RESID_,pRewardItemNode->rewardItemCount);
							dd->setEnabled(true);
							break;
						}
					case kDT_AWARD_PRESTIGE:
						{
							int quality=_PREGIST_QUALITY_RESID_;
							dd->ChangeObject(quality,_PREGIST_ICON_RESID_,pRewardItemNode->rewardItemCount);
							dd->setEnabled(true);
							break;
						}
					case kDT_AWARD_POWER:
						{
							int quality=_POWER_QUALITY_RESID_;
							dd->ChangeObject(quality,_POWER_ICON_RESID_,pRewardItemNode->rewardItemCount);
							dd->setEnabled(true);
							break;
						}
					default:
						break;
					}	   
					if(m_pLevelUpRewardData->getRewardInfoVector().at(cellIndex)->getCanReward())
					{ 
						NFC_bindSelectotForCellBtn(_LUEAW_CELL_REWARD_BTN_TAG_,cellIndex,pTableCell,this,menu_selector(LevelUpRewardActivityWindow::rewardBtnSelectorHandler));
						NFC_setMenuEnable(_LUEAW_CELL_REWARD_BTN_TAG_,pTableCell,true);
						NFC_PlayEffet(_LUEAW_CELL_REWARD_EFFECT_TAG_,pTableCell,true);
					}
					else
					{
						NFC_setMenuEnable(_LUEAW_CELL_REWARD_BTN_TAG_,pTableCell,false);
					    NFC_PlayEffet(_LUEAW_CELL_REWARD_EFFECT_TAG_,pTableCell,false);
					}
				}
			}
			else
			{
				NFC_setNodeVisable(rewardOBJIndexArray[index],pTableCell,false);
			} 
		COMMON_END_ARRAY 
  
	}
}

cocos2d::CCSize LevelUpRewardActivityWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCELL;
}

cocos2d::extension::CCTableViewCell* LevelUpRewardActivityWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int LevelUpRewardActivityWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(m_pLevelUpRewardData)
	{ 
		return   m_pLevelUpRewardData->getRewardInfoVector().size();
	}
	return  0;
}


void LevelUpRewardActivityWindow::_refreshTableView(cocos2d::extension::CCTableView* tb) const 
{
	tb->reloadData();
	if(m_offsetPoint.equals(cocos2d::CCPointZero))
	{ 
	   tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
	else
	{
		if(m_offsetPoint.y<=(tb->getViewSize().height-tb->getContentSize().height))
		{
			tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
		}
		else
		{
			tb->setContentOffset(m_offsetPoint);
		} 
	} 
}  

 
void  LevelUpRewardActivityWindow::dispatchReceiptCode(int receiptCode)
{
    switch(receiptCode)
	{
	case 0:	
		{
			//更新UI界面
			//绑定数据
			m_pLevelUpRewardData = LevelUpRewardActivityDataHandler::get_instance2()->getLevelUpRewardDatas();
			_refreshTableView(m_pTable);
			NFC_showCommunicationWating(false);
			break;
		}
	case 1:
		{
			//领取获得奖励回执 刷新页面
			//
			gotRewardUpdateHandler();
		}
	default:
		break;
	}
}


unsigned int  LevelUpRewardActivityWindow::getRewardItemCount()
{
	if(m_pLevelUpRewardData)
	{ 
		return   m_pLevelUpRewardData->getRewardInfoVector().size();
	}
	return  0;
}

 

void  LevelUpRewardActivityWindow::rewardInfoSelectorHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite&&m_pLevelUpRewardData)
	{ 
		int cellIndex = pMenuItemSprite->getAttachData1();
		int cellInterIndex = pMenuItemSprite->getAttachData2();
		PRewardItemNode pRewardItemNode = m_pLevelUpRewardData->getRewardInfoVector().at(cellIndex)->getRewardVector().at(cellInterIndex);
		if(pRewardItemNode&&pRewardItemNode->rewardItemType == 0)
		{ 
			 NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pRewardItemNode->rewardTemplateID, _TYPED_WINDOW_LEVELUPREWARDACTIVITYWINDOW_);
		} 
	}
}
 


void  LevelUpRewardActivityWindow::rewardBtnSelectorHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite&&m_pLevelUpRewardData)
	{  
		BTN_INTERVAL("LEVELUPREWARD",_COMMON_BTN_CLICK_INTERVAL_SMALL)
		m_nLastPlayerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
		NFC_showCommunicationWating(true);
		m_nLastRewardLevel = m_pLevelUpRewardData->getRewardInfoVector().at(pMenuItemSprite->getIDX())->getRewardLevel();
		m_offsetPoint = m_pTable->getContentOffset();
		C2SGetLevelUpRewardPacket getLevelUpReward(m_nLastRewardLevel);
		getLevelUpReward.Send(); 
	}
}

void  LevelUpRewardActivityWindow::gotRewardUpdateHandler()
{
	//删除当前子项，刷新列表
	m_pLevelUpRewardData->removeRewardInfoItem(m_nLastRewardLevel);
	if(m_pLevelUpRewardData->getRewardInfoVector().empty())
	{
		ActivityInfoItem* pAct = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(m_CurWindowActiviId);
		pAct->setActivityOpen(0);
		ActivityDataHandler::get_instance2()->HasSurplusActivity();
		PushEvent(_TYPED_EVENT_DELETE_ACTIVITY_);
		return ;
	}
	//设置特效
	if (ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(m_CurWindowActiviId))
	{
		ActivityInfoItem* pAct = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(m_CurWindowActiviId);
		pAct->setActivityOpen(pAct->getActivityOpen() -1);
		if (pAct->getActivityOpen() == 0)
		{
			ActivityDataHandler::get_instance2()->HasSurplusActivity();
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEEFFECT_ACTIVITY_,_to_event_param_(m_CurWindowActiviId));
		}
	}
	_refreshTableView(m_pTable);
	NFC_showCommunicationWating(false);
}
