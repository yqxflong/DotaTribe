//Name : TenCallWindow
//Function : 十连抽召唤窗口
//Author : lvyunlong
//Date: 20140522

#include "../include/TenCallWindow.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/NFAnimationController.h"
#include  "../include/RoleHeroSkinsDataHandler.h"
#include "../include/PopWindowManager.h"

USING_NS_CC;


TenCallWindow::TenCallWindow()
:m_pRoot(NULL),
m_pLayer(NULL)
{
	m_WindowType   = _TYPED_WINDOW_TENCALLWINDOW;
	m_bModelWindow = true;

}

TenCallWindow::~TenCallWindow()
{

}


bool TenCallWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_TENCALLWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_TENCALLWINDOW_, true);
	
	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_HERO_NEW);
	return IWindow::Init();
}
bool TenCallWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		return true;
	} 
	while (false);

	return false;
}

void TenCallWindow::Tick()
{
	IWindow::Tick();
}

void TenCallWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	IWindow::Destroy();
}

//显示弹窗
void TenCallWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
//弹窗已经隐藏
void TenCallWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void TenCallWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_TENCALLWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_TENCALLWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}

void TenCallWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

void TenCallWindow::ShowWindow(){
	Show(true);
}

void  TenCallWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void TenCallWindow::_initLayout()
{
	m_pRoot = m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pLayer = cocos2d::CCLayer::create();
	//获得当前显示英雄信息
	m_pRoot->addChild(m_pLayer,1);
	_initControl();
	_setinfodata();
	_mapBtn();

	NFC_Action_scaleIn(m_pLayer,CONST_KEY_MULTIREWARD_POP_DURING_2,CONST_KEY_MULTIREWARD_POP_DURING_3,CONST_KEY_MULTIREWARD_POP_DURING_4);

	CCNode* gray=NFC_getNode(TEN_PRIORITY,m_pLayer);
	gray->removeFromParentAndCleanup(false);
	m_pRoot->addChild(gray,0);
}

void TenCallWindow::_mapBtn()
{
	CCMenu* menu =(CCMenu*)m_pLayer->getChildByTag(udHEROLISTBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udHEROLISTBTN);
	cc->setTarget(this,menu_selector(TenCallWindow::On_Click_Summon_Event));
}

void TenCallWindow::On_Click_Summon_Event(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_TENCALLWINDOW_);
}

void TenCallWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTENCALLWINDOW,m_pLayer);
}

