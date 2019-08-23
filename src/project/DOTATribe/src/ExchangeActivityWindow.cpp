#include "../include/ExchangeActivityWindow.h"
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
#include "../include/RoleInfoDataHandler.h"

 
//////////////////////////////////////////////////////////////////////////  
const  int  maxExchangeNeedItemsCount = 3;
const  int  showVIPLevelConditionTID =  7028;
const  int  leftExchangeCountTID =  7027;




 
ExchangeActivityWindow::ExchangeActivityWindow()
{
	m_WindowType = _TYPED_WINDOW_EXCHANGEACTIVITYWINDOW_;
	m_pTable = NULL;
	m_szCELL = cocos2d::CCPointZero;
	m_pExchangeInfoData = NULL;
	m_bActivityEnd = false;
	m_nActivityItemID = 0;
	m_offSetPoint = cocos2d::CCPointZero;
}

ExchangeActivityWindow::~ExchangeActivityWindow()
{  
}

bool   ExchangeActivityWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_EXCHANGEACTIVITYWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_EXCHANGEACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_EXCHANGEACTIVITYWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_REFRESH_EXCHANGEACTIVITYWINDOW_,true); 
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true); 
	
	return IWindow::Init();
}

bool    ExchangeActivityWindow::Load()
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


void   ExchangeActivityWindow::LoadUILayer()
{ 
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEXCHANGEACTIVITYWINDOW,m_pRootNode); 
	SetTableView();
}

void    ExchangeActivityWindow::Tick()
{
	IWindow::Tick();
}

void    ExchangeActivityWindow::Destroy()
{
	m_offSetPoint = cocos2d::CCPointZero;
	m_nActivityItemID = 0;
	m_bActivityEnd = false;
	m_pExchangeInfoData = NULL;
	m_pRootNode->removeAllChildrenWithCleanup(true); 
	IWindow::Destroy();
}

void	ExchangeActivityWindow::TimerEventHandler(int eventType,std::string attachParam)
{
	if(eventType==CTimerEventProtocol::_COUNTDONW_END_TYPE_)
	{
	  // 禁止所有按钮使能
		m_bActivityEnd = true;
	    _refreshTableView(m_pTable);
	}
}


void	ExchangeActivityWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_EXCHANGEACTIVITYWINDOW_)
	{
		if(!paramList.empty())
		{ 
			int activityItemID = atoi(paramList.begin()->c_str());
			m_nActivityItemID = activityItemID;
		}
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_EXCHANGEACTIVITYWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_EXCHANGEACTIVITYWINDOW_)
	{
		NFC_showCommunicationWating(false);
		int  receiptCode = atoi(paramList.begin()->c_str());
		dispatchReceiptCode(receiptCode);
	}
	else if (iEventType == _TYPED_EVENT_REFRESH_EXCHANGEACTIVITYWINDOW_)
	{
		NFC_showCommunicationWating(true);
		C2SChioseActivityPacket  chioseActivity(m_nActivityItemID);
		chioseActivity.Send();
	}  
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{ 
		NFC_showCommunicationWating(false);
		refreshUIWithExchangeInfoData();
	}
}

 
void   ExchangeActivityWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	NFC_showCommunicationWating(false);
}
 
void  ExchangeActivityWindow::CommonSelectorHandler(cocos2d::CCObject * pSender)
{
	//PushEvent(_TYPED_EVENT_HIDE_EXCHANGEACTIVITYWINDOW_);
}



//////////////////////////////////////////////////////////////////////////

void	ExchangeActivityWindow::SetTableView()
{
	cocos2d::CCNode * pCellNode = m_pRootNode->getChildByTag(_EXCHANGEACTIVITY_CELL_TAG_);
	if( pCellNode )
	{
		m_szCELL = pCellNode->getContentSize();
	}
	m_pTable =(cocos2d::extension::CCTableView *)m_pRootNode->getChildByTag(_EXCHANGEACTIVITY_TABEL_TAG_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	_refreshTableView(m_pTable);
}

void	ExchangeActivityWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEXCHANGEACTIVITYCELL,pTableCell);
}

