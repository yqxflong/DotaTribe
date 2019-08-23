// Name :		FriendWindow.h
// Function:	ºÃÓÑ´°¿Ú
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_FRIENDWINDOW_H_
#define  _DOTATRIBE_FRIENDWINDOW_H_


#include "../include/CMenuItemSprite.h"
#include "../include/IWindow.h"
#include "../include/CPublicVarReader.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/ChatDataHandler.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include <vector>
#include <list>
using namespace cocos2d;
using namespace cocos2d::extension;
class FriendWindow : public IWindow,CPriorityLayerColorDelegate
{
	enum
	{
		_Friend_BG_Down,
		_Friend_BG,
		_Friend_HelpButton,
		_Friend_CloseButton,
		_Friend_Tab_1,
		_Friend_Tab_1Title,
		_Friend_Tab_2,
		_Friend_Tab_2Title,
		_Friend_Tab_3,
		_Friend_Tab_3Title,
		_Friend_FriendTitle,
		_Friend_FriendText,
		_Friend_LeftButton,
		_Friend_RightButton,
		_Friend_PageBG,
		_Friend_PageText,
		_Friend_HeadIcon1,
		_Friend_LvImage1,
		_Friend_LvValue1,
		_Friend_Name1,
		_Friend_HeadIcon2,
		_Friend_LvImage2,
		_Friend_LvValue2,
		_Friend_Name2,
		_Friend_HeadIcon3,
		_Friend_LvImage3,
		_Friend_LvValue3,
		_Friend_Name3,
		_Friend_HeadIcon4,
		_Friend_LvImage4,
		_Friend_LvValue4,
		_Friend_Name4,
		_Friend_HeadIcon5,
		_Friend_LvImage5,
		_Friend_LvValue5,
		_Friend_Name5,
		_Friend_HeadIcon6,
		_Friend_LvImage6,
		_Friend_LvValue6,
		_Friend_Name6,
		_Friend_HeadIcon7,
		_Friend_LvImage7,
		_Friend_LvValue7,
		_Friend_Name7,
		_Friend_HeadIcon8,
		_Friend_LvImage8,
		_Friend_LvValue8,
		_Friend_Name8,
		_Friend_HeadIcon9,
		_Friend_LvImage9,
		_Friend_LvValue9,
		_Friend_Name9,
		_Friend_HeadIcon10,
		_Friend_LvImage10,
		_Friend_LvValue10,
		_Friend_Name10,
		_Friend_FindBox,
		_Friend_FindButton,
		_Friend_FindTitle,
		_Friend_AllAgree,
		_Friend_AllAgreeTitle,
		_Friend_AllIgnore,
		_Friend_AllIgnoreTitle,
		_Friend_Refurbish,
		_Friend_RefurbishTitle,
		_Friend_MarkLayer,
		_Friend_MyFriendLayer,
		_Friend_MyFriendBG,
		_Friend_MyFriendItem1,
		_Friend_MyFriendItem1Title,
		_Friend_MyFriendItem2,
		_Friend_MyFriendItem2Title,
		_Friend_MyFriendItem3,
		_Friend_MyFriendItem3Title,
		_Friend_MyFriendItem4,
		_Friend_MyFriendItem4Title,
		_Friend_ApplyLayer,
		_Friend_ApplyBG,
		_Friend_ApplyItem1,
		_Friend_ApplyItem1Title,
		_Friend_ApplyItem2,
		_Friend_ApplyItem2Title,
		_Friend_ApplyItem3,
		_Friend_ApplyItem3Title,
		_Friend_NominateLayer,
		_Friend_NominateBG,
		_Friend_NominateItem1,
		_Friend_NominateItem1Title,
		_Friend_NominateItem2,
		_Friend_NominateItem2Title,
		_Friend_NominateItem3,
		_Friend_NominateItem3Title,
		_Friend_ApplyForFriendNumBG,
		_Friend_ApplyForFriendNum,
	};

	enum
	{
		_Friend_UnknowTab,
		_Friend_MyFriendTab,
		_Friend_ApplyTab,
		_Friend_NominateTab,
	};
public:
	FriendWindow();
	virtual ~FriendWindow();

	int m_TabIndex;
	int m_CurPage;
	int m_MaxPage;
	int m_PlayerIndex;
	CPriorityLayerColor* m_MarkLayer;
	CPriorityLayerColor* m_MyFriendLayer;
	CPriorityLayerColor* m_ApplyLayer;
	CPriorityLayerColor* m_NominateLayer;

	CCNode * m_Root;
public:
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
public:

	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	void initLayer();
	void UpdataFriendList();
	void UpdataSelectTab(int index);
	void UpdataFindFriendList();
	void UpdataButton();
	void UpdataFriendNum();
	void UpdataPage();
	void UpdataApplyForFriendNum();
	void ClearList();
	void CloseLayer();
	int  GetCurSelectedPlayerID();
	std::string GetCurSelectedPlayerName();
	int  GetMaxPage();
	void Sure_Delete();
	bool IsListEmpty();
	void On_Close(cocos2d::CCObject* pSender);
	void On_SelectTab(cocos2d::CCObject* pSender);
	void On_FindFriend(cocos2d::CCObject* pSender);
	void On_AllAgree(cocos2d::CCObject* pSender);
	void On_AllIgnore(cocos2d::CCObject* pSender);
	void On_Refurbish(cocos2d::CCObject* pSender);
	void On_LeftClick(cocos2d::CCObject* pSender);
	void On_RightClick(cocos2d::CCObject* pSender);
	void On_CheckInfo(cocos2d::CCObject* pSender);
	void On_AgreeSingle(cocos2d::CCObject* pSender);
	void On_IgnoreSingle(cocos2d::CCObject* pSender);
	void On_Delete(cocos2d::CCObject* pSender);
	void On_SendMessage(cocos2d::CCObject* pSender);
	void On_AskForBeFriend(cocos2d::CCObject* pSender);
	void On_AskForFight(cocos2d::CCObject* pSender);
	void On_SelectPlayer(cocos2d::CCObject* pSender);
	void OnShowWindowEventHandler(std::list<std::string>& paramList);
	void OnUpdateUITextEventHandler(std::list<std::string>& paramList);
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	virtual void On_Close_Window(cocos2d::CCObject* pSender);
};


#endif

