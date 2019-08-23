//Name��HomeWindow
//Function����������ͨ�����������ıؾ�֮·
//Written By����ǿ
//Modify By:liqian
//Time:2013-08-29
#ifndef  _DOTATRIBE_HOMEWINDOW_H_
#define  _DOTATRIBE_HOMEWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/RollingBoard.h"
using namespace cocos2d;
using namespace cocos2d::extension;


class CMapScrollView;
class HomeWindow : public IWindow,public cocos2d::CCIMEDelegate 
{
private:
	float m_fTick_quickout_hint;
	const static float TIME_SHOWHINT_QUICKOUT;
	bool m_bIsShowHint_quickout;
	int building_status[8];	//8����ʾnew�Ľ�����״̬����


	RollingBoard * roll;
	RollingBoard * roll1;
	RollingBoard * roll2;
	RollingBoard * roll3;
	RollingBoard * roll4;
	RollingBoard * roll5;
public:
	HomeWindow();
	virtual ~HomeWindow();

	enum{
		udMAPSCROLL,	//��ͼ������
		udROLEINFO,//����
		udBAG,//����
		udSMELT,//ǿ��
 		udFRIEND,//����
		udSYSTEM,//ϵͳ
		udOUT,//���ٳ���
    	udPAYPRESENT,//��ֵ���
		udMARKET,//�̳�
		udLUATEST,			//Lua����
		udBOSSSCORE,	//����boss
		udZHENGSHOU,	//����
		udEMAIL,//����
		udVIP,		//vip
		udLIMITEDACTIVITY,	//��ʱ�
		udACTIVITY,		//�
		udMOREBTN,//���ఴť
		udAWARDNOTICE_EFFECT,//����������Ч
		udACTIVITY_EFFECT,//���ʻ��Ч
		udVIPREWARD_EFFECT,//���ʻ��Ч
		udBOSS_EFFECT,//Boss��Ч
		udOUTTITLE,	//���ٽ��븱����������
		udVIPLEVELTEXT,			//��ǰVIp�ȼ�����
		udCOLLECTIONCORNER,				//���սǱ�
		udEMAILCORNER,					//����Ǳ�
		udFRIENDCORNER,					//���ѽǱ�
		udBOSSCORNER,					//boss���ֽǱ�
		udBOTTOM_BAR_DECORATION,	//�ײ�����
		udOUT_HINT,//���ٳ�����ʾ
		udOUT_EXP_DOUBLE_HINT,	//˫��������ʾ
		udSTRENTHEN_HINT_1,	//ǿ����ʾ��չ��
		udSTRENTHEN_HINT_2,	//ǿ����ʾ���ر�
		udSTRENTHEN_HINT_NODE,	//ǿ����ʾռλ���洢during��dis
		//
		udSTRENTHEN_HINT_1_NODE=1000,		//ǿ��1�ڵ�
		udSTRENTHEN_HINT_2_NODE,			//ǿ��2�ڵ�
	}kHomeWindow;

