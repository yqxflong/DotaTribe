// Name :		FriendWindow.h
// Function:	好友窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/FriendWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/WindowManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/FriendFightPacket.h"
#include "../include/PersonalChatPacket.h"
#include "../include/FriendCheckPlayerInfoPacket.h"
#include "../include/FriendAgreeSinglePacket.h"
#include "../include/FriendIgnoreSinglePacket.h"
#include "../include/FriendAddPacket.h"
#include "../include/FriendDeletePacket.h"
#include "../include/FriendAgreeAllPacket.h"
#include "../include/FriendIgnoreAllPacket.h"
#include "../include/FriendFindFriendPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/FriendRefurbishPacket.h"
#include "../include/FriendPacket.h"
#include "../include/MessageBoxWindow.h"
#include <include/common/Random.h>
#include <cocos2d.h>
#include <string.h>
#include <vector>
#include <list>
#include "../include/NFControlsManager.h"


using  namespace  cocos2d;
using  namespace  cocos2d::extension;


#define  OnePagePlayerNum 10
FriendWindow::FriendWindow()
{
	m_WindowType = _TYPED_WINDOW_FRIEND_;
	m_TabIndex = 1;
	m_CurPage = 1;
	m_MaxPage = 1;
	m_PlayerIndex = 0;
}

FriendWindow::~FriendWindow()
{

}

bool FriendWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_FRIENDWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_FRIENDWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_DELETE_FRIEND_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ALLFRIEND_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_FINDFRIENDWINDOW_, true);

	return IWindow::Init();
}

bool FriendWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		initLayer();
		
		return true;
	} 
	while (false);

	return false;
}

void FriendWindow::Tick()
{
	IWindow::Tick();
}

void FriendWindow::Destroy()
{
	m_TabIndex = 1;
	m_CurPage = 1;
	m_MaxPage = 1;
	m_PlayerIndex = 0;
	FriendDataHandler::get_instance2()->m_IsFindPlayer = false;
	IWindow::Destroy();
}

void FriendWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_FRIENDWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_FRIENDWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_FRIENDWINDOW_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_FINDFRIENDWINDOW_)
	{
		UpdataFindFriendList();
	}
	else if(iEventType == _TYPED_EVENT_DELETE_FRIEND_)
	{
		Sure_Delete();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_ALLFRIEND_)
	{
		//重新请求好友
		C2SFriendPacket crpacket;
		crpacket.Send();
		//重新请求推荐好友
		C2SFriendRefurbishPacket packet;
		packet.Send();
		NFC_showCommunicationWating(true);
	}
}

void FriendWindow::On_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_FRIENDWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
}	

void FriendWindow::On_SelectPlayer(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* pItem = (CMenuItemSprite*)pSender;
	m_PlayerIndex = (pItem->getParent()->getTag() - _Friend_HeadIcon1)/(_Friend_HeadIcon2 - _Friend_HeadIcon1)+ (m_CurPage-1)*OnePagePlayerNum;
	CCLOG("Index:%d",m_PlayerIndex);
	m_MarkLayer->setVisible(true);
	if (m_TabIndex == _Friend_MyFriendTab)
	{
		m_ApplyLayer->setVisible(false);
		m_NominateLayer->setVisible(false);
		m_MyFriendLayer->setVisible(true);
		m_MyFriendLayer->setPosition(ccp(pItem->getPositionX(),pItem->getPositionY()-pItem->getContentSize().height/2 - m_MyFriendLayer->getContentSize().height/2));
	}
	else if (m_TabIndex == _Friend_ApplyTab)
	{
		m_MyFriendLayer->setVisible(false);
		m_NominateLayer->setVisible(false);
		m_ApplyLayer->setVisible(true);
		m_ApplyLayer->setPosition(ccp(pItem->getPositionX(),pItem->getPositionY()-pItem->getContentSize().height/2 - m_ApplyLayer->getContentSize().height/2));
	}
	else if (m_TabIndex == _Friend_NominateTab)
	{
		m_MyFriendLayer->setVisible(false);
		m_ApplyLayer->setVisible(false);
		m_NominateLayer->setVisible(true);
		m_NominateLayer->setPosition(ccp(pItem->getPositionX(),pItem->getPositionY()-pItem->getContentSize().height/2 - m_NominateLayer ->getContentSize().height/2));
	}
}

