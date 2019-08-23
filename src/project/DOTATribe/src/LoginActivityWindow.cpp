//Name: LoginActivityWindow
//Author: lvyunlong
//Func: Activity of Everyday Login
//Maintainer:lvyunlong


#include "../include/LoginActivityWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/EffectDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/ActivityDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/NFAnimationController.h"

const  int   LoginmaxCellCount = 4;

LoginActivityWindow::LoginActivityWindow()
	:m_pTableAttachment(NULL),
	m_CurWindowActiviId(0)
{
	m_WindowType   = _TYPED_WINDOW_ACTIVITYLOGIN_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

LoginActivityWindow::~LoginActivityWindow()
{

}


void LoginActivityWindow::_initLayout()
{
	_initControl();
	_initCell();
}

void LoginActivityWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLOGINACTIVITYWINDOW,m_pRootNode);
}

void LoginActivityWindow::_initCell()
{
	CCNode* cell = NFC_getNode(udTABLECELL,m_pRootNode);
	m_szCellGift = cell->getContentSize();
}


bool  LoginActivityWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LOGINACTIVITYWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LOGINACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LOGINACTIVITYWINDOW_, true);
	return IWindow::Init();
}

bool  LoginActivityWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		//_initData();
		_initLayout();
		_setTableView(); //设置TableView

		return true;
	} 
	while (false);

	return false;
}

void  LoginActivityWindow::Tick()
{
	IWindow::Tick();
}

void  LoginActivityWindow::Destroy()
{
	m_pTableAttachment = NULL;
	if (m_pRootNode)
	{
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}

	IWindow::Destroy();
}

void  LoginActivityWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LOGINACTIVITYWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LOGINACTIVITYWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LOGINACTIVITYWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
}

void   LoginActivityWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		m_CurWindowActiviId = atoi(paramList.begin()->c_str());
		LOGINREWARDDATAHANDLER->setLoginRewardActiviId(m_CurWindowActiviId);
	}
	Show(true);
}

void  LoginActivityWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void  LoginActivityWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_refreshTableView(m_pTableAttachment);
	NFC_showCommunicationWating(false);
}

void LoginActivityWindow::_setTableView()
{
	if (m_pTableAttachment)
		m_pTableAttachment->removeAllChildrenWithCleanup(true);

	m_pTableAttachment = (CCTableView*)m_pRootNode->getChildByTag(udTABLE);
	m_pTableAttachment->setDataSource(this);
	m_pTableAttachment->setDelegate(this);
	m_pTableAttachment->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTableAttachment->setTouchEnabled(true);
	m_pTableAttachment->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}

cocos2d::CCSize LoginActivityWindow::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	if (idx ==0)
	{
		return CCSizeMake(m_szCellGift.width,m_szCellGift.height+20.0f);
	}
	else
	{
		return m_szCellGift;
	}
}


cocos2d::extension::CCTableViewCell* LoginActivityWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){

	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(idx,cell);

	return cell;
}

void LoginActivityWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLOGINACTIVITYCELL,cell);
}

