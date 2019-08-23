//Name : ShopWindow
//Function : �̵�
//Author : ������

#ifndef  _DOTATRIBE_SHOPWINDOW_H_
#define  _DOTATRIBE_SHOPWINDOW_H_


#include "../include/IWindow.h"
#include "../include/ShopView.h"
#include "../include/SecretView.h"
#include "../include/SpecialOfferView.h"
#include <string>
#include "cocos-ext.h"

#define TAB_VIEW_INDEX_0_		0
#define TAB_VIEW_INDEX_1_		1


#define  PRESTIGE_SHOP	0
#define  SECRET_SHOP	1

class ShopWindow : public IWindow
{
private:
	enum
	{
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
	ShopWindow();
	virtual ~ShopWindow();
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
	/*
		�����̵�����¼�����
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);
	/*
		ˢ������̵��¼�����
	*/
	inline void OnUpdataWindowEventHandler(std::list<std::string>& paramList);
private:

	void selectSubTabItem(int idx);

public:

	void On_Tab_Selected(cocos2d::CCObject* pSender);

private:
	/*
		�رմ����¼�
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);
	/*
		����Ƿ����ر��̵�
	*/
	bool _checkOpenMBShop();
};


#endif
