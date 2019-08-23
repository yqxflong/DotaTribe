#ifndef  _DOTATRIBE_TEMPLEWINDOW_H_
#define  _DOTATRIBE_TEMPLEWINDOW_H_


#include "IWindow.h"
#include "../include/CMenuItemSprite.h"
#include "../include/EquipPromoteView.h"


class TempleWindow : public IWindow
{
public:
	TempleWindow();
	virtual ~TempleWindow();
	enum
	{
		TempleBG_BIG,
		TempleBG_SMALL,
		Temple_HELP,
		Temple_CLOSE,
		Temple_DIAMONDIMAGE,
		Temple_DIAMONDNUM,
		Temple_MONEYIMAGE,
		Temple_MONEYDNUM,
		Temple_TAB_ONE_BUTTON,
		Temple_TAB_ONE_BUTTON_LABEL,
	};
	enum
	{
		Temple_FIRST_TAB_,
		Temple_SECOND_TAB_,
	};
	CMenuItemSprite* m_Tab_One;
	CMenuItemSprite* m_Tab_Two;
	IWindow* m_showWindow;
	int m_tabNum;
	int m_return;


public:
	virtual bool Init();
	virtual bool Load();
	virtual void Tick();
	virtual void Destroy();
	virtual	void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	void On_Close(cocos2d::CCObject* pSender);
	void On_Help(cocos2d::CCObject* pSender);
	void On_SelectTab(cocos2d::CCObject* pSender);

	void InitLayer();
	void InitTab();
	void OnShowWindowEventHandler(std::list<std::string>& paramList);
	void OnUpdateTempleUI(std::list<std::string>& paramList);
private:
	inline void	_uckInitButton();
	inline void _uckUpdateDiamondAndMoney();
	inline void _uckInitTab(int tabNum);
	inline void _uckSetTabAndReturnWindow(std::list<std::string>& paramList);
	inline void _uckSelectTab(CMenuItemSprite* pItem);
	inline void _uckReturnWindow();
};


#endif