void FriendWindow::On_CheckInfo(cocos2d::CCObject* pSender)
{
	int id = GetCurSelectedPlayerID();
	if (id != -1)
	{
		bool isFriendApply = false;
		//如果是从申请列表过来，则查看时添加好友直接走同意好友申请
		if (m_TabIndex == _Friend_ApplyTab)
		{
			isFriendApply = true;
		}
		FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(id, _TYPED_WINDOW_FRIEND_, isFriendApply);
		CloseLayer();
	}
}

void FriendWindow::On_AgreeSingle(cocos2d::CCObject* pSender)
{
	int id = GetCurSelectedPlayerID();
	if (id != -1)
	{
		C2SFriendAgreeSinglePacket pack(id);
		pack.Send();
		CloseLayer();
	}
}

void FriendWindow::On_IgnoreSingle(cocos2d::CCObject* pSender)
{
	int id = GetCurSelectedPlayerID();
	if (id != -1)
	{
		C2SFriendIgnoreSinglePacket pack(id);
		pack.Send();
		CloseLayer();
	}
}

void FriendWindow::On_Delete(cocos2d::CCObject* pSender)
{
	std::string str=SysLangDataManager::get_instance2()->GetSysLangById(164);
	NFC_showMessageBox(kFRIEND_DELETEFRIEND,str);
}

void FriendWindow::Sure_Delete()
{
	int id = GetCurSelectedPlayerID();
	if (id != -1)
	{
		C2SFriendDeletePacket pack(id);
		pack.Send();
		CloseLayer();
	}
}
void FriendWindow::On_AskForBeFriend(cocos2d::CCObject* pSender)
{
	if (FriendDataHandler::get_instance2()->m_IsFindPlayer)
	{
		C2SFriendAddPacket pack(FriendDataHandler::get_instance2()->m_FindPlayer.id);
		pack.Send();
		CloseLayer();
	}
	else
	{
		int id = GetCurSelectedPlayerID();
		if (id != -1)
		{
			C2SFriendAddPacket pack(id);
			pack.Send();
			CloseLayer();
		}
	}
}

void FriendWindow::On_SendMessage(cocos2d::CCObject* pSender)
{
	std::string _name = GetCurSelectedPlayerName();
	if (_name!="")
	{
		//写信
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_WRITEEMAILWINDOW_,_name);
		CloseLayer();
	}
}

void FriendWindow::On_AskForFight(cocos2d::CCObject* pSender)
{
	int id = GetCurSelectedPlayerID();
	if (id != -1)
	{
		C2SFriendFightPacket pack(RoleInfoDataHandler::get_instance2()->updateRoleAthleticsSerialID(),id);
		pack.Send();
		CloseLayer();
	}
}

void FriendWindow::On_FindFriend(cocos2d::CCObject* pSender)
{
	CCEditBox* pBox = (CCEditBox *)m_Root->getChildByTag(_Friend_FindBox);
	std::string temp =pBox->getText();
	if (temp!="")
	{
		C2SFriendFindFriendPacket pack(pBox->getText());
		pack.Send();
		pBox->setText("");
	}
}	

void FriendWindow::On_AllAgree(cocos2d::CCObject* pSender)
{
	if (FriendDataHandler::get_instance2()->ApplyList.size()>0)
	{
		C2SFriendAgreeAllPacket pack;
		pack.Send();
		CloseLayer();
	}
}	

void FriendWindow::On_AllIgnore(cocos2d::CCObject* pSender)
{
	if (FriendDataHandler::get_instance2()->ApplyList.size()>0)
	{
		C2SFriendIgnoreAllPacket pack;
		pack.Send();
		CloseLayer();
	}
}	

