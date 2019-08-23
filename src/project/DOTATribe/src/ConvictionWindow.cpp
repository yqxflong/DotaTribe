// Name :		ConvictionWindow.h
// Function:	信仰窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/ConvictionWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/HeroTechnologyLevelUpPacket.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/IDStringDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/RestingTechnologyPointPacket.h"
#include "../include/GuideSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "cocos-ext.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>
using  namespace  cocos2d;

#define OnePageConvictionNum 8
#define INFO_LINE_1 357
#define INFO_LINE_2 358
#define INFO_LINE_3 359
ConvictionWindow::ConvictionWindow()
{
	m_WindowType = _TYPED_WINDOW_CONVICTION_;
	m_Cur_Page = 1;
	m_Total_Page = 0;
	m_Select_Index = -1;
	m_lastSelect= NULL;
	m_RestingButton = NULL;
}

ConvictionWindow::~ConvictionWindow()
{

}

bool ConvictionWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_CONVICTIONWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_CONVICTIONWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_CONVICTIONWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_UPDATE_PRAY_COST,true);
	return IWindow::Init();
}

bool ConvictionWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		InitLayer();
		_checkNewFunc();
		return true;
	} 
	while (false);

	return false;
}
	/*
		检查新功能开启
	*/
void ConvictionWindow::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH)){
		//======显示帮助界面======
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,_to_event_param_(UIViewDataManager::kHEROTECHNOLOGY_HELP_));
		NFC_setNodeVisable(Conviction_PRAY_ARROW,m_pRootNode,true);
		//=======结束新功能开启=========
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH);
	}
}

void ConvictionWindow::Tick()
{
	IWindow::Tick();
}

void ConvictionWindow::Destroy()
{
	m_Cur_Page = 1;
	m_Total_Page = 0;
	m_Select_Index = -1;
	m_RestingButton = NULL;
	m_lastSelect= NULL;
	IWindow::Destroy();
}

void ConvictionWindow::InitLayer()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCONVICTIONWINDOW,m_pRootNode);
	_uckInitButton();
	_uckUpdataPageInfo();
	_uckUpdataConvictionInfo();
	_uckUpdataConvictionPoint();
	_uckUpdataRestingButton();
	_uckUpdataConvictionIcon();
	_uckSetSelect((CPriorityLayerColor*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_TOUCH_LAYER));
}

void ConvictionWindow::touchEvent( CPriorityLayerColor* pLayerColor )
{
	_uckSetSelect(pLayerColor);
}

void ConvictionWindow::OnEventHandler( int iEventType, std::list<std::string>& paramList )
{
	if (iEventType == _TYPED_EVENT_SHOW_CONVICTIONWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_CONVICTIONWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_CONVICTIONWINDOW_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_PRAY_COST)
	{
		_uckUpdatePrayCost();
		_uckUpdataPageInfo();
		_uckUpdataConvictionInfo();
		_uckUpdataConvictionPoint();
		_uckUpdataRestingButton();
		_uckUpdataConvictionIcon();
	}

}

void ConvictionWindow::OnShowWindowEventHandler( std::list<std::string>& paramList )
{
	if (m_pRootNode->isVisible())
	{
		_uckUpdataPageInfo();
		_uckUpdataConvictionInfo();
		_uckUpdataConvictionPoint();
		_uckUpdataRestingButton();
		_uckUpdataConvictionIcon();
	}
	else
		Show(true);

	_uckSendGetTechnologyPointPacket();



}

void ConvictionWindow::OnUpdateUITextEventHandler( std::list<std::string>& paramList )
{
	_uckUpdataPageInfo();
	_uckUpdataConvictionInfo();
	_uckUpdataConvictionPoint();
	_uckUpdataRestingButton();
	_uckUpdataConvictionIcon();
	NFC_showCommunicationWating(false);
}

void ConvictionWindow::On_Click_Resetting( cocos2d::CCObject* pSender )
{
	_uckSendResettingPacket();	
}

void ConvictionWindow::On_Click_LvUp( cocos2d::CCObject* pSender )
{
	_uckSendLvUpPacket();
}

void ConvictionWindow::On_Click_Pray( cocos2d::CCObject* pSender )
{
	_uckSendPrayPacket();
}

void ConvictionWindow::On_Click_Page( cocos2d::CCObject* pSender )
{
	_uckSetPage((CMenuItemSprite*)pSender);
}

void ConvictionWindow::_uckUpdataConvictionInfo()
{
	if (m_Select_Index == -1)
	{
		_uckHideConvictionInfo();
	}
	else
	{
		_uckSetConvictionInfo();
		_uckCheckConvictionIsMaxLv();
	}

}