void	ExchangeActivityWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{    
	if(cellIndex < getExchangeItemsCount())
	{ 
		ExchangeItemInfo *  pExchangeItemInfo = m_pExchangeInfoData->getExchangeItemVector().at(cellIndex);
		if(pExchangeItemInfo)
		{  
			size_t  needItemCount = pExchangeItemInfo->getNeedItemsVector().size();
			int		itemIconArray[] ={_EXCHANGE_CELL_ITEM_1_TAG,_EXCHANGE_CELL_ITEM_2_TAG,_EXCHANGE_CELL_ITEM_3_TAG};
			int		itemNumArray[] ={_EXCHANGE_CELL_ITEM_1_NUM_TAG,_EXCHANGE_CELL_ITEM_2_NUM_TAG,_EXCHANGE_CELL_ITEM_3_NUM_TAG};
			TemplateItemInfoData *  pTemplateIndoData = NULL;
			bool    isCanExchangeFromNeedItem = true; 
			for(int index = 0;index < maxExchangeNeedItemsCount ;index++ )
			{  
				if(index<needItemCount)
				{ 
					pTemplateIndoData = pExchangeItemInfo->getNeedItemsVector().at(index); 
					isCanExchangeFromNeedItem &= pTemplateIndoData->getItemHadCount() >= pTemplateIndoData->getItemNeedCount() ? true:false;
					showNeedItemInfoWithData(cellIndex,index,itemIconArray[index],itemNumArray[index],pTemplateIndoData,pTableCell); 			
				}
				else
				{ 
					NFC_setNodeVisable(itemIconArray[index],pTableCell,false); 
					NFC_setNodeVisable(itemNumArray[index],pTableCell,false);
				} 
			}   
			//检测VIP等级和剩余次数
			//显示VIP提示
			//显示剩余次数 
			if(pExchangeItemInfo->getVipLevel() > 0)
			{
				//显示VIP等级
				NFC_setLabelStringInt(_EXCHANGE_CELL_EXCHANGE_VIP_TIPS_TAG,pTableCell,pExchangeItemInfo->getVipLevel(),showVIPLevelConditionTID,true);
			}
			else
			{
				//隐藏VIP等级
				NFC_setNodeVisable(_EXCHANGE_CELL_EXCHANGE_VIP_TIPS_TAG,pTableCell,false);
			} 
			//显示剩余次数
			NFC_setLabelStringInt(_EXCHANGE_CELL_EXCHANGE_LAST_LABEL_TAG,pTableCell,pExchangeItemInfo->getLeftExchangeTimes(),leftExchangeCountTID,true);
			 
			UIViewDataManager::get_instance2()->loadData(UIViewDataManager::kEXCHANGEACTIVITYCELL); 
			if(pExchangeItemInfo->getLeftExchangeTimes() > 0)
			{
				NFC_setLabelByFontID(_EXCHANGE_CELL_EXCHANGE_LAST_LABEL_TAG,pTableCell,UIViewDataManager::get_instance2()->getControlDataByID(_EXCHANGE_CELL_EXCHANGE_LAST_LABEL_TAG)->m_nFontStyleID);
			}
			else
			{  
				NFC_setLabelByFontID(_EXCHANGE_CELL_EXCHANGE_LAST_LABEL_TAG,pTableCell,UIViewDataManager::get_instance2()->getControlDataByID(_EXCHANGE_CELL_EXCHANGE_LAST_LABEL_TAG)->width_);
			}
			  
			if(isCanExchangeFromNeedItem&&!m_bActivityEnd)
			{
				if(RoleInfoDataHandler::get_instance2()->m_pRIData->vipLevel_ >= pExchangeItemInfo->getVipLevel()&&pExchangeItemInfo->getLeftExchangeTimes()>0)
				{  
					NFC_setMenuEnable(_EXCHANGE_CELL_EXCHANGE_BTN_TAG,pTableCell,true);
					NFC_bindSelectotForCellBtn(_EXCHANGE_CELL_EXCHANGE_BTN_TAG,cellIndex,pTableCell,this,menu_selector(ExchangeActivityWindow::exchangeBtnSelectorHandler));
				    NFC_setMenuSpriteAttachParam(_EXCHANGE_CELL_EXCHANGE_BTN_TAG,pTableCell,cellIndex,pExchangeItemInfo->getExchamgeItemID());
				}
				else
				{
					//置灰按钮
					NFC_setMenuEnable(_EXCHANGE_CELL_EXCHANGE_BTN_TAG,pTableCell,false);
				}
			}
			else
			{
				//直接置灰按钮
				NFC_setMenuEnable(_EXCHANGE_CELL_EXCHANGE_BTN_TAG,pTableCell,false);
			}
			showTargetItemInfoWithData(cellIndex,_EXCHANGE_CELL_REWARD_ITEM_TAG,_EXCHANGE_CELL_REWARD_ITEM_TAG,_EXCHANGE_CELL_REWARD_NUM_TAG,pExchangeItemInfo->getTargetItem(),pTableCell);
	    } 
	}
}