	enum{
		udHOMEMAP_1,//��ͼ1
		udHOMEMAP_2,//��ͼ2���ӵ�ͼ1
		udBAR,//�ư�
		udDOOR,//����
		udHOME,//�Ǳ�
		udSHOP,//��������
		udPKPLACE,//������
		udTDOOR,//Զ���ż�
		udTOWER,//����֮��
		udMINERALHOLE,//��
		udBAR_FILE_NODE,//�ƹ��ļ��洢�ڵ�
		udDOOR_FILE_NODE,//�����ļ��洢�ڵ�
		udHOME_FILE_NODE,//�Ǳ��ļ��洢�ڵ�
		udSHOP_FILE_NODE,//���������ļ��洢�ڵ�
		udPKPLACE_FILE_NODE,//�������ļ��洢�ڵ�
		udTDOOR_FILE_NODE,//Զ���ż��ļ��洢�ڵ�
		udTOWER_FILE_NODE,//����֮���ļ��洢�ڵ�
		udMINERALHOLE_FILE_NODE,//���ļ��洢�ڵ�
		udBARTXTBG,//�ưɱ��ⱳ��
		udDOORTXTBG,//���ű��ⱳ��
		udHOMETXTBG,//�Ǳ����ⱳ��
		udMARKETTXTBG,//���б��ⱳ��
		udPKPLACETXTBG,//���������ⱳ��
		udTDOORTXTBG,//����֮�ű��ⱳ��
		udTOWERTXTBG, //�����ⱳ��
		udMINERALBG,	//�󶴱��ⱳ��
		udBARTXT,//�ưɱ���
		udDOORTXT,//���ű���
		udHOMETXT,//�Ǳ�����
		udMAKETTXT,//���б���
		udPKPLACETXT,//����������
		udTDOORTXT,//����֮�ű���
		udTOWERTXT,//xx���������
		udMINERALTXT,//�󶴱���
		udBUSSINESSMAN,	//����ռλ�ڵ�
		udSE_TEMPLE_1,//��ɫ�����==����
		udSE_TEMPLE_2,//��ɫ�����==����
		udSE_TEMPLE_3,//��ɫ�����==����
		udSE_TEMPLE_4,//��ɫ�����==����
		udSE_MAP_1,//��ɫС����
		udSE_MAP_2,//��ɫС����
		udSE_MAP_3,//��ɫС����
		udSE_MAP_4,//��ɫС����
		udSE_MINERAL,//����Ч==��
		udSE_BAR,//BAR��Ч==�ƹ�
		udSE_TEAMPVE,//�ż���Ч
		udSE_TEAMPVE_2,	//�ż�����
		udSE_MARKET_1,//��������
		udSE_MARKET_2,//�����
		udSE_MAP_5,//��������
		udSE_PVP,//����������
		udICON_NEW,//�����ϵ�new����
		udICON_MINERALEMPTYHINT,//�󶴿��е�����
		udMINERALEMPTY_HINT_NODE,	//�󶴿���ռλ���洢during��dis
		udICON_FREESUPPLI,//�����Ը����
		udICON_FREESUMMON,//����ٻ�����
		udICON_REFRESHSHOP,//��ˢ������
		//
		udREALBUSSINESSMAN=1000,		//����������
		udNEW_HEROBAR,					//��̳����
		udNEW_AREANA,					//����������
		udNEW_MINERAL,					//�ʹӿ���
		udNEW_HEROTECH,					//�Ƽ�����
		udNEW_TOWER,					//����
		udNEW_TEAMBATTLE,				//��Ӹ���
		udHINT_MINERALEMPTY,			//�󶴿��нڵ�
		udHINT_FREESUPPLI,				//�����Ը�ڵ�
		udHINT_FREESUMMON,				//����ٻ��ڵ�
		udHINT_REFRESHSHOP,				//�̵�ˢ�½ڵ�
	}kHomeMap;

	CCNode* m_pRoot;					//�����ڵ�
	cocos2d::CCMenu* m_pRootMenu;		//���฽�Ӱ�ť��menu
	CMapScrollView* m_pMapScroll;		//������ͼ������
	//=======================��ͷ����=================================
	cocos2d::extension::CCSkeletonAnimation* m_pArrow_Collection;	//����ͷ
	cocos2d::extension::CCSkeletonAnimation* m_pArrow_QuickOut;		//���ٳ��Ǽ�ͷ
	//
	std::vector<cocos2d::CCPoint*> m_vecMoreitemPos;   //��¼����More��items
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

	//���MoreItems��ǰ״̬
	void checkMoreItems();

	//open morebtn
	void openMoreBtn(bool isaction);

	//close morebtn
	void closeMoreBtn(bool isaction);

	//show items
	void showMoreItems();
	//hide items
	void hideMoreItems();

	//show items
	void showMoreItems_normal();
	//hide items
	void hideMoreItems_normal();

	//��ʾ����
	inline void _showBottomBar(bool isshow);
	/*
		��鹦�ܽ������
	*/
	void CheckFunctionLock();
	/*
		�����ʾ��Ϣ
	*/
	void CheckAllHint();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		��ʾ��������¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
private:
	inline void _initLayout();
	inline void _SetHomeMap();
	inline void _createBusinessMan();
	inline void _initStrengthenHint();
	inline void _initMineralEmptyHint();
	inline void _initFreeSuppliHint();
	inline void _initFreeSummonHint();
	inline void _initRefreshShopHint();
	inline void _mapBtn();
	inline void _mapGlodBg();
	inline void _mapMoreItems();
	inline void _mapRoleInfoItem();
	inline void _mapBagItem();
	inline void _mapSkillItem();
	inline void _mapStrengthenItem();
	inline void _mapFriendItem();
	inline void _mapSystemItem();

	/*
		���ÿ��ٳ���
	*/
	void _setQuickOut();
	/*
		���ÿ��ٽ��븱����������
	*/
	void _setOutProgress();
	/*	
		��齨���������
	*/
	void _checkBuildingLock();
	/*	
		����̳�������
	*/
	void _checkBuildingLock_HeroBar();
	/*	
		�����н������
	*/
	void _checkBuildingLock_Market();
	/*	
		��龺�����������
	*/
	inline void _checkBuildingLock_PkPlace();
	/*	
		��������������
	*/
	inline void _checkBuildingLock_Tower();
	/*	
		�����Ӹ����������
	*/
	inline void _checkBuildingLock_TeamPVE();
	/*	
		���Ǳ��������
	*/
	inline void _checkBuildingLock_HomeTown();
	/*
		����ʹӽ������
	*/
	inline void _checkBuildingLock_Labor();
	/*
		��鸡����ť�������
	*/
	inline void _checkHangupItemLock();
	/*
		�������������
	*/
	inline void _checkHangupItemLock_Email();
	/*
		������ս������
	*/
	inline void _checkHangupItemLock_Collect();