void ConvictionWindow::_uckUpdataPageInfo()
{
	if (m_Total_Page == 0)
	{
		if (HeroTechnologyDataHandler::get_instance2()->count%OnePageConvictionNum != 0 || HeroTechnologyDataHandler::get_instance2()->count == 0)
			m_Total_Page = HeroTechnologyDataHandler::get_instance2()->count/OnePageConvictionNum + 1;
		else
			m_Total_Page = HeroTechnologyDataHandler::get_instance2()->count/OnePageConvictionNum;
	}

	CCLabelTTF* pPage = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_PAGE_LABEL);
	char _pPage[128] ="";
	sprintf(_pPage,"%d/%d",m_Cur_Page,m_Total_Page);
	pPage->setString(_pPage);

}

void ConvictionWindow::_uckUpdataConvictionPoint()
{
	CCLabelTTF* pPoint = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_POINT);
	char _Point[128] ="";
	sprintf(_Point,"%d",HeroTechnologyDataHandler::get_instance2()->score);
	pPoint->setString(_Point);
}

void ConvictionWindow::_uckUpdataRestingButton()
{
	for (int i=0;i<HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList.size();i++)
	{
		if (HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[i]->level !=0)
		{
			m_RestingButton->setEnabled(true);
			return;
		}
	}
	m_RestingButton->setEnabled(false);

}

void ConvictionWindow::_uckUpdatePrayCost()
{
	_uckCheckPrayFreeTimes();
	_uckSetPrayCostPoint();
	_uckSetPrayButton();
	NFC_showCommunicationWating(false);
}

void ConvictionWindow::_uckUpdataConvictionIcon()
{
	for (int i=0;i<OnePageConvictionNum;i++)
	{
		int index = i+(m_Cur_Page-1)*(Conviction_IMAGE_2_BG-Conviction_IMAGE_1_BG);
		if (index >= HeroTechnologyDataHandler::get_instance2()->count)
		{
			_uckHideTechnologyCell(i);
			continue;
		}
		_uckSetTechnologyCell(i,index);

	}
}

void ConvictionWindow::_uckSetSelect( CPriorityLayerColor* pLayerColor )
{
	CCSprite* cur_select = (CCSprite*)m_pRootNode->getChildByTag(pLayerColor->getTag()+1);
	if (m_lastSelect && m_lastSelect != cur_select)
	{

		m_lastSelect->setVisible(false);
		m_lastSelect = cur_select;
		m_lastSelect->setVisible(true);
		m_Select_Index = (pLayerColor->getTag()-Conviction_IMAGE_1_TOUCH_LAYER)/(Conviction_IMAGE_2_BG-Conviction_IMAGE_1_BG)+(m_Cur_Page-1)*OnePageConvictionNum;
		_uckUpdataConvictionInfo();

	}
	else if (m_lastSelect != cur_select)
	{
		m_lastSelect = cur_select;
		m_lastSelect->setVisible(true);
		m_Select_Index = (pLayerColor->getTag()-Conviction_IMAGE_1_TOUCH_LAYER)/(Conviction_IMAGE_2_BG-Conviction_IMAGE_1_BG)+(m_Cur_Page-1)*OnePageConvictionNum;
		_uckUpdataConvictionInfo();
	}
}

void ConvictionWindow::_uckInitButton()
{
	CCMenu* ptemp = (CCMenu*)m_pRootNode->getChildByTag(Conviction_RESTING_BUTTON);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(ConvictionWindow::On_Click_Resetting));
	m_RestingButton = ptempItem;

	ptemp = (CCMenu*)m_pRootNode->getChildByTag(Conviction_PRAY_BUTTON);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(ConvictionWindow::On_Click_Pray));

	ptemp = (CCMenu*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(ConvictionWindow::On_Click_LvUp));

	ptemp = (CCMenu*)m_pRootNode->getChildByTag(Conviction_ARROW_LEFT);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(ConvictionWindow::On_Click_Page));

	ptemp = (CCMenu*)m_pRootNode->getChildByTag(Conviction_ARROW_RIGHT);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(ConvictionWindow::On_Click_Page));

	int key = Conviction_IMAGE_1_TOUCH_LAYER;
	for (int i=0;i<OnePageConvictionNum;i++)
	{

		CPriorityLayerColor* layer = (CPriorityLayerColor*)m_pRootNode->getChildByTag(key);
		layer->setDelegate(this);
		key += (Conviction_IMAGE_2_BG-Conviction_IMAGE_1_BG);
	}
}

