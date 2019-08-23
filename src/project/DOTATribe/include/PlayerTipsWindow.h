//Name��PlayerTipsWindow
//Function����Һ���tips
//Written By������
//Maintainer:  zhoushaonan, shaobing
//Time:2013-9-18

#ifndef  _DOTATRIBE_PLAYERTIPSWINDOW_H_
#define  _DOTATRIBE_PLAYERTIPSWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/FontStyleDataManager.h"
#include "../include/DTEquipBoard.h"

class PlayerTipsWindow : public IWindow,public CPriorityLayerColorDelegate,public DTEquipBoardDelegate
{
private:
	enum{
		MASKCCP = 0,			//���ֲ�
		MASKSMALL,				//���ֲ㣨С��
		udBG,					//����
		udCLOSEBTN,				//�رհ�ť
		udSKELETONNODE,			//�����������
		udPLAYERNAME,			//�������
		udLVVALUE,				//�ȼ�ֵ
		udABILITYVALUE,			//ս��ֵ
		udHP,					//HP
		udHPVALUE,				//HPֵ
		udMP,					//MP
		udMPVALUE,				//MPֵ
		udATTACK,				//����
		udATTACKVALUE,			//����ֵ
		udSPEED,				//�ٶ�
		udSPEEDVALUE,			//�ٶ�ֵ
		udHIT,					//����
		udHITVALUE,				//����ֵ
		udSUNDER,				//�Ƽ�
		udSUNDERVALUE,			//�Ƽ�ֵ
		udGRIT,					//����
		udGRITVALUE,			//����ֵ
		udDODGE,				//Dodge����
	    udDODGEVALUE,			//����ֵ
		udARMOR,				//Armor����
		udARMORVALUE,			//����ֵ
		udTOUGHNESS,			//Toughness����
		udTOUGHNESSVALUE,		//����ֵ
		udLINELEFT,				//�ָ��ߣ���ࣩ
		udEQUIPTABBTN,			//װ��TAB��ť
		udSOULTABBTN,			//ս��TAB��ť
		udEQUIPTABBTNLABEL,		//װ��LABEL
		udSOULTABBTNLABEL,		//ս��LABEL
		udBOARD_1,				//����BOARD
		udBOARD_2,				//�·�BOARD
		udBOARD_3,				//��ָBOARD
		udBOARD_4,				//Ь��BOARD
		udBOARD_5,				//ʥ��BOARD
		udBOARD_6,				//����BOARD
		udBOARD_7,				//ͷ��BOARD
		udBOARD_8,				//��ƷBOARD
		udLINERIGHT_1,			//�ָ��ߣ���һ��
		udLINERIGHT_2,			//�ָ��ߣ��Ҷ���
		udSTR,					//����
		udSTRVALUE,				//����ֵ
		udAGI,					//����
		udAGIVALUE,				//����ֵ
		udINT,					//����
		udINTVALUE,				//����ֵ
		udSKILL_1,				//����1
		udSKILL_2,				//����2
		udSKILL_3,				//����3
		udSKILL_4,				//����4
		udSKILL_5,				//����5
		udSKILL_6,				//����6
		udSKILL_7,				//����7
		udSKILL_8,				//����8
		udADDFRIENDBTN,			//�Ӻ��Ѱ�ť
		udADDFRIENDLABEL,		//�Ӻ���LABEL
		udSOUL_1,				//Ӣ��1
		udSOUL_2,				//Ӣ��2
		udSOUL_3,				//Ӣ��3
		udSOUL_4,				//Ӣ��4
		udHERONAME,				//Ӣ����
		udSKILL_KUANG_1,		//����1���
		udSKILL_KUANG_2,		//����2���
		udSKILL_KUANG_3,		//����3���
		udSKILL_KUANG_4,		//����4���
		udSKILL_KUANG_5,		//����5���
		udSKILL_KUANG_6,		//����6���
		udSKILL_KUANG_7,		//����7���
		udSKILL_KUANG_8,		//����8���
		udSTAR_DATA,			//�Ǽ�����


	};
	enum{
		_kTAB1_,
		_kTAB2_
	};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pNode;
;public:
	PlayerTipsWindow();
	virtual ~PlayerTipsWindow();
	void On_Close(cocos2d::CCObject* pSender);
	void On_AddFriend(cocos2d::CCObject* pSender);

private:
	/*
		_initLayout
	*/
	inline void _initLayout();
	/*
		_initData. ���ñ�ǩҳ����ť��
	*/
	inline void _initData();
	/*
		_setMask, �������ֲ�
	*/
	inline void _setMask();
	/*
		_createSkeleton������Ӣ�۹������� 
	*/
	inline void _createSkeleton();
	/*
		_setInfo�����þ�����Ϣ
	*/	
	inline void _setInfo();
	/*
		_setEquipInfo������װ����Ϣ
	*/
	inline void _setEquipInfo();
	/*
		_setSkillInfo�����ü�����Ϣ
	*/
	inline void _setSkillInfo();
	/*
		_setSoulInfo������ս����Ϣ
	*/
	inline void _setSoulInfo();
	/*
		_setStarts����������
	*/
	inline void _setStars();

	inline void _setTTFText(int key, const char * text);
	inline void _setTTFText(int key, int text);

	/*
		ѡ���ǩҳCallBack
	*/
	inline void On_TabSelected(cocos2d::CCObject* pSender);

	int currentTab;	//��ǰ��ǩҳ, kTab1, kTab2

private:
	CMenuItemSprite* m_equipTabItem;	//Equip Tab
	CMenuItemSprite* m_soulTabItem;		//Soul Tab
	CCLabelTTF*	m_equipTabLabel;		//Equip Tab Label
	CCLabelTTF* m_soulTabLabel;			//Soul Tab Label
	FSData* m_selectedFont;				//Tab Selected Font
	FSData* m_unselectedFont;			//Tab Unselected Font
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

	//
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);

	void touchEvent(CPriorityLayerColor* pLayerColor);

	/*
		���װ��ͼ��CallBack 
	*/
	virtual void CallBack_ClickEquip(int type, int equipId);
	/*
		���ս��ͼ��CallBack
	*/
	void OnSoulIconClick(cocos2d::CCObject* pSender);
};


#endif