cocos2d::CCSize ExchangeActivityWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCELL;
}

cocos2d::extension::CCTableViewCell* ExchangeActivityWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int ExchangeActivityWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{ 
	 if(m_pExchangeInfoData)
	 { 
		 return  m_pExchangeInfoData->getExchangeItemVector().size();
	 }
	 return 0;
}


void  ExchangeActivityWindow::dispatchReceiptCode(int receiptCode)
{
	//此消息用于绑定指定的内存数据并且刷新页面  
	m_pExchangeInfoData = ExchangeActivityDataHandler::get_instance2()->getExchangeInfoItemByID((short)receiptCode);
	//刷新页面
	refreshUIWithExchangeInfoData(); 
}

void  ExchangeActivityWindow::refreshUIWithExchangeInfoData()
{
	//刷新倒计时时间 
	if(m_pExchangeInfoData->getLeftActivityMinute()==0)
	{
		m_bActivityEnd = true;
	}
	else
	{
		CTimeLabel * pTimeLabler = (CTimeLabel * )NFC_getNode(_EXCHANGEACTIVITY_COUNTDOWN_LABEL_TAG_,m_pRootNode);
		if(pTimeLabler)
		{ 
			pTimeLabler->setTimerEventDelegate(this);
			pTimeLabler->StartActivityMiniteTimer(m_pExchangeInfoData->getLeftActivityMinute());  			
		}
	} 
	//更新数据
	 _refreshTableView(m_pTable);
}

void  ExchangeActivityWindow::_refreshTableView(cocos2d::extension::CCTableView* tb) const
{
	tb->reloadData();
	if(m_offSetPoint.equals(cocos2d::CCPointZero))
	{ 
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
	else
	{ 
		if(m_offSetPoint.y<=(tb->getViewSize().height-tb->getContentSize().height))
		{
		   tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
		}
		else
		{
		   tb->setContentOffset(m_offSetPoint);
		} 
	}
}

unsigned int  ExchangeActivityWindow::getExchangeItemsCount()
{
	if(m_pExchangeInfoData)
	{
		return  m_pExchangeInfoData->getExchangeItemVector().size();
	}
	return 0;
}



void  ExchangeActivityWindow::exchangeItemInfoBtnSelectorHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite&&m_pExchangeInfoData)
	{ 
		int cellIndex = pMenuItemSprite->getIDX();
		int cellItemIndex = pMenuItemSprite->getAttachData1();
		if(cellItemIndex==_EXCHANGE_CELL_REWARD_ITEM_TAG)
		{
		   RewardItemNode * pTargetItem = m_pExchangeInfoData->getExchangeItemVector().at(cellIndex)->getTargetItem();
		   if(pTargetItem&&pTargetItem->rewardItemType==0)
		   {
			   NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pTargetItem->rewardTemplateID, _TYPED_WINDOW_EXCHANGEACTIVITYWINDOW_);
		   }
		}
		else
		{
			TemplateItemInfoData * pTemplateData = m_pExchangeInfoData->getExchangeItemVector().at(cellIndex)->getNeedItemsVector().at(cellItemIndex);
			if(pTemplateData->getItemType()==0)
			{
				NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pTemplateData->getItemTemplateID(), _TYPED_WINDOW_EXCHANGEACTIVITYWINDOW_);
			}  
		}  
	}
}


void  ExchangeActivityWindow::exchangeBtnSelectorHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite&&m_pExchangeInfoData)
	{  
		int exchangeID = pMenuItemSprite->getAttachData1(); 
		short exchangeIDShort =(short)exchangeID;
		m_offSetPoint = m_pTable->getContentOffset();
		C2SExchangeExchangePacket  exchangePacket(m_pExchangeInfoData->getActivityID(),exchangeIDShort);
		exchangePacket.Send();
	} 
}