void ConvictionWindow::_uckSendResettingPacket()
{
	C2SRestingTechnologyPointPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void ConvictionWindow::_uckSendLvUpPacket()
{
	if (m_Select_Index != -1 && m_Select_Index<HeroTechnologyDataHandler::get_instance2()->count)
	{
		HeroTechnology* pTechnologyData = HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[m_Select_Index];
		C2SHeroTechnologyLevelUpPacket packet(pTechnologyData->id);
		packet.Send();
		NFC_showCommunicationWating(true);
	}
}

void ConvictionWindow::_uckSendPrayPacket()
{
	//隐藏箭头
	NFC_setNodeVisable(Conviction_PRAY_ARROW,m_pRootNode,false);
	CCSprite* pNode = NFC_getUnLoopFrameEffect(2043);
	pNode->setPosition(ccp(m_pRootNode->getChildByTag(Conviction_PRAY_BUTTON_LABEL)->getPositionX()-4,m_pRootNode->getChildByTag(Conviction_PRAY_BUTTON_LABEL)->getPositionY()+10));
	m_pRootNode->addChild(pNode,10);
	NFC_showCommunicationWating(true);
	C2SAddTechnologyPointPacket crpacket;
	crpacket.Send();
}

void ConvictionWindow::_uckSetPage( CMenuItemSprite* pItem )
{
	if (pItem->getParent()->getTag() == Conviction_ARROW_LEFT)
	{
		if (m_Cur_Page >1)
		{
			m_Cur_Page--;
			m_Select_Index = -1;
			if (m_lastSelect)
			{
				m_lastSelect->setVisible(false);
				m_lastSelect= NULL;
			}
			_uckUpdataPageInfo();
			_uckUpdataConvictionIcon();
			_uckUpdataConvictionInfo();
		}
	}
	else
	{
		if (m_Cur_Page < m_Total_Page)
		{
			m_Cur_Page++;
			m_Select_Index = -1;
			if (m_lastSelect)
			{
				m_lastSelect->setVisible(false);
				m_lastSelect= NULL;
			}
			_uckUpdataPageInfo();
			_uckUpdataConvictionIcon();
			_uckUpdataConvictionInfo();
		}
	}
}

void ConvictionWindow::_uckHideConvictionInfo()
{
	CCLabelTTF* Line1 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_1);
	Line1->setVisible(false);
	CCLabelTTF* Line2 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_2);
	Line2->setVisible(false);
	CCLabelTTF* Line3 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_3);
	Line3->setVisible(false);

	CCMenu* pButton = (CCMenu*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON);
	pButton->setVisible(false);
	CCLabelTTF* pLabel = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON_LABEL);
	pLabel->setVisible(false);
}

void ConvictionWindow::_uckSetConvictionInfo()
{
	HeroTechnology* pTechnologyData = HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[m_Select_Index];
	CCLabelTTF* Line1 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_1);
	char _line1[128]="";
	sprintf(_line1,SysLangDataManager::get_instance2()->GetSysLangById(INFO_LINE_1).c_str(),pTechnologyData->name.c_str(),pTechnologyData->level);
	Line1->setString(_line1);
	Line1->setVisible(true);

	CCLabelTTF* Line2 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_2);
	char _line2[128]="";
	sprintf(_line2,SysLangDataManager::get_instance2()->GetSysLangById(INFO_LINE_2).c_str(),IDStringDataManager::get_instance2()->GetIDStringByID(3,pTechnologyData->attriType).c_str(),pTechnologyData->nextLevelAddValue);
	Line2->setString(_line2);
	Line2->setVisible(true);

	CCLabelTTF* Line3 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_3);
	char _line3[128]="";
	sprintf(_line3,SysLangDataManager::get_instance2()->GetSysLangById(INFO_LINE_3).c_str(),pTechnologyData->costPoints);
	Line3->setString(_line3);
	Line3->setVisible(true);
}