void FriendWindow::On_Refurbish(cocos2d::CCObject* pSender)
{
	NFC_showCommunicationWating(true);
	C2SFriendRefurbishPacket packet;
	packet.Send();
}	

void FriendWindow::On_LeftClick(cocos2d::CCObject* pSender)
{
	if (m_CurPage > 1)
	{
		m_CurPage--;
		UpdataFriendList();
		UpdataPage();
	}
}

void FriendWindow::On_RightClick(cocos2d::CCObject* pSender)
{
	if (m_CurPage < GetMaxPage())
	{
		m_CurPage++;
		UpdataFriendList();
		UpdataPage();
	}
}

void FriendWindow::On_SelectTab(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* pItem = (CMenuItemSprite*)pSender;
	UpdataSelectTab(pItem->getParent()->getTag());
}	

void FriendWindow::UpdataSelectTab(int index)
{
	CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_1);
	CMenuItemSprite* ptempItem1 = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_2);
	CMenuItemSprite* ptempItem2 = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_3);
	CMenuItemSprite* ptempItem3 = (CMenuItemSprite*)ptemp->getChildByTag(0);
	switch(index)
	{
	case _Friend_Tab_1:
		{
			m_TabIndex =1;
			m_CurPage =1;
			ptempItem1->selected(true);
			ptempItem2->unselected();
			ptempItem3->unselected();
			break;
		}
	case _Friend_Tab_2:
		{
			m_TabIndex =2;
			m_CurPage =1;
			ptempItem1->unselected();
			ptempItem2->selected(true);
			ptempItem3->unselected();
			break;
		}
	case _Friend_Tab_3:
		{
			m_TabIndex =3;
			m_CurPage =1;
			ptempItem1->unselected();
			ptempItem2->unselected();
			ptempItem3->selected(true);
			break;
		}
	default:
		break;
	}

	UpdataFriendList();
	UpdataButton();
	FriendDataHandler::get_instance2()->m_IsFindPlayer = false;
}

