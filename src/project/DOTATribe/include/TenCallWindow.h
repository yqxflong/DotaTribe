//Name : TenCallWindow
//Function : ʮ�����ٻ�����
//Author : lvyunlong
//Date: 20140522

#ifndef  _DOTATRIBE_TENCALLWINDOW_H_
#define  _DOTATRIBE_TENCALLWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/IPopWindow.h"

class TenCallWindow : public IWindow 
	,public IPopWindow
{
private:
	enum{
			TEN_PRIORITY = 0,
			TEN_DTAWARD,
			TEN_DTHEROICON,
			TEN_HEROTYPE,
			TEN_HAVEICON,
			TEN_NEWICON,
			TEN_NAMEFRAME,
			TEN_NAMETTF,
			TEN_START,
			udHEROLISTBTN =81,
			udHEROLISTTEXT,
		};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCLayer* m_pLayer;
public:
	TenCallWindow();
	virtual ~TenCallWindow();
	
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _setHeroType(int index,int type,cocos2d::CCNode * pParent);
	inline void _setStarRank();
	inline void _setHeroBoard(int type);
	inline void _setAwardBoard();
	void _setinfodata();
	void _mapBtn();
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

	//��ʾ����
	virtual void ShowPopWindow();
	//�����Ѿ�����
	virtual void PopWindowDidHide();
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		��ʾ���Ӣ������¼�����	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	void ShowWindow();
	/*
		���ػ��Ӣ������¼�����	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_Enevnt(cocos2d::CCObject* pSender);

	void On_Click_Summon_Event(cocos2d::CCObject* pSender);

};


#endif