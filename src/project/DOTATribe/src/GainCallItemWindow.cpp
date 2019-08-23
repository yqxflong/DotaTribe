//Name : GainCallItemWindow
//Function : 获得召唤物品窗口
//Author : lvyunlong
//Date: 20140522

#include "../include/GainCallItemWindow.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/NFAnimationController.h"
#include  "../include/RoleHeroSkinsDataHandler.h"
#include "../include/PopWindowManager.h"

USING_NS_CC;


GainCallItemWindow::GainCallItemWindow()
:m_pRoot(NULL),
m_pGainData(NULL)
{
	m_WindowType   = _TYPED_WINDOW_GAINCALLITEMWINDOW_;
	m_bModelWindow = true;
}

GainCallItemWindow::~GainCallItemWindow()
{

}

bool GainCallItemWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_GAINCALLITEMWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_GAINCALLITEMWINDOW_, true);
	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_HERO_NEW);
	return IWindow::Init();
}
bool GainCallItemWindow::Load()
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

void GainCallItemWindow::Tick()
{
	IWindow::Tick();
}

void GainCallItemWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	IWindow::Destroy();
}

void GainCallItemWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_GAINCALLITEMWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_GAINCALLITEMWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}

void GainCallItemWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

void GainCallItemWindow::ShowWindow(){
	Show(true);
}

//显示弹窗
void GainCallItemWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
//弹窗已经隐藏
void GainCallItemWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void  GainCallItemWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void GainCallItemWindow::_initLayout()
{
	m_pRoot = m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	//获得当前显示英雄信息
	m_pGainData = HEROSUMMONCONTROLDATAHANDLER->m_pCurGainData;
	_initControl();
	_setInfoData();
	CPriorityLayerColor* p = (CPriorityLayerColor*)m_pRoot->getChildByTag(udPRIORITY);
	p->setDelegate(this);
}

void GainCallItemWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGAINCALLITEMWINDOW,m_pRoot);
}

void GainCallItemWindow::_setInfoData()
{

	DTAwardBoard* dd=(DTAwardBoard*)m_pRoot->getChildByTag(udDTAWARDBOARD);

	switch (m_pGainData->m_RewardData.rewardItemType)
	{
	case  kDT_AWARD_OBJECT:
		{     
			dd->ChangeObject(m_pGainData->m_RewardData.rewardQuality,m_pGainData->m_RewardData.rewardIconID,m_pGainData->m_RewardData.rewardItemCount);
			dd->setEnabled(true);
			if(m_pGainData->m_RewardData.rewardCatagory == kBAGSKIN)
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
			dd->ChangeObject(quality,_GOLD_ICON_RESID_,m_pGainData->m_RewardData.rewardItemCount);
			dd->setEnabled(true);

		}
		break;
	case  kDT_AWARD_EXP:
		{
			int quality=_EXP_QUALITY_RESID_;
			dd->ChangeObject(quality,_EXP_ICON_RESID_,m_pGainData->m_RewardData.rewardItemCount);
			dd->setEnabled(true);

		}
		break;
	case  kDT_AWARD_DIAMOND:
		{
			int quality=_DIAMOND_QUALITY_RESID_;
			dd->ChangeObject(quality,_DIAMOND_ICON_RESID_,m_pGainData->m_RewardData.rewardItemCount);
			dd->setEnabled(true);

		}
		break;
	case kDT_AWARD_PRESTIGE:
		{
			int quality=_PREGIST_QUALITY_RESID_;
			dd->ChangeObject(quality,_PREGIST_ICON_RESID_,m_pGainData->m_RewardData.rewardItemCount);
			dd->setEnabled(true);	
		}
		break;
	case kDT_AWARD_POWER:
		{
			int quality=_POWER_QUALITY_RESID_;
			dd->ChangeObject(quality,_POWER_ICON_RESID_,m_pGainData->m_RewardData.rewardItemCount);
			dd->setEnabled(true);
		}
		break;
	default:
		break;
	}
	NFC_setLabelString(udNAME,m_pRoot,m_pGainData->m_RewardData.rewardRewardName,true);
}

/*
	CPriorityLayerColor Delegate
*/
void GainCallItemWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{	
	PushEvent(_TYPED_EVENT_HIDE_GAINCALLITEMWINDOW_);
}