void FriendWindow::UpdataFriendList()
{
	ClearList();
	switch(m_TabIndex)
	{
	case _Friend_MyFriendTab:
		{
			int index = (m_CurPage-1) * OnePagePlayerNum;
			for (int i=0;i < OnePagePlayerNum;i++)
			{
				if (index+i < (int)FriendDataHandler::get_instance2()->MyFriendList.size())
				{
					CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_HeadIcon1+i*4);
					CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);

					CCSprite* pNormal =CCSprite::create();
					pNormal->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->MyFriendList[index+i]->iconId));
					CCSprite *pSelected =CCSprite::create();
					pSelected->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->MyFriendList[index+i]->iconId));
					ptempItem->setNormalImage(pNormal);
					ptempItem->setSelectedImage(pSelected);
					ptemp->setVisible(true);
					CCSprite *pTempSprite = (CCSprite*)m_Root->getChildByTag(_Friend_LvImage1+i*4);
					pTempSprite->setVisible(true);

					CCLabelTTF *pTempLabel1 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_LvValue1+i*4);
					char level[128]="";
					sprintf(level,"%d",FriendDataHandler::get_instance2()->MyFriendList[index+i]->level);
					pTempLabel1->setString(level);
					pTempLabel1->setVisible(true);

					CCLabelTTF *pTempLabel2 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_Name1+i*4);
					pTempLabel2->setString(FriendDataHandler::get_instance2()->MyFriendList[index+i]->name.c_str());
					pTempLabel2->setVisible(true);
				}
			}
			break;
		}
	case _Friend_ApplyTab:
		{
			int index = (m_CurPage-1) * OnePagePlayerNum;
			for (int i=0;i < OnePagePlayerNum;i++)
			{
				if (index+i < (int)FriendDataHandler::get_instance2()->ApplyList.size())
				{
					CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_HeadIcon1+i*4);
					CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
					CCLOG("ID:%d,iconID%d.",FriendDataHandler::get_instance2()->ApplyList[index+i]->id,FriendDataHandler::get_instance2()->ApplyList[index+i]->iconId);
					
					CCSprite* pNormal =CCSprite::create();
					pNormal->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->ApplyList[index+i]->iconId));
					CCSprite *pSelected =CCSprite::create();
					pSelected->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->ApplyList[index+i]->iconId));
					ptempItem->setNormalImage(pNormal);
					ptempItem->setSelectedImage(pSelected);
					ptemp->setVisible(true);
					CCSprite *pTempSprite = (CCSprite*)m_Root->getChildByTag(_Friend_LvImage1+i*4);
					pTempSprite->setVisible(true);

					CCLabelTTF *pTempLabel1 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_LvValue1+i*4);
					char level[128]="";
					sprintf(level,"%d",FriendDataHandler::get_instance2()->ApplyList[index+i]->level);
					pTempLabel1->setString(level);
					pTempLabel1->setVisible(true);

					CCLabelTTF *pTempLabel2 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_Name1+i*4);
					pTempLabel2->setString(FriendDataHandler::get_instance2()->ApplyList[index+i]->name.c_str());
					pTempLabel2->setVisible(true);
				}
			}
			UpdataApplyForFriendNum();
			break;
		}
	case _Friend_NominateTab:
		{
			int index = (m_CurPage-1) * OnePagePlayerNum;
			for (int i=0;i < OnePagePlayerNum;i++)
			{
				if (index+i < (int)FriendDataHandler::get_instance2()->NominateList.size())
				{
					CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_HeadIcon1+i*4);
					CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);

					CCSprite* pNormal =CCSprite::create();
					pNormal->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->NominateList[index+i]->iconId));
					CCSprite *pSelected =CCSprite::create();
					pSelected->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->NominateList[index+i]->iconId));
					ptempItem->setNormalImage(pNormal);
					ptempItem->setSelectedImage(pSelected);
					ptemp->setVisible(true);
					CCSprite *pTempSprite = (CCSprite*)m_Root->getChildByTag(_Friend_LvImage1+i*4);
					pTempSprite->setVisible(true);

					CCLabelTTF *pTempLabel1 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_LvValue1+i*4);
					char level[128]="";
					sprintf(level,"%d",FriendDataHandler::get_instance2()->NominateList[index+i]->level);
					pTempLabel1->setString(level);
					pTempLabel1->setVisible(true);

					CCLabelTTF *pTempLabel2 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_Name1+i*4);
					pTempLabel2->setString(FriendDataHandler::get_instance2()->NominateList[index+i]->name.c_str());
					pTempLabel2->setVisible(true);
				}
			}
			break;
		}
	default:
		return ;
	}
	UpdataApplyForFriendNum();
	UpdataFriendNum();
	UpdataPage();
}

void FriendWindow::UpdataFindFriendList()
{
	ClearList();
	m_TabIndex =3;
	m_CurPage =1;
	CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_1);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->unselected();
	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_2);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->unselected();
	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_3);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->selected(true);

	
	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_HeadIcon1);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);

	CCSprite* pNormal =CCSprite::create();
	pNormal->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->m_FindPlayer.iconId));
	CCSprite *pSelected =CCSprite::create();
	pSelected->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(FriendDataHandler::get_instance2()->m_FindPlayer.iconId));
	ptempItem->setNormalImage(pNormal); 
	ptempItem->setSelectedImage(pSelected);
	ptemp->setVisible(true);
	CCSprite *pTempSprite = (CCSprite*)m_Root->getChildByTag(_Friend_LvImage1);
	pTempSprite->setVisible(true);

	CCLabelTTF *pTempLabel1 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_LvValue1);
	char level[128]="";
	sprintf(level,"%d",FriendDataHandler::get_instance2()->m_FindPlayer.level);
	pTempLabel1->setString(level);
	pTempLabel1->setVisible(true);

	CCLabelTTF *pTempLabel2 = (CCLabelTTF*)m_Root->getChildByTag(_Friend_Name1);
	pTempLabel2->setString(FriendDataHandler::get_instance2()->m_FindPlayer.name.c_str());
	pTempLabel2->setVisible(true);
}

