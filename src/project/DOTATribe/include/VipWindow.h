// Name : VipWindow.h
// Function:Vip窗口
// Author : lvyunlong
// Date: 20131125

#ifndef  _DOTATRIBE_VIPWINDOW_H_
#define  _DOTATRIBE_VIPWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
#include "../include/CTableView.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class VipWindow : public IWindow
{
private:
	enum{
		udPRIORITYLAYERBIG = 0,
		udSCENEEFFECT,
		udFRAMEBG,
		udMAINBG,
		udVIPLOGOICON,
		udVIPLOGOLEVELTEXT,
		udCURVIPLEVELTEXT,
		udPAYLATERVIPLEVELTEXT,
		udVIPEXPTEXT,
		udVIPEXPBG,
		udVIPEXPPROGRESS,
		udPRIVILEGETEXTBG,
		udPRIVILEGETEXT,		
		udCLOSEBTN,
		udVIPREWARDBTN,
		udVIPREWARDBTNTEXT,
		udLEFTBTN,
		udRIGHTBTN,
		udCURPAGEBG,
		udCURPAGETEXT,
		udIMMEDIATELYPAYBTN,
		udEFFECT1,
		udIMMEDIATELYPAYTEXT,
		udSECROLLVIEW,
		udPRIORITYlAYER,

		Box_VIPBG,
		Box_NAMETTF,
		Box_GIFTBOXBTN,
		Box_GIFTBOXBG1,
		Box_GIFTBOXICON,
		Box_COSTPRICE,
		Box_COSTPRICEICON,
		Box_COSTMONEY,
		Box_COSTMONEYBG,
		Box_OFFERPRICE,
		Box_OFFERPRICEICON,
		Box_OFFERMONEY,
		Box_OFFERMONEYBG,
		Box_BUYBTN,
		Box_BUYBTNTTF,
	};

	enum
	{
		udVIPFONTTTF0,
		udVIPFONTTTF1,
		udVIPFONTTTF2,
		udVIPFONTTTF3,
		udVIPFONTTTF4,
		udVIPFONTTTF5,
		udVIPFONTTTF6,
		udVIPFONTTTF7,
		udVIPFONTTTF8,
		udVIPFONTTTF9,
		udVIPFONTTTF10,
		udVIPFONTTTF11,
		udVIPFONTTTF12,
		udVIPFONTTTF13,
		udVIPFONTTTF14,
		udVIPFONTTTF15,
		udVIPFONTTTF16,
		udVIPFONTTTF17,
		udVIPFONTTTF18,
		udVIPFONTTTF19,
	};

	cocos2d::CCNode* m_pRoot;	  //当前窗口节点	
	cocos2d::CCNode* m_pVipNode;//充值Autococo节点
	cocos2d::CCLayer* m_Layerview;	//放在CCScrollView上的层
	CScrollView* m_ScrollView;		//
	int m_CurVipPage;				//当前vip页

public:
	VipWindow();
	virtual ~VipWindow();

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setText();
	inline void _setExp();
	inline void _setVipGift(int viplevel);
	inline void _showVipGift(bool visible);
public:
	void setFontAllVisble(bool isvisble = false);
	void SetfontByViplevel(int level);
	
public:
	virtual    bool    Init();

	virtual    bool    Load();

	virtual    void    Tick();

	virtual    void    Destroy();

public:
	/*
	消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示VIP面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏VIP面板事件处理
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新VIP面板事件处理
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新VIP礼包事件处理
	*/
	inline void  OnUpdateGiftWindowEventHandler(std::list<std::string>& paramList);
	/*
		QA是否购买礼包	
	*/
	inline void  OnBackQAWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_ColseBtn(cocos2d::CCObject* pSender);

	void On_Click_BtnClick(cocos2d::CCObject* pSender);

	void On_Click_Buy_Enevnt(cocos2d::CCObject* pSender);
	/*
		查看奖励按钮回调
	*/
	void On_CheckItem_Click(cocos2d::CCObject* pSender);
};

#endif
