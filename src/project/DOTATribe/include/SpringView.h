#ifndef  _DOTATRIBE_SPRINGVIEW_H_
#define  _DOTATRIBE_SPRINGVIEW_H_

#include "IWindow.h"
#include "../include/DOTATribeApp.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include <vector>
#include <map>

using namespace cocos2d;

class SpringView :public IWindow
{
private:

	enum
	{
		_Spring_BG_1,
		_Spring_BG_,
		_Spring_DESC_BG_,
		_Spring_DESC_,
		_Spring_Time_BG_,
		_Spring_Time_Labele1_,
		_Spring_Time_Labele2_,
		_Spring_Time_Labele3_,
		_Spring_Enter_Button_,
		_Spring_Enter_Button_Label,
	};
private:
	int m_CurWindowActiviId;
public:
	SpringView();
	virtual ~SpringView();
	void OnClick(cocos2d::CCObject* pSender);
	void initLayer();
	virtual bool    Init();
	virtual bool    Load();
	virtual void    Tick();
	virtual void    Destroy();
	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
private:
	
	
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);
	void   OnUpdateTempleUI(std::list<std::string>& paramList);
	void   UpdataButton();
};


#endif