void ConvictionWindow::_uckCheckConvictionIsMaxLv()
{
	HeroTechnology* pTechnologyData = HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[m_Select_Index];
	if (pTechnologyData->costPoints != -1)
	{
		CCMenu* pButton = (CCMenu*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON);
		if (HeroTechnologyDataHandler::get_instance2()->score >= pTechnologyData->costPoints)
		{
			pButton->setVisible(true);
			CMenuItemSprite* ptempItem = (CMenuItemSprite*)pButton->getChildByTag(0);
			ptempItem->setEnabled(true);
		}
		else
		{
			pButton->setVisible(true);
			CMenuItemSprite* ptempItem = (CMenuItemSprite*)pButton->getChildByTag(0);
			ptempItem->setEnabled(false);
		}

		CCLabelTTF* pLabel = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON_LABEL);
		pLabel->setVisible(true);
	}
	else
	{
		CCMenu* pButton = (CCMenu*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON);
		pButton->setVisible(false);
		CCLabelTTF* pLabel = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_LVUP_BUTTON_LABEL);
		pLabel->setVisible(false);

		CCLabelTTF* Line2 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_2);
		Line2->setString(SysLangDataManager::get_instance2()->GetSysLangById(4007).c_str());
		CCLabelTTF* Line3 = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_INFO_LINE_3);
		Line3->setVisible(false);
	}
}

void ConvictionWindow::_uckCheckPrayFreeTimes()
{
	if(HeroTechnologyDataHandler::get_instance2()->m_free_pray_times >0)
	{
		CCSprite* bg = (CCSprite*)m_pRootNode->getChildByTag(Conviction_PRAY_FREE_TIMES_BG);
		bg->setVisible(true);
		CCLabelTTF* times = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_PRAY_FREE_TIMES);
		char _times[128]="";
		sprintf(_times,"%d",HeroTechnologyDataHandler::get_instance2()->m_free_pray_times);
		times->setString(_times);
		times->setVisible(true);

		CCLabelTTF* cost = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_DIAMOND_COST);
		cost->setString(SysLangDataManager::get_instance2()->GetSysLangById(51).c_str());
		cost->setVisible(true);

		CCSprite* cost_image = (CCSprite*)m_pRootNode->getChildByTag(Conviction_DIAMOND_COST_IMAGE);
		cost_image->setVisible(false);
	}
	else
	{
		CCSprite* bg = (CCSprite*)m_pRootNode->getChildByTag(Conviction_PRAY_FREE_TIMES_BG);
		bg->setVisible(false);
		CCLabelTTF* times = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_PRAY_FREE_TIMES);
		times->setVisible(false);

		CCLabelTTF* cost = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_DIAMOND_COST);
		char _cost[128]="";
		sprintf(_cost,"%d",HeroTechnologyDataHandler::get_instance2()->m_pray_cost);
		cost->setString(_cost);
		cost->setVisible(true);

		CCSprite* cost_image = (CCSprite*)m_pRootNode->getChildByTag(Conviction_DIAMOND_COST_IMAGE);
		cost_image->setVisible(true);
	}
}

void ConvictionWindow::_uckSetPrayCostPoint()
{
	CCLabelTTF* point = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_POINT);
	char _point[128]="";
	sprintf(_point,"%d",HeroTechnologyDataHandler::get_instance2()->score);
	point->setString(_point);
}

void ConvictionWindow::_uckSetPrayButton()
{
	CCMenu* ptemp = (CCMenu*)m_pRootNode->getChildByTag(Conviction_PRAY_BUTTON);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	if(HeroTechnologyDataHandler::get_instance2()->m_pray_cost < 0)
		ptempItem->setEnabled(false);
	else
		ptempItem->setEnabled(true);

	CCLabelTTF* cost = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_DIAMOND_COST);
	if(HeroTechnologyDataHandler::get_instance2()->m_pray_cost < 0)
		cost->setVisible(false);
	else
		cost->setVisible(true);;

	CCSprite* cost_image = (CCSprite*)m_pRootNode->getChildByTag(Conviction_DIAMOND_COST_IMAGE);
	if(HeroTechnologyDataHandler::get_instance2()->m_pray_cost < 0)
		cost_image->setVisible(false);
	else
		cost_image->setVisible(true);
}

void ConvictionWindow::_uckSendGetTechnologyPointPacket()
{
	C2SGetTechnologyPointPacket crpacket;
	crpacket.Send();
}

void ConvictionWindow::_uckSetTechnologyCell( int key,int index )
{
	HeroTechnology* pTechnologyData = HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[index];
	_uckSetTechnologyBG(pTechnologyData,key);
	_uckSetTechnologyIcon(pTechnologyData,key);
	_uckSetTechnologyGreyLayer(pTechnologyData,key);
	_uckSetTechnologyTouchLayer(pTechnologyData,key);
	_uckSetTechnologySelectFrame(pTechnologyData,key);
	_uckSetTechnologyNookBG(pTechnologyData,key);
	_uckSetTechnologyNookLv(pTechnologyData,key);
	_uckSetTechnologyNameAndLv(pTechnologyData,key);

}