	/*
		�������Boss�������
	*/
	void _checkHangupItemLock_Boss();

	/*
		���������������������
	*/
	void _checkOtherLock();

	/*
		���������������������_��֮Ѱ��
	*/
	void _checkOtherLock_Labor();

	/*
		���������������������_���ɼ�
	*/
	void _checkOtherLock_GoldMine_();
	/*
		����vip�ȼ�
	*/
	void _updateVipNum();

	//===========״̬��==============
	inline void _heroIllustrateEvent();
	inline void _skillEvent();
	inline void _moreEvent();
	inline void _bagEvent();
	inline void _strengthenEvent();
	inline void _friendEvent();
	inline void _systemEvent();
	inline void _outEvent();
	inline void _paypresentEvent();
	inline void _zhengshouEvent();
	inline void _shopEvent();
	inline void _emailEvent();
	inline void _limitedActivityEvent();
	inline void _activityEvent();
	inline void _vipEvent();
	//=========�����¼�=========
	inline void _barEvent();
	inline void _doorEvent();
	inline void _homeEvent();
	inline void _marketEvent();
	inline void _luaEvent();
	inline void _bossEvent();
	inline void _pkPlaceEvent();
	inline void _tdoorEvent();
	inline void _towerEvent();
	inline void _mineralhole();

	//��齨����� �Ƿ�����
	bool _buildingCheckOpened(int key);

	//����ָ��������Ч
	void _enableBuildingEffect(int key,bool opened);

	//��齨����ʾ
	void _buildingCheckHint(int key,bool opened);

	//��齨������ָ��
	void _buildingCheckNewOpen(int key);


	//��齨����չʾ״̬
	void _buildingCheckDisplay(int key,bool opened);


	/*
		��ʾ��װ������ǿ��
	*/
	void _showStrengthenHint();

	/*
		���ٳ���˫��������ʾ
	*/
	void _showQuickOutHint_DoubleExp();

	/*
		��ʾ������Boss �
	*/
	void _showBossHint();
	/*
		��ʾ������ٻ�
	*/
	void _showFreeSummonHint();
	/*
		��ʾ�������Ը
	*/
	void _showFreeSupplicaHint();
	/*
		��ʾ��ˢ���̵�
	*/
	void _showRefreshShopHint();

	/*
		��ʾ�п���ǿյ�
	*/
	void _showMineralEmptyHint();

	/*
		��ʾ���ٳ���
	*/
	bool _showQuickOutHint();
	/*
		���ؿ��ٳ�����ʾ
	*/
	void _hideQuickOutHint();
	/*
		��ʾ���������н���
	*/
	void checkAwardNoticeHint();
	/*
		��ʾ���ʻ�н���
	*/
	void checkAwardActivityHint();
	/*
		��ʾVIP�н���
	*/
	void checkAwardVipHint();
	/*
		��������Ǳ꣺��ʾδ��ɵ�����
	*/
	void setTaskCorner();
	/*
		�������սǱ꣺��ʾ�ܿ����մ���
	*/
	void setCollectionCorner();
	/*
		��������Ǳ꣺��ʾδ������
	*/
	void setEmailCorner();
	/*
		���ú��ѽǱ꣺��ʾ������ѵ�����
	*/
	void setFriendCorner();
	/*
		����boss���ֽǱ꣺��ʾBoss������Ѵ���
	*/
	void setBossScoreCorner();

	/*
		����ˢ��UI�¼�
	*/
	static void Event_RefreshUI_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
	/*
		���մ�More���¼�
	*/
	static void Event_ShowMoreItems_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);

	//ע���¼�
	inline void _registerRefreshEvent();
	inline void _unregisterRefreshEvent();


	/*
		��ʾnew������ָ������
	*/
	void _showNewFlowICon4Building(int ModuleID);
	/*
		����new����by����
	*/
	inline void _createFlowNewICon(const CCPoint &cp,int key);

	/*
		����ͼ�ƶ������ұ�
	*/
	void _moveMapToRightBottom();
	/*
		����ͼ�ƶ��������
	*/
	void _moveMapToLeftTop();

	//===========================��ͷ��ȫ============================
	/*
		��ʾ����ͷ
	*/
	void _showArrow_Collection();
	/*
		���ٵ���ͷ
	*/
	void _hideArrow_Collection();
	/*
		��ʾ���ٳ��Ǽ�ͷ
	*/
	void _showArrow_QuickOut();
	/*
		���ٿ��ٳ��Ǽ�ͷ
	*/
	void _hideArrow_QuickOut();
public:
	/*
		������ť�ĵ���¼�
	*/
	void On_Click_BtnClick(cocos2d::CCObject* pSender);
	/*
		�������Ͻ����ĵ���¼�
	*/
	void On_Click_Event_MainBG(cocos2d::CCObject* pSender);
};

#endif
