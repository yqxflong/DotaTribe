//Name：PESWindow
//Function：英雄相关
//Written By：尹强

#ifndef  _DOTATRIBE_PESWINDOW_H_
#define  _DOTATRIBE_PESWINDOW_H_

#include "IWindow.h"

class HeroWindowSubView;
class PESWindow : public IWindow
{
public:
	enum
	{
		LOAD_EQUIP_VIEW = 0,
		LOAD_SOUL_VIEW,
	};
private:
	HeroWindowSubView* m_pSubView;
public:
	int m_nBackWindowType;
	int m_CurTabId;
	int m_TypeView;
public:
	enum{
		kBG,
		kCLOSE,
		kHELP,
		kBTN_SOUL,
		kBTN_SOUL_TITLE,
		kTAB_1,
		kTAB_1_TL,
		kTAB_2,
		kTAB_2_TL,
		kTAB_3,
		kTAB_3_TL,
	};
	PESWindow();
	virtual ~PESWindow(){};

public:
	//@标配
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

protected:
	/*
		显示面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		刷新英雄装备界面
		type:0 人物装备，1: 装备列表
	*/
	void On_Refresh_HeroEquipView(int type);

	/*
		Tips装备回调
	*/
	void On_Tips_Callback_Equip(std::list<std::string>& paramList);
	/*
		Tips卸下回调
	*/
	void On_Tips_Callback_Disboard(std::list<std::string>& paramList);

private:
	void _initLayout();
	void _mapBtn();
	void _mapTitle();
	void _highlightTabItem(unsigned int idx);
	void _selectTabItem(unsigned int idx);

	//@载入装备和战魂界面
	void _loadHeroEquipView(int tabidx=0);
	void _loadSoulView(int tabidx=0);

	//@检查战魂是否开启
	//#未开启给提示
	bool _isSoulFuncOpen();

	//@更改战魂按钮标题
	void _changeSoulBtnTitle(bool isSoul);
private:
	/*
		关闭窗口事件
	*/
	void On_Click_Event(cocos2d::CCObject* pSender);
	/*
		tab回调
	*/
	virtual void On_Tab_Selected(cocos2d::CCObject* pSender);
};


#endif
