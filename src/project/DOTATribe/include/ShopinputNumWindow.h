//Name : ShopinputNumWindow
//Function : �̵����ι��򴰿������
//Author : lvyunlong
//Date : 201309

#ifndef  _DOTATRIBE_SHOPINPUTNUMWINDOW_H_
#define  _DOTATRIBE_SHOPINPUTNUMWINDOW_H_


#include "IWindow.h"
#include "../include/ShopInfoDataHandler.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class ShopinputNumWindow : public IWindow,public cocos2d::extension::CCEditBoxDelegate
{
private:
	enum{
		udPriorityBG = 0,
		udBG,
		udInputBG,
		udOnePriceBG,
		udTotalPricesBG,
		udCloseBtn,
		udADDBtn,
		udDELETEBtn,
		udMAXBtn,
		udBuyBtn,
		udBuyLB,
		udJewelMoney1,
		udJewelMoney2,
		udGoldMoney1,
		udGoldMoney2,
		udPRESTIGEMoney1,
		udPRESTIGEMoney2,
		udLONGXUE1,
		udLONGXUE2,
		udItemCountLB,
		udOnePriceLB,
		udTotalPriceLB,
		udItemnameLB,
	};
	enum
	{
		_TYPE_GOLD_ = 0,
		_TYPE_JEWEL_ ,
		_TYPE_PRESTIGE_,
		_TYPE_EXCHANGE_ITEM_,
	};
private:
	cocos2d::CCNode* m_pRoot;
	//��Ʒ���֡��ɹ����������������������͡�����

	ShopInfoGoodsData *m_Curshopdata;

	int m_moneytype;//��������
	int m_oneprice;//�����۸�
	bool m_IsKeyBroadShow; //�����Ƿ���ʾ

	bool m_bIfAreadySetted;//�Ƿ������ù�
	int m_iTypeShop;
private:

	CCEditBox* pEditBoxInputNum;	//����
public:
	ShopinputNumWindow();
	virtual ~ShopinputNumWindow();
private:
	inline void _initControl();
	inline void _initRegister();
	inline void _createLabel();
	inline void _mapBtn();
	inline void _setScaleandible();
	void  _initEditBox();//��ʼ��EditBox
public:
	void setTitle(const char* title);   //
	void deleteNum();//��߼��ٰ�ť
	void addNum();//�ұ����Ӱ�ť
	void setMaxNum();//��Ϊ�������
public:

	void On_Click_BtnClick(cocos2d::CCObject* pSender);
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

private:
	/*
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	 /*
		���´�������¼�����
	*/
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);
public:
	void   UpDataToTalNumPrice();

	//���õ�ǰ�������ͺ͵���
	void    setCurMoneyTypeandPrice(ShopInfoGoodsData *data);
	/*
		��õ�ǰ���ɹ�����
	*/
	int GetBuyAbiliMax();
public:
	 /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    
    
    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    
    /**
     * This method is called when the edit box text was changed.
     * @param editBox The edit box object that generated the event.
     * @param text The new text.
     */
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    
    /**
     * This method is called when the return button was pressed or the outside area of keyboard was touched.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxReturn(CCEditBox* editBox);
};


#endif