void LoginActivityWindow::_setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	unsigned int cellindex = idx;
	cell->removeAllChildrenWithCleanup(true);
	_createTableCell(cell);
	NFC_setNodeVisable(udCELLREWARDOBJ1,cell,false);
	NFC_setNodeVisable(udCELLREWARDOBJ5,cell,false);
	NFC_setNodeVisable(udGETBTNTTFNODE,cell,false);
	NFC_setNodeVisable(udTODAYTTFNODE,cell,false);
	if (cellindex == 0)
	{
		NFC_showNode(udTIMETTF,cell,false);
		NFC_showNode(udLOGINREWARDTTF,cell,false);
		MaskNode* nodesprite = (MaskNode*)NFC_getNode(udTODAYNODE,cell);
		NFC_createSpriteByViewData(cell,nodesprite->GetViewData());
		NFC_setNodeVisable(udTODAYTTFNODE,cell,true);
		NFC_setNodeVisable(udGETBTNTTFNODE,cell,true);
		MaskNode* nodemenu = (MaskNode*)NFC_getNode(udGETBTNNODE,cell);
		CMenuItemSprite* pmenuSprite = NFC_createMenuItemByViewData(cell,nodemenu->GetViewData());
		pmenuSprite->setTarget(this,menu_selector(LoginActivityWindow::On_Click_Get_Enevnt));
		//MaskNode* nodettf = (MaskNode*)NFC_getNode(udGETBTNTTFNODE,cell);
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(udGETBTNTTFNODE,cell);
		if (LOGINREWARDDATAHANDLER->m_Hasreward)
		{
			ttf->setString(SysLangDataManager::get_instance2()->GetSysLangById(6060).c_str());
			pmenuSprite->setEnabled(false);
		}
		else
		{
			ttf->setString(SysLangDataManager::get_instance2()->GetSysLangById(6047).c_str());
			pmenuSprite->setEnabled(true);
			MaskNode* nodeeffect = (MaskNode*)NFC_getNode(udGETEFFECTNODE,cell);
			CCSprite* pEff = NFC_getLoopFrameEffect(nodeeffect->GetViewData().colorR_);
			nodeeffect->addChild(pEff);
		}
	}
	else
	{	
		char buff[256]={0};
		if (cellindex == 1)
		{
			sprintf(buff,"%s",SysLangDataManager::get_instance2()->GetSysLangById(6062).c_str());
		}
		else
		{
			std::string str = _to_event_param_(cellindex+1);
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6061).c_str(),str.c_str());
		}
		NFC_setLabelString(udTIMETTF,cell,buff);
	}
	int rewardIndexArrTemp1[] = {udCELLREWARDOBJ1,udCELLREWARDOBJ2,udCELLREWARDOBJ3,udCELLREWARDOBJ4};
	int rewardIndexArrTemp2[] = {udCELLREWARDOBJ2,udCELLREWARDOBJ3,udCELLREWARDOBJ4,udCELLREWARDOBJ5};
	int rewardIndexArr[4]={0};
	if (cellindex == 0)
	{
		NFC_setNodeVisable(udCELLREWARDOBJ1,cell,true);
		memcpy(rewardIndexArr,rewardIndexArrTemp1,sizeof(rewardIndexArrTemp1));
	}
	else
	{
		NFC_setNodeVisable(udCELLREWARDOBJ5,cell,true);
		memcpy(rewardIndexArr,rewardIndexArrTemp2,sizeof(rewardIndexArrTemp2));
	}
	unsigned int rewardSize = LOGINREWARDDATAHANDLER->m_RewardList.at(cellindex)->m_RewardVec.size();
	for (int index=0;index<LoginmaxCellCount;index++)
	{
		if (index<rewardSize)
		{
			
			PRewardItemNode pRewardItemNode = LOGINREWARDDATAHANDLER->m_RewardList.at(cellindex)->m_RewardVec.at(index);
			if(pRewardItemNode)
			{
				//绑定事件 
				int key=rewardIndexArr[index];
				DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(key);
				//NFC_bindMenuSpriteAttachParams(rewardIndexArr[index],cell,cellindex,index,this,menu_selector(LoginActivityWindow::On_Click_RewardInfo));
				if (cellindex == 8)
				{
					int i =0;
				}
				dd->setIDX(cellindex);
				dd->setAttachParam(cellindex,index);
				dd->setTarget(this,menu_selector(LoginActivityWindow::On_Click_RewardInfo));

				switch (pRewardItemNode->rewardItemType)
				{
				case  kDT_AWARD_OBJECT:
					{     
						dd->ChangeObject(pRewardItemNode->rewardQuality,pRewardItemNode->rewardIconID,pRewardItemNode->rewardItemCount);
						dd->setEnabled(true);
						if(pRewardItemNode->rewardCatagory == kBAGSKIN)
						{
							dd->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
						}
						else
						{
							dd->setContentScale(1);
						}
						
					}
					break;
				case   kDT_AWARD_MONEY:
					{    
						int quality=_GOLD_QUALITY_RESID_;
						dd->ChangeObject(quality,_GOLD_ICON_RESID_,pRewardItemNode->rewardItemCount);
						dd->setEnabled(true);
						
					}
					break;
				case  kDT_AWARD_EXP:
					{
						int quality=_EXP_QUALITY_RESID_;
						dd->ChangeObject(quality,_EXP_ICON_RESID_,pRewardItemNode->rewardItemCount);
						dd->setEnabled(true);
						
					}
					break;
				case  kDT_AWARD_DIAMOND:
					{
						int quality=_DIAMOND_QUALITY_RESID_;
						dd->ChangeObject(quality,_DIAMOND_ICON_RESID_,pRewardItemNode->rewardItemCount);
						dd->setEnabled(true);
						
					}
					break;
				case kDT_AWARD_PRESTIGE:
					{
						int quality=_PREGIST_QUALITY_RESID_;
						dd->ChangeObject(quality,_PREGIST_ICON_RESID_,pRewardItemNode->rewardItemCount);
						dd->setEnabled(true);	
					}
					break;
				case kDT_AWARD_POWER:
					{
						int quality=_POWER_QUALITY_RESID_;
						dd->ChangeObject(quality,_POWER_ICON_RESID_,pRewardItemNode->rewardItemCount);
						dd->setEnabled(true);
					}
					break;
				default:
					break;
				}	
			}
		}
		else
		{
			NFC_setNodeVisable(rewardIndexArr[index],cell,false);
		}
	}
}


unsigned int LoginActivityWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return LOGINREWARDDATAHANDLER->m_RewardList.size();
}

void LoginActivityWindow::On_Click_Get_Enevnt(cocos2d::CCObject* pSender)
{
	LOGINREWARDDATAHANDLER->ToServerGetReward();
}

void LoginActivityWindow::On_Click_RewardInfo(cocos2d::CCObject* pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if (pMenuItemSprite)
	{
		int cellIndex = pMenuItemSprite->getAttachData1();
		int cellInterIndex = pMenuItemSprite->getAttachData2();	
		PRewardItemNode pRewardItemNode = LOGINREWARDDATAHANDLER->m_RewardList.at(cellIndex)->m_RewardVec.at(cellInterIndex);
		if(pRewardItemNode&&pRewardItemNode->rewardItemType == 0)
		{ 
			NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pRewardItemNode->rewardTemplateID, _TYPED_WINDOW_ACTIVITYLOGIN_);
		}
	}
}