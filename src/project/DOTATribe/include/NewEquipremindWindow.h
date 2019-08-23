//Name:NewEquipremindWindow
//Author: lvyunlong
//Func: ��װ�����ѹ���
//Maintainer:lvyunlong

#ifndef  _DOTATRIBE_NEWEQUIPREMINDWINDOW_H_
#define  _DOTATRIBE_NEWEQUIPREMINDWINDOW_H_

#include "IWindow.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/CPublicVarReader.h"
#include <cocos2d.h>
#include <cocos-ext.h>


class NewEquipremindWindow : public IWindow
{
private:
	enum{
			udBG = 0,
			udQUALITY,
			udEQUIPICON,
			udEFFECT,
			udDESCRIBE, 
			udCHECKBTN,
			udCHECKBTNTEXT,
			udCLOSEBTN,
		};
public:
	NewEquipremindWindow();
	virtual ~NewEquipremindWindow();
public:
	BagEquipData *m_pEquip;
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setEquipicon();
	inline void _setQualityicon();
public:
	/*
		��ʼ������
	*/
	virtual    bool    Init();
	/*
		���ش���
	*/
	virtual    bool    Load();
	/*
		����´���
	*/
	virtual    void    Tick();
	/*
		���ٴ���
	*/ 
	virtual    void    Destroy();
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		��ʾ���Ӣ������¼�����	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		���ػ��Ӣ������¼�����	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
private:
	void On_Check_ClickBtn(cocos2d::CCObject * pSender);

	void On_Close_ClickBtn(cocos2d::CCObject * pSender);
};


#endif