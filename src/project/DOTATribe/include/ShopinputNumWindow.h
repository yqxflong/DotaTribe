//Name : ShopinputNumWindow
//Function : 商店批次购买窗口输入框
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
	//物品名字、可购买量、最大购买量、金币类型、单价

	ShopInfoGoodsData *m_Curshopdata;

	int m_moneytype;//货币类型
	int m_oneprice;//单个价格
	bool m_IsKeyBroadShow; //键盘是否显示

	bool m_bIfAreadySetted;//是否已设置过
	int m_iTypeShop;
private:

	CCEditBox* pEditBoxInputNum;	//数字
public:
	ShopinputNumWindow();
	virtual ~ShopinputNumWindow();
private:
	inline void _initControl();
	inline void _initRegister();
	inline void _createLabel();
	inline void _mapBtn();
	inline void _setScaleandible();
	void  _initEditBox();//初始化EditBox
public:
	void setTitle(const char* title);   //
	void deleteNum();//左边减少按钮
	void addNum();//右边增加按钮
	void setMaxNum();//设为最大数量
public:

	void On_Click_BtnClick(cocos2d::CCObject* pSender);
public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	 /*
		更新大厅面板事件处理
	*/
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);
public:
	void   UpDataToTalNumPrice();

	//设置当前货币类型和单价
	void    setCurMoneyTypeandPrice(ShopInfoGoodsData *data);
	/*
		获得当前最大可购买量
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
