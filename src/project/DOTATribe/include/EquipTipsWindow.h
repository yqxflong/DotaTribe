// Name :EquipTipsWindow.h
// Function：装备物品tips窗口
// Author : lvyunlong
// Date: 20131016

#ifndef  _DOTATRIBE_EQUIPTIPSWINDOW_H_
#define  _DOTATRIBE_EQUIPTIPSWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/BagEquipDataHandler.h"


enum{
	kTIPS_BAGEQUIP=0,	//装备列表中的装备类型
	kTIPS_ROLEEQUIP,	//已装备的装备类型
	kTIPS_OTHEREQUIP,	//查看其他玩家的装备
};



class EquipTipsWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum
	{
		udMASKCCP,	  //遮罩层
		udNodeCompareEquiped,		//已装备结点
		udNodeCheckCurEquip,		//点击装备
		udNodeOtherEquip,			//其他玩家装备结点
		udMaskNode,			//
	};

	enum{
		udBG = 0,	//背景
		udName,		//名字
		udEquiptype,
		udEQUIPBOAD,
		udEBASIC,
		udEBVALUE,
		udPRICEVALUE,
		udPRICEICON,
		udEATTACH1,
		udEATTACH1VALUE,
		udEATTACH2,
		udEATTACH2VALUE,
		udEATTACH3,
		udEATTACH3VALUE,
		udEATTACH4,
		udEATTACH4VALUE,
		udEQUIPED,
		udPRICETEXT,
	}EQUIPED;
	
	enum{
		EudBG = 0,	//背景
		EudName,	//名字
		EudEquiptype,
		EudEQUIPBOAD,
		EudEBASIC,
		EudEBVALUE,
		EudPRICEVALUE,
		EudPRICEICON,
		EudEATTACH1,
		EudEATTACH1VALUE,
		EudEATTACH2,
		EudEATTACH2VALUE,
		EudEATTACH3,
		EudEATTACH3VALUE,
		EudEATTACH4,
		EudEATTACH4VALUE,
		EudSELLBTN,
		EudSELLLB,
		EudEQUIPBTN,
		EudEQUIPBTNLB,
		EudDISBOARDBTN,
		EudDISBOARDLB,
		EudCLOSEBTN,
		EudPRICETEXT,
	}EQUIP;

	cocos2d::CCNode* m_pRoot;//窗口根节点

	cocos2d::CCNode* m_pCompareNode;
	cocos2d::CCNode* m_pCheckNode;
	cocos2d::CCNode* m_pOtherNode;
	int m_idx;
	int m_isEquiped;
	int m_nHeroPos;
	//这个是对比的
	std::map<int,int> m_ComparemapAttribute;
	std::map<int,int> m_ComparemapAttributeMAX;
	int m_nCompareMainAttribute;
	int m_nCompareMainAttributeMax;

	//点击的
	std::map<int,int> m_mapAttribute;
	std::map<int,int> m_mapAttributeMAX;
	int m_nMainAttribute;
	int m_nMainAttributeMax;
	int m_nEquipID;

	BagEquipData *m_NeedEquipData;

public:
	void _fillLocalAtrributeMap(BagEquipData* dd,bool isCompare);
	void _createLabels(BagEquipData* dd,bool isCompare);

public:
	/*
		调整文字位置 
	*/
	void _createNAME(BagEquipData* data,bool isCompare);
	void _createPrice(BagEquipData* data,bool isCompare);
	void _createEquiptype(BagEquipData* data,bool isCompare);
	void _createEquipInfo(BagEquipData* data,bool isCompare);
	void _createBASIC(BagEquipData* data,bool isCompare);
	void _createBASICVALUE(BagEquipData* data,bool isCompare);
	
	inline void _createATT(int key,int udEnum,bool isCompare);
	inline void _createATTValue(int key,int val,int udEnum,bool isCompare);
	void _setColorATTValue(int curval,int maxval,CCLabelTTF* ttf);
public:
	EquipTipsWindow();
	virtual ~EquipTipsWindow();

private:
	inline void _initLayout();
	/*
		初始化控件
	*/
	inline void _initControl();

	void _createLabel();
	
	void _mapBtn();
	
	inline void _initCompareEquipedNode(BagEquipData* data,bool isCompare = true);

	inline void _initCheckEquipNode(BagEquipData* data,bool isCompare = false);

	inline void _initOtherEquipNode(BagEquipData* data,bool isCompare = false);

	inline void _copyBagEquipdata(BagEquipData*& data, BagEquipData* dd);
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
	show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		显示装备信息
	*/
	void _refreshQeuipInfo();
	/*
		显示装备对比Tip
	*/
	void ShowEquipCompare(BagEquipData* equiped,BagEquipData* dd);
	/*
		单个显示装备Tip
	*/
	void ShowEquip(BagEquipData* dd);
	/*
		查看其他玩家装备TIP
	*/
	void ShowEquipOthers(BagEquipData* dd);
		/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);

	/*
		出售按钮
	*/
	void On_Check_Sell_Event(cocos2d::CCObject* pSender);
	/*
		装备按钮
	*/
	void On_Check_Equip_Event(cocos2d::CCObject* pSender);
	/*
		关闭按钮
	*/
	void On_Check_Close_Event(cocos2d::CCObject* pSender);

	/*
		卸下按钮
	*/
	void On_Check_Disboard_Event(cocos2d::CCObject* pSender);
};


#endif