void TenCallWindow::_setinfodata()
{
	std::vector<TenCallGainData>::iterator itbegin = HEROSUMMONCONTROLDATAHANDLER->m_pTenCallList.begin();	
	std::vector<TenCallGainData>::iterator itend = HEROSUMMONCONTROLDATAHANDLER->m_pTenCallList.end();
	int index = 0;
	std::string sysname="";
	for (itbegin;itbegin != itend;itbegin++)
	{
		if ((*itbegin).gaintype_ == 0)
		{
			NFC_setNodeVisable(TEN_NEWICON + index*8,m_pLayer,true);
			_setHeroType(TEN_HEROTYPE + index*8,(*itbegin).herotype,m_pLayer);
			NFC_setDTHeroIcon(TEN_DTHEROICON + index*8,m_pLayer,(*itbegin).heroiconid,true);
			NFC_setDTHeroQualiy(TEN_DTHEROICON + index*8,m_pLayer,(*itbegin).quality);
			sysname = (*itbegin).heroName;
			CCardsStarProgress * pStar=(CCardsStarProgress *)m_pLayer->getChildByTag(TEN_START + index*8);
			pStar->SetCurcount((*itbegin).quality+1);
			pStar->setVisible(true);
		}
		else if ((*itbegin).gaintype_ == 1)
		{
			NFC_setNodeVisable(TEN_HAVEICON +index*8,m_pLayer,true);
			_setHeroType(TEN_HEROTYPE + index*8,(*itbegin).herotype,m_pLayer);
			NFC_setDTHeroIcon(TEN_DTHEROICON + index*8,m_pLayer,(*itbegin).heroiconid,true);
			NFC_setDTHeroQualiy(TEN_DTHEROICON + index*8,m_pLayer,(*itbegin).quality);
			sysname = (*itbegin).heroName;
			CCardsStarProgress * pStar=(CCardsStarProgress *)m_pLayer->getChildByTag(TEN_START + index*8);
			pStar->SetCurcount((*itbegin).quality+1);
			pStar->setVisible(true);
		}
		else if ((*itbegin).gaintype_ == 2)
		{
			DTAwardBoard* dd=(DTAwardBoard*)m_pLayer->getChildByTag(TEN_DTAWARD + index*8);

			switch ((*itbegin).m_RewardData.rewardItemType)
			{
			case  kDT_AWARD_OBJECT:
				{     
					dd->ChangeObject((*itbegin).m_RewardData.rewardQuality,(*itbegin).m_RewardData.rewardIconID,(*itbegin).m_RewardData.rewardItemCount);
					dd->setEnabled(true);
					if((*itbegin).m_RewardData.rewardCatagory == kBAGSKIN)
					{
						dd->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
					}
					else if ((*itbegin).m_RewardData.rewardCatagory == kBAGEQUIP)
					{
						dd->setContentScale(1);
						CCardsStarProgress * pStar=(CCardsStarProgress *)m_pLayer->getChildByTag(TEN_START + index*8);
						pStar->SetCurcount((*itbegin).m_RewardData.rewardQuality+1);
						pStar->setVisible(true);
						
					}
					else if ((*itbegin).m_RewardData.rewardCatagory == kBAGOBJECT)
					{
						dd->setContentScale(1);
					}

				}
				break;
			case   kDT_AWARD_MONEY:
				{    
					int quality=_GOLD_QUALITY_RESID_;
					dd->ChangeObject(quality,_GOLD_ICON_RESID_,(*itbegin).m_RewardData.rewardItemCount);
					dd->setEnabled(true);

				}
				break;
			case  kDT_AWARD_EXP:
				{
					int quality=_EXP_QUALITY_RESID_;
					dd->ChangeObject(quality,_EXP_ICON_RESID_,(*itbegin).m_RewardData.rewardItemCount);
					dd->setEnabled(true);

				}
				break;
			case  kDT_AWARD_DIAMOND:
				{
					int quality=_DIAMOND_QUALITY_RESID_;
					dd->ChangeObject(quality,_DIAMOND_ICON_RESID_,(*itbegin).m_RewardData.rewardItemCount);
					dd->setEnabled(true);

				}
				break;
			case kDT_AWARD_PRESTIGE:
				{
					int quality=_PREGIST_QUALITY_RESID_;
					dd->ChangeObject(quality,_PREGIST_ICON_RESID_,(*itbegin).m_RewardData.rewardItemCount);
					dd->setEnabled(true);	
				}
				break;
			case kDT_AWARD_POWER:
				{
					int quality=_POWER_QUALITY_RESID_;
					dd->ChangeObject(quality,_POWER_ICON_RESID_,(*itbegin).m_RewardData.rewardItemCount);
					dd->setEnabled(true);
				}
				break;
			default:
				break;
			}
			sysname = (*itbegin).m_RewardData.rewardRewardName;
		}
		NFC_setLabelString(TEN_NAMETTF + index*8,m_pLayer,sysname,true);
		index++;
	}
}


void TenCallWindow::_setHeroType(int index,int type,cocos2d::CCNode* node)
{
	int typeResouleID = 0;
	if (type == HERO_POWER)
	{
		typeResouleID = ClientConstDataManager::get_instance2()->getValueByKey(POWER_ICON);
	}
	else if (type == HERO_QUICK)
	{
		typeResouleID = ClientConstDataManager::get_instance2()->getValueByKey(QUICK_ICON);
	}
	else if (type == HERO_INTELIGENCE)
	{
		typeResouleID = ClientConstDataManager::get_instance2()->getValueByKey(INTELIGENCE_ICON);
	}

	std::string strpath = ResourceIDDataManager::get_instance2()->getDataByID(typeResouleID).c_str();
	NFC_setPicForCCSprite(index,node,strpath.c_str(),true);
}

void TenCallWindow::_setStarRank()
{
	//NFC_setCardsStarLevel(TEN_START,m_pLayer,m_pGainData->quality_+1);
}



