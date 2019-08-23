//Name : MarketWindow
//Function : �̳�
//Author : ������
//�����ʱ�� 20131210

#ifndef  _DOTATRIBE_MARKETWINDOW_H_
#define  _DOTATRIBE_MARKETWINDOW_H_


#include "../include/IWindow.h"
#include "../include/SpecialOfferView.h"
#include "../include/BoutiqueView.h"
#include <string>
#include "cocos-ext.h"

#define TAB_VIEW_INDEX_0_		0
#define TAB_VIEW_INDEX_1_		1

#define  SPECIALOFFER_MARKET	2
#define  BOUTIQUE_MARKET	3

class MarketWindow : public IWindow
{
private:
	enum
	{
		udGRAYLAYER = 0,
		udMAINBG,
		udTAB1,
		udTAB2,
		udCLOSEBTN,
	};
private:
	SHSubView* m_pSubView;
	const int m_nSVZorder;
	int m_nBackWindow;
	std::string m_strParam1;
public:
	MarketWindow();
	virtual ~MarketWindow();
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
	inline void _initLayout();
	inline void _loadSubView();
	inline void _mapBtn();
	
public:
	void _selectTabItem(unsigned int idx);

	void _loadSubView(unsigned int idx);

	void _resetAllHighlight();
	void _highlightTabItem(unsigned int idx);

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		��ʾ�̵�����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		�����̵�����¼�����
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);
private:

	void selectSubTabItem(int idx);

public:

	void On_Tab_Selected(cocos2d::CCObject* pSender);

private:
	/*
		�رմ����¼�
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);
	
};


#endif
