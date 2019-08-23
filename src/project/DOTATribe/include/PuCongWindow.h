//Name : PuCongWindow
//Function : �ʹ�
//Author : ����

#ifndef _DOTATRIBE_PUCONGWINDOW_H_
#define _DOTATRIBE_PUCONGWINDOW_H_

#include "../include/IWindow.h"
#include "../include/SubView.h"
#include "cocos-ext.h"

class PuCongWindow : public IWindow
{
private:
	enum
	{
		pBg = 0,
		pBoard,
		pCloseBtn,
		pHuntTab,
		pHuntTabTTF,
		pServantTab,
		pServantTabTTF,
		pMiningTab,
		pMiningTabTTF,
	};

private:
	SubView* m_pSubView;
	const int m_nSVZorder;
	int m_nBackWindow;
	std::string m_strParam1;

	cocos2d::CCNode * m_pRoot; 

public:
	enum{
		HLW_MINING = 0,		//�ڿ�
		HLW_HUNT = 1,		//��Ѱ��
		HLW_SERVANT = 2,	//�ʹӷ�ҳ
	};
	PuCongWindow();
	virtual ~PuCongWindow();

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

protected:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		��ʾ����¼�����
	*/
	inline void OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		��������¼�����
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

private:
	inline void _checkNewFunc();
	inline void _loadWindowControls();
	inline void _mapBtn();
	inline void _loadSubViews(unsigned int idx);
	inline void selectTabItem(unsigned int index);
private:
	/*
		�رմ����¼�
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);

	/*
		tab�ص�
	*/
	virtual void On_Tab_Selected(cocos2d::CCObject* pSender);

};


#endif