void FriendWindow::ClearList()
{	
	for (int i=_Friend_HeadIcon1;i<=_Friend_Name10;i++)
	{
		CCNode* ptemp = (CCNode*)m_Root->getChildByTag(i);
		ptemp->setVisible(false);
	}
}

void FriendWindow::UpdataFriendNum()
{
	CCLabelTTF* pNum = (CCLabelTTF*)m_Root->getChildByTag(_Friend_FriendText); 
	char _num[128]="";
	sprintf(_num,"%d/%d",FriendDataHandler::get_instance2()->m_FriendNum,FriendDataHandler::get_instance2()->m_MaxFriendNum);
	pNum->setString(_num);
}

void FriendWindow::UpdataPage()
{
	CCLabelTTF* pPage = (CCLabelTTF*)m_Root->getChildByTag(_Friend_PageText); 
	char _page[128]="";
	sprintf(_page,"%d/%d",m_CurPage,GetMaxPage());
	pPage->setString(_page);
}

void  FriendWindow::UpdataApplyForFriendNum()
{
	if (FriendDataHandler::get_instance2()->ApplyList.size() > 0)
	{
		CCSprite *bg =  (CCSprite*)m_Root->getChildByTag(_Friend_ApplyForFriendNumBG); 
		bg->setVisible(true);

		CCLabelTTF* num = (CCLabelTTF*)m_Root->getChildByTag(_Friend_ApplyForFriendNum); 
		char _num[128]="";
		sprintf(_num,"%d",FriendDataHandler::get_instance2()->ApplyList.size());
		num->setString(_num);
		num->setVisible(true);
	}
	else
	{
		CCSprite *bg =  (CCSprite*)m_Root->getChildByTag(_Friend_ApplyForFriendNumBG); 
		bg->setVisible(false);

		CCLabelTTF* num = (CCLabelTTF*)m_Root->getChildByTag(_Friend_ApplyForFriendNum); 
		num->setVisible(false);
	}
}

int  FriendWindow::GetMaxPage()
{
	if (m_TabIndex == _Friend_MyFriendTab)
	{
		if (FriendDataHandler::get_instance2()->MyFriendList.size()%OnePagePlayerNum != 0 || FriendDataHandler::get_instance2()->MyFriendList.size() == 0)
			return (FriendDataHandler::get_instance2()->MyFriendList.size()/OnePagePlayerNum + 1);
		else
			return (FriendDataHandler::get_instance2()->MyFriendList.size()/OnePagePlayerNum);
	}
	else if (m_TabIndex == _Friend_ApplyTab)
	{
		if (FriendDataHandler::get_instance2()->ApplyList.size()%OnePagePlayerNum != 0 || FriendDataHandler::get_instance2()->ApplyList.size() == 0)
			return (FriendDataHandler::get_instance2()->ApplyList.size()/OnePagePlayerNum +1);
		else
			return (FriendDataHandler::get_instance2()->ApplyList.size()/OnePagePlayerNum);
	}
	else if (m_TabIndex == _Friend_NominateTab)
	{
		return 1;
	}
	else
		return -1;
}

