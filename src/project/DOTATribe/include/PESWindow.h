//Name��PESWindow
//Function��Ӣ�����
//Written By����ǿ

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
	//@����
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

protected:
	/*
		��ʾ����¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		ˢ��Ӣ��װ������
		type:0 ����װ����1: װ���б�
	*/
	void On_Refresh_HeroEquipView(int type);

	/*
		Tipsװ���ص�
	*/
	void On_Tips_Callback_Equip(std::list<std::string>& paramList);
	/*
		Tipsж�»ص�
	*/
	void On_Tips_Callback_Disboard(std::list<std::string>& paramList);

private:
	void _initLayout();
	void _mapBtn();
	void _mapTitle();
	void _highlightTabItem(unsigned int idx);
	void _selectTabItem(unsigned int idx);

	//@����װ����ս�����
	void _loadHeroEquipView(int tabidx=0);
	void _loadSoulView(int tabidx=0);

	//@���ս���Ƿ���
	//#δ��������ʾ
	bool _isSoulFuncOpen();

	//@����ս�갴ť����
	void _changeSoulBtnTitle(bool isSoul);
private:
	/*
		�رմ����¼�
	*/
	void On_Click_Event(cocos2d::CCObject* pSender);
	/*
		tab�ص�
	*/
	virtual void On_Tab_Selected(cocos2d::CCObject* pSender);
};


#endif
