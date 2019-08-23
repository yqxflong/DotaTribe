// Name :EquipTipsWindow.h
// Function��װ����Ʒtips����
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
	kTIPS_BAGEQUIP=0,	//װ���б��е�װ������
	kTIPS_ROLEEQUIP,	//��װ����װ������
	kTIPS_OTHEREQUIP,	//�鿴������ҵ�װ��
};



class EquipTipsWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum
	{
		udMASKCCP,	  //���ֲ�
		udNodeCompareEquiped,		//��װ�����
		udNodeCheckCurEquip,		//���װ��
		udNodeOtherEquip,			//�������װ�����
		udMaskNode,			//
	};

	enum{
		udBG = 0,	//����
		udName,		//����
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
		EudBG = 0,	//����
		EudName,	//����
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

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�

	cocos2d::CCNode* m_pCompareNode;
	cocos2d::CCNode* m_pCheckNode;
	cocos2d::CCNode* m_pOtherNode;
	int m_idx;
	int m_isEquiped;
	int m_nHeroPos;
	//����ǶԱȵ�
	std::map<int,int> m_ComparemapAttribute;
	std::map<int,int> m_ComparemapAttributeMAX;
	int m_nCompareMainAttribute;
	int m_nCompareMainAttributeMax;

	//�����
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
		��������λ�� 
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
		��ʼ���ؼ�
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
	��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
	show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		��ʾװ����Ϣ
	*/
	void _refreshQeuipInfo();
	/*
		��ʾװ���Ա�Tip
	*/
	void ShowEquipCompare(BagEquipData* equiped,BagEquipData* dd);
	/*
		������ʾװ��Tip
	*/
	void ShowEquip(BagEquipData* dd);
	/*
		�鿴�������װ��TIP
	*/
	void ShowEquipOthers(BagEquipData* dd);
		/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);

	/*
		���۰�ť
	*/
	void On_Check_Sell_Event(cocos2d::CCObject* pSender);
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