void FriendWindow::UpdataButton()
{
	
	if (m_TabIndex == _Friend_MyFriendTab)
	{
		CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllAgree);
		ptemp->setVisible(false);
		CCLabelTTF* pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_AllAgreeTitle); 
		pLabel->setVisible(false);
		ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllIgnore);
		ptemp->setVisible(false);
		pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_AllIgnoreTitle); 
		pLabel->setVisible(false);
		ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Refurbish);
		ptemp->setVisible(false);
		pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_RefurbishTitle); 
		pLabel->setVisible(false);

	}
	else if(m_TabIndex == _Friend_ApplyTab)
	{
		CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllAgree);
		ptemp->setVisible(true);
		CCLabelTTF* pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_AllAgreeTitle); 
		pLabel->setVisible(true);
		ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllIgnore);
		ptemp->setVisible(true);
		pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_AllIgnoreTitle); 
		pLabel->setVisible(true);
		ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Refurbish);
		ptemp->setVisible(false);
		pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_RefurbishTitle); 
		pLabel->setVisible(false);
	}
	else if(m_TabIndex == _Friend_NominateTab)
	{
		CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllAgree);
		ptemp->setVisible(false);
		CCLabelTTF* pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_AllAgreeTitle); 
		pLabel->setVisible(false);
		ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllIgnore);
		ptemp->setVisible(false);
		pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_AllIgnoreTitle); 
		pLabel->setVisible(false);
		ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Refurbish);
		ptemp->setVisible(true);
		pLabel = (CCLabelTTF*)m_Root->getChildByTag(_Friend_RefurbishTitle); 
		pLabel->setVisible(true);
	}

}

int FriendWindow::GetCurSelectedPlayerID()
{
	switch(m_TabIndex)
	{
	case _Friend_MyFriendTab:
		{
			if (m_PlayerIndex < (int)FriendDataHandler::get_instance2()->MyFriendList.size())
				return FriendDataHandler::get_instance2()->MyFriendList[m_PlayerIndex]->id;
		}
	case _Friend_ApplyTab:
		{
			if (m_PlayerIndex < (int)FriendDataHandler::get_instance2()->ApplyList.size())
				return FriendDataHandler::get_instance2()->ApplyList[m_PlayerIndex]->id;
		}
	case _Friend_NominateTab:
		{
			if (FriendDataHandler::get_instance2()->m_IsFindPlayer)
			{
				return FriendDataHandler::get_instance2()->m_FindPlayer.id;
			}
			else
			{
				if (m_PlayerIndex < (int)FriendDataHandler::get_instance2()->NominateList.size())
					return FriendDataHandler::get_instance2()->NominateList[m_PlayerIndex]->id;
			}

		}
	default:
		return -1;
	}
}

std::string FriendWindow::GetCurSelectedPlayerName()
{
	switch(m_TabIndex)
	{
	case _Friend_MyFriendTab:
		{
			if (m_PlayerIndex < (int)FriendDataHandler::get_instance2()->MyFriendList.size())
				return FriendDataHandler::get_instance2()->MyFriendList[m_PlayerIndex]->name;
		}
	case _Friend_ApplyTab:
		{
			if (m_PlayerIndex < (int)FriendDataHandler::get_instance2()->ApplyList.size())
				return FriendDataHandler::get_instance2()->ApplyList[m_PlayerIndex]->name;
		}
	case _Friend_NominateTab:
		{
			if (FriendDataHandler::get_instance2()->m_IsFindPlayer)
			{
				return FriendDataHandler::get_instance2()->m_FindPlayer.name;
			}
			else
			{
				if (m_PlayerIndex < (int)FriendDataHandler::get_instance2()->NominateList.size())
					return FriendDataHandler::get_instance2()->NominateList[m_PlayerIndex]->name;
			}

		}
	default:
		return "";
	}
}

bool FriendWindow::IsListEmpty()
{
	switch(m_TabIndex)
	{
	case _Friend_MyFriendTab:
		{
			if (FriendDataHandler::get_instance2()->MyFriendList.size() > 0)
				return false;
		}
	case _Friend_ApplyTab:
		{
			if (FriendDataHandler::get_instance2()->ApplyList.size() > 0)
				return false;
		}
	case _Friend_NominateTab:
		{
			if (FriendDataHandler::get_instance2()->NominateList.size() > 0)
				return false;
		}
	default:
		return true;
	}
}