void  ExchangeActivityWindow::showNeedItemInfoWithData(int cellIndex,int cellItemIndex,int iconIndex,int labelIndex, TemplateItemInfoData * pTemplateInfoData,cocos2d::extension::CCTableViewCell * pCell)
{ 
	//绑定事件  
	DTAwardBoard* dd=(DTAwardBoard*)pCell->getChildByTag(iconIndex);
	dd->setIDX(cellIndex);
	dd->setAttachParam(cellItemIndex);
	dd->setTarget(this,menu_selector(ExchangeActivityWindow::exchangeItemInfoBtnSelectorHandler)); 
	dd->setVisible(true);
	switch (pTemplateInfoData->getItemType())
	{
	case  kDT_AWARD_OBJECT:
		{     
			dd->ChangeObject(pTemplateInfoData->getItemQuality(),pTemplateInfoData->getItemIconID(),-1);
			dd->setEnabled(true);
			break;
		}
	case   kDT_AWARD_MONEY:
		{    
			dd->ChangeObject(_GOLD_QUALITY_RESID_,_GOLD_ICON_RESID_,-1);
			dd->setEnabled(true);
			break;
		}
	case  kDT_AWARD_EXP:
		{
			dd->ChangeObject(_EXP_QUALITY_RESID_,_EXP_ICON_RESID_,-1);
			dd->setEnabled(true);
			break;
		}
	case  kDT_AWARD_DIAMOND:
		{
			dd->ChangeObject(_DIAMOND_QUALITY_RESID_,_DIAMOND_ICON_RESID_,-1);
			dd->setEnabled(true);
			break;
		}
	case kDT_AWARD_PRESTIGE:
		{
			dd->ChangeObject(_PREGIST_QUALITY_RESID_,_PREGIST_ICON_RESID_,-1);
			dd->setEnabled(true);
			break;
		}
	case kDT_AWARD_POWER:
		{
			dd->ChangeObject(_POWER_QUALITY_RESID_,_POWER_ICON_RESID_,-1);
			dd->setEnabled(true);
			break;
		}
	default:
		break;
	}  
	//显示数值 
	char  strBuffer[32] = {0};
	sprintf(strBuffer,"%d",pTemplateInfoData->getItemNeedCount());
	NFC_setLabelString(labelIndex,pCell,strBuffer,true);
	UIViewDataManager::get_instance2()->loadData(UIViewDataManager::kEXCHANGEACTIVITYCELL);
	if(pTemplateInfoData->getItemHadCount()>=pTemplateInfoData->getItemNeedCount())
	{
		NFC_setLabelByFontID(labelIndex,pCell,UIViewDataManager::get_instance2()->getControlDataByID(labelIndex)->m_nFontStyleID);
	}
	else
	{
		NFC_setLabelByFontID(labelIndex,pCell,UIViewDataManager::get_instance2()->getControlDataByID(labelIndex)->width_);
	}
}


void  ExchangeActivityWindow::showTargetItemInfoWithData(int cellIndex,int cellItemIndex,int iconIndex,int labelIndex, RewardItemNode * pItemInfoData,cocos2d::extension::CCTableViewCell * pCell)
{ 
	//绑定事件  
	DTAwardBoard* dd=(DTAwardBoard*)pCell->getChildByTag(iconIndex);
	dd->setIDX(cellIndex);
	dd->setAttachParam(cellItemIndex);
	dd->setTarget(this,menu_selector(ExchangeActivityWindow::exchangeItemInfoBtnSelectorHandler)); 
	switch (pItemInfoData->rewardItemType)
	{
	case  kDT_AWARD_OBJECT:
		{     
			dd->ChangeObject(pItemInfoData->rewardQuality,pItemInfoData->rewardIconID,-1);
			dd->setEnabled(true);
			break;
		}
	case   kDT_AWARD_MONEY:
		{    
			dd->ChangeObject(_GOLD_QUALITY_RESID_,_GOLD_ICON_RESID_,-1);
			dd->setEnabled(false);
			break;
		}
	case  kDT_AWARD_EXP:
		{
			dd->ChangeObject(_EXP_QUALITY_RESID_,_EXP_ICON_RESID_,-1);
			dd->setEnabled(false);
			break;
		}
	case  kDT_AWARD_DIAMOND:
		{
			dd->ChangeObject(_DIAMOND_QUALITY_RESID_,_DIAMOND_ICON_RESID_,-1);
			dd->setEnabled(false);
			break;
		}
	case kDT_AWARD_PRESTIGE:
		{
			dd->ChangeObject(_PREGIST_QUALITY_RESID_,_PREGIST_ICON_RESID_,-1);
			dd->setEnabled(false);
			break;
		}
	case kDT_AWARD_POWER:
		{
			dd->ChangeObject(_POWER_QUALITY_RESID_,_POWER_ICON_RESID_,-1);
			dd->setEnabled(false);
			break;
		}
	default:
		break;
	}  
	NFC_setLabelStringInt(labelIndex,pCell,pItemInfoData->rewardItemCount,true);  
}