void ConvictionWindow::_uckHideTechnologyCell( int key )
{
	CCSprite* bg = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG)));
	bg->setVisible(false);
	CCSprite* icon = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_ICON-Conviction_IMAGE_1_BG));
	icon->setVisible(false);
	CCSprite* grey_layer = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_GREY_LAYER-Conviction_IMAGE_1_BG));
	grey_layer->setVisible(false);
	CPriorityLayerColor* touch_layer = (CPriorityLayerColor*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_TOUCH_LAYER-Conviction_IMAGE_1_BG));
	touch_layer->setVisible(false);
	CCSprite* select_fraame = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_SELECT_FRAME-Conviction_IMAGE_1_BG));
	select_fraame->setVisible(false);
	CCSprite* nook_bg = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_NOOK_BG-Conviction_IMAGE_1_BG));
	nook_bg->setVisible(false);
	CCLabelTTF* nook_label = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_NOOK_LABEL-Conviction_IMAGE_1_BG));
	nook_label->setVisible(false);
	CCLabelTTF* name_lv = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_NAME_LV-Conviction_IMAGE_1_BG));
	name_lv->setVisible(false);
}

void ConvictionWindow::_uckSetTechnologyBG( HeroTechnology* pTechnologyData,int key )
{
	//底图
	CCSprite* bg = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG)));
	bg->setVisible(true);
}

void ConvictionWindow::_uckSetTechnologyIcon( HeroTechnology* pTechnologyData,int key )
{
	//图标
	CCSprite* icon = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_ICON-Conviction_IMAGE_1_BG));
	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(ResourceIDDataManager::get_instance2()->getDataByID(pTechnologyData->icon).c_str());
	if(texture)
		icon->setTexture(texture);
	icon->setVisible(true);
}

void ConvictionWindow::_uckSetTechnologyGreyLayer( HeroTechnology* pTechnologyData,int key )
{
	//灰层
	CCSprite* grey_layer = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_GREY_LAYER-Conviction_IMAGE_1_BG));
	if (pTechnologyData->level >0)
		grey_layer->setVisible(false);
	else
		grey_layer->setVisible(true);
}

void ConvictionWindow::_uckSetTechnologyTouchLayer( HeroTechnology* pTechnologyData,int key )
{
	//按钮层
	CPriorityLayerColor* touch_layer = (CPriorityLayerColor*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_TOUCH_LAYER-Conviction_IMAGE_1_BG));
	touch_layer->setVisible(true);
}

void ConvictionWindow::_uckSetTechnologySelectFrame( HeroTechnology* pTechnologyData,int key )
{
	//选择框
	CCSprite* select_frame = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_SELECT_FRAME-Conviction_IMAGE_1_BG));
	if (select_frame != m_lastSelect)
		select_frame->setVisible(false);
}

void ConvictionWindow::_uckSetTechnologyNookBG( HeroTechnology* pTechnologyData,int key )
{
	//角标
	CCSprite* nook_bg = (CCSprite*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_NOOK_BG-Conviction_IMAGE_1_BG));
	if (pTechnologyData->level >0)
		nook_bg->setVisible(true);
	else
		nook_bg->setVisible(false);
}

void ConvictionWindow::_uckSetTechnologyNookLv( HeroTechnology* pTechnologyData,int key )
{
	//角标文字
	CCLabelTTF* nook_label = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_NOOK_LABEL-Conviction_IMAGE_1_BG));
	char _level[128]="";
	sprintf(_level,"%d",pTechnologyData->level);
	nook_label->setString(_level);
	if (pTechnologyData->level >0)
		nook_label->setVisible(true);
	else
		nook_label->setVisible(false);
}

void ConvictionWindow::_uckSetTechnologyNameAndLv( HeroTechnology* pTechnologyData,int key )
{
	//名称等级
	CCLabelTTF* name_lv = (CCLabelTTF*)m_pRootNode->getChildByTag(Conviction_IMAGE_1_BG+(key*(Conviction_IMAGE_2_BG - Conviction_IMAGE_1_BG))+(Conviction_IMAGE_1_NAME_LV-Conviction_IMAGE_1_BG));
	char _name_lv[128]="";
	sprintf(_name_lv,"%s+%d",IDStringDataManager::get_instance2()->GetIDStringByID(3,pTechnologyData->attriType).c_str(),pTechnologyData->addValue);
	name_lv->setString(_name_lv);
	name_lv->setVisible(true);
}