void FriendWindow::initLayer()
{
	CCNode *pNode =m_pRootNode;
	m_Root = CCNode::create();
	pNode->addChild(m_Root,10);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kFRIENDWINDOW,m_Root);

	CCEditBox* box = (CCEditBox*)m_Root->getChildByTag(_Friend_FindBox);
	box->setMaxLength(20); 
	box->setInputMode(kEditBoxInputModeAny); 
	box->setReturnType(kKeyboardReturnTypeDone);


	
	CCMenu* ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_CloseButton);
	
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_Close));
	
	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_1);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_SelectTab));
	ptempItem->selected(true);

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_2);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_SelectTab));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Tab_3);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_SelectTab));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_FindButton);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_FindFriend));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllAgree);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_AllAgree));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_AllIgnore);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_AllIgnore));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_Refurbish);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_Refurbish));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_LeftButton);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_LeftClick));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_RightButton);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_RightClick));


	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_MyFriendItem1);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_CheckInfo));


	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_MyFriendItem2);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_Delete));


	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_MyFriendItem3);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_SendMessage));


	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_MyFriendItem4);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_AskForFight));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_ApplyItem1);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_CheckInfo));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_ApplyItem2);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_AgreeSingle));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_ApplyItem3);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_IgnoreSingle));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_NominateItem1);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_CheckInfo));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_NominateItem2);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_AskForBeFriend));

	ptemp = (CCMenu*)m_Root->getChildByTag(_Friend_NominateItem3);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(FriendWindow::On_SendMessage));

	for (int i=_Friend_HeadIcon1;i<=_Friend_Name10;i=i+4)
	{
		ptemp = (CCMenu*)m_Root->getChildByTag(i);
		ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
		ptempItem->setTarget(this,menu_selector(FriendWindow::On_SelectPlayer));
	}

	CPriorityLayerColor* pLayer = (CPriorityLayerColor*)m_Root->getChildByTag(_Friend_MarkLayer);
	pLayer->setVisible(false);
	pLayer->setDelegate(this);
	m_MarkLayer = pLayer;
	CPriorityLayerColor* pLayer1 = (CPriorityLayerColor*)m_Root->getChildByTag(_Friend_MyFriendLayer);
	for (int i=_Friend_MyFriendBG;i<=_Friend_MyFriendItem4Title;i++)
	{
		CCNode* pTempNode = m_Root->getChildByTag(i);
		pTempNode->removeFromParent();
		pTempNode->setParent(NULL);
		pLayer1->addChild(pTempNode,i);

	}
	m_MyFriendLayer = pLayer1;
	pLayer1->setVisible(false);

	CPriorityLayerColor* pLayer2 = (CPriorityLayerColor*)m_Root->getChildByTag(_Friend_ApplyLayer);
	for (int i=_Friend_ApplyBG;i<=_Friend_ApplyItem3Title;i++)
	{
		CCNode* pTempNode = m_Root->getChildByTag(i);
		pTempNode->removeFromParent();
		pTempNode->setParent(NULL);
		pLayer2->addChild(pTempNode,i);
	}
	m_ApplyLayer = pLayer2;
	pLayer2->setVisible(false);

	CPriorityLayerColor* pLayer3 = (CPriorityLayerColor*)m_Root->getChildByTag(_Friend_NominateLayer);
	for (int i=_Friend_NominateBG;i<=_Friend_NominateItem3Title;i++)
	{
		CCNode* pTempNode = m_Root->getChildByTag(i);
		pTempNode->removeFromParent();
		pTempNode->setParent(NULL);
		pLayer3->addChild(pTempNode,i);
	}
	m_NominateLayer= pLayer3;
	pLayer3->setVisible(false);
	UpdataButton();
	UpdataApplyForFriendNum();
}

void FriendWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	if (FriendDataHandler::get_instance2()->ApplyList.size()>0&&!m_pRootNode->isVisible())
		UpdataSelectTab(_Friend_Tab_2);
	UpdataFriendList();
	Show(true);	
}

void FriendWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{
	UpdataFriendList();
}

void FriendWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	CloseLayer();
}

void FriendWindow::CloseLayer()
{
	m_MarkLayer->setVisible(false);
	m_MyFriendLayer->setVisible(false);
	m_ApplyLayer->setVisible(false);
	m_NominateLayer->setVisible(false);
}

void FriendWindow::On_Close_Window(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_FRIENDWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
}

