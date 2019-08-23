// Name :SoulTipsWindow.h
// Function��ս��tips����
// Author : lvyunlong
// Date: 20140224

#ifndef  _DOTATRIBE_SOULTIPSWINDOW_H_
#define  _DOTATRIBE_SOULTIPSWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/RoleSoulsDataHandler.h"

enum{
	_SOULTIPS_OWNER_ = 0,
	_SOULTIPS_OTHER_
};

enum{
	_SOUL_DB_TYPE_ = 0,
	_SOUL_HERO_TYPE_,
};

class SoulTipsWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum{
		_SOULTIPS_PRIORITY = 0,//�ڸǲ�
		_SOULTIPS_BG,		//����
		_SOULTIPS_NAME,			//����
		_SOULTIPS_SOULFRAME,	//�׿�
		_SOULTIPS_SOULICON,		//ս��ͼ��
		_SOULTIPS_LEVEL,		//�ȼ�
		_SOULTIPS_ADDITTION,	//����1
		_SOULTIPS_EQUIPEDBTN,	//װ����ť
		_SOULTIPS_EQUIPEDTTF,	//װ����ť����
		_SOULTIPS_UNLOADBTN,	//ж�ذ�ť
		_SOULTIPS_UNLOADTTF,	//ж�ذ�ť����
		_SOULTIPS_CLOSEBTN,	//�رհ�ť
	}SOULTIPS;


	IHeroSoulItem * m_pNeedSoulData;
	int m_soulBufferID;
	int m_soulType;
	unsigned char m_Heroindex;
public:
	SoulTipsWindow();
	virtual ~SoulTipsWindow();

private:
	inline void _initLayout();
	/*
		��ʼ���ؼ�
	*/
	inline void _initControl();

	void _mapBtn();

	void setBtnshow();
	void setInfoTips();
public:
	virtual    bool    Init();

	virtual    bool    Load();

	virtual    void    Tick();

	virtual    void    Destroy();

public:
	/*
	��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
	show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		װ����ť
	*/
	void On_Check_Equip_Event(cocos2d::CCObject* pSender);
	/*
		�رհ�ť
	*/
	void On_Check_Close_Event(cocos2d::CCObject* pSender);

	/*
		ж�°�ť
	*/
	void On_Check_Disboard_Event(cocos2d::CCObject* pSender);
};


#endif
