//Name:FirstRechGiftWindow
//Author: lvyunlong
//Func: Activity of first recharge get gift
//Maintainer:lvyunlong	


#include "../include/FirstRechGiftWindow.h"
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

FirstRechGiftWindow::FirstRechGiftWindow()
:m_pTableAttachment(NULL),
m_CurWindowActiviId(0)
{
	m_WindowType   = _TYPED_WINDOW_FIRSTRECHWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

FirstRechGiftWindow::~FirstRechGiftWindow()
{

}
	

void FirstRechGiftWindow::_initLayout()
{
	_initControl();
	_initCell();
	_mapBtn();
}

void FirstRechGiftWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kFIRSTRECHWINDOW,m_pRootNode);
}

void FirstRechGiftWindow::_initCell()
{
	CCNode* cell = NFC_getNode(udTABLECELL,m_pRootNode);
	m_szCellGift = cell->getContentSize();
}

void FirstRechGiftWindow::_mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
	dd->setIDX(idx);
	dd->setTarget(this,menu_selector(FirstRechGiftWindow::On_CheckItem_Click));
}

void FirstRechGiftWindow::_mapBtn()
{
	CCMenu* menu=(CCMenu*)NFC_getNode(udQUICKRECHBTN,m_pRootNode);
	CMenuItemSprite *item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(udQUICKRECHBTN);
	item->setTarget(this, menu_selector(FirstRechGiftWindow::On_Click_Quick_Enevnt));


	menu=(CCMenu*)NFC_getNode(udGETBTN,m_pRootNode);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(udGETBTN);
	item->setTarget(this, menu_selector(FirstRechGiftWindow::On_Click_Get_Enevnt));

	if (ROLEINFODATAHANDLER->m_pRIData->accumuRechNum <= 0)
	{
		NFC_showNode(udGETEFFECT,m_pRootNode,false);
	}
}

bool  FirstRechGiftWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_FIRSTRECHGIFTWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_FIRSTRECHGIFTWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_FIRSTRECHGIFTWINDOW_, true);
	return IWindow::Init();
}

bool  FirstRechGiftWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		_setTableView(); //设置TableView

		return true;
	} 
	while (false);

	return false;
}

void  FirstRechGiftWindow::Tick()
{
	IWindow::Tick();
}

void  FirstRechGiftWindow::Destroy()
{
	m_pTableAttachment = NULL;
	if (m_pRootNode)
	{
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}
	
	IWindow::Destroy();
}

void  FirstRechGiftWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_FIRSTRECHGIFTWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_FIRSTRECHGIFTWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_FIRSTRECHGIFTWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
}

void   FirstRechGiftWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		m_CurWindowActiviId = atoi(paramList.begin()->c_str());
		FIRSTRECHDATAHANDLER->setFirstRechActiviId(m_CurWindowActiviId);
	}
	Show(true);
}

void  FirstRechGiftWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void  FirstRechGiftWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_refreshTableView(m_pTableAttachment);
	NFC_showCommunicationWating(false);
}

void FirstRechGiftWindow::_setTableView()
{
	if (m_pTableAttachment)
		m_pTableAttachment->removeAllChildrenWithCleanup(true);

	m_pTableAttachment = (CCTableView*)m_pRootNode->getChildByTag(udTABLE);
	m_pTableAttachment->setDataSource(this);
	m_pTableAttachment->setDelegate(this);
	m_pTableAttachment->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	m_pTableAttachment->setTouchEnabled(true);
	m_pTableAttachment->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}

cocos2d::CCSize FirstRechGiftWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCellGift;
}

cocos2d::extension::CCTableViewCell* FirstRechGiftWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){

	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(idx,cell);

	return cell;
}

void FirstRechGiftWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kFIRSTRECHCELL,cell);
}

void FirstRechGiftWindow::_setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	RechGiftDataObject *data = FIRSTRECHDATAHANDLER->m_RechList[idx];
	assert(data != NULL);
	char buff[64]={0};
	int count = data->count_;
	if(data->type_ == kDT_AWARD_DIAMOND)
	{
		//NFC_setLabelString(udINFOCELLNUM,cell,SysLangDataManager::get_instance2()->GetSysLangById(6072));
	}
	else
	{
		sprintf(buff,"%d",count);
		NFC_setLabelString(udINFOCELLNUM,cell,buff);
	}
	_mapCellItemBtn(idx,cell);
	//设置当前附件图标
	_setAttachmenticon(data,cell);
}

void FirstRechGiftWindow::_setAttachmenticon(RechGiftDataObject *data,cocos2d::extension::CCTableViewCell* cell)
{
	DTAwardBoard* award=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
	switch(data->type_)
	{
	case kDT_AWARD_OBJECT:
		{
			award->ChangeObject(data->quality_,data->iconId_);
			award->setEnabled(true);
			if(data->catogory == kBAGSKIN){
				award->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
			}else{
				award->setContentScale(1.0f);
			}
		}
		break;
	case kDT_AWARD_MONEY:
		{
			int quality=_GOLD_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD); 
			award->ChangeObject(quality,iconID);
			award->setEnabled(false);
		}
		break;
	case kDT_AWARD_EXP:	
		{
			int quality=_EXP_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP); 
			award->ChangeObject(quality,iconID);
			award->setEnabled(false);
		}
		break;
	case kDT_AWARD_DIAMOND:
		{
			int quality=_DIAMOND_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND); 
			award->ChangeObject(quality,iconID);
			award->setEnabled(false);
		}
		break;
	case kDT_AWARD_PRESTIGE:
		{
			int quality=_PREGIST_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE); 
			award->ChangeObject(quality,iconID);
			award->setEnabled(false);
		}
		break;
	case kDT_AWARD_POWER:
		{
			int quality=_POWER_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG); 
			award->ChangeObject(quality,iconID);
			award->setEnabled(false);
		}
		break;
	default:
		break;
	}
}

unsigned int FirstRechGiftWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return FIRSTRECHDATAHANDLER->m_RechList.size();
}

void FirstRechGiftWindow::On_Click_Quick_Enevnt(cocos2d::CCObject* pSender)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_ACTIVITYWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_RECHARGEWINDOW_);
}

void FirstRechGiftWindow::On_Click_Get_Enevnt(cocos2d::CCObject* pSender)
{
	//int i = 0;
	FIRSTRECHDATAHANDLER->ToServerGetGift();
}

void FirstRechGiftWindow::On_CheckItem_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;	
	int index = cc->getIDX();
	RechGiftDataObject* data = FIRSTRECHDATAHANDLER->m_RechList[index];
	if (data == NULL)
		return;

	if (data->type_ == kEFFECT_TYPE_OBJECT)
	{
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(data->templateId_, _TYPED_WINDOW_FIRSTRECHWINDOW_);
	}
}