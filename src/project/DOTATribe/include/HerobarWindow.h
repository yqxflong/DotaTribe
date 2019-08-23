//Name��Ӣ���ٻ�����
//Function��Ӣ���ٻ����
//Written By��������
//Date��20131205

#ifndef  _DOTATRIBE_HEROBARWINDOW_H_
#define  _DOTATRIBE_HEROBARWINDOW_H_


#include "../include/IWindow.h"
#include <string>
#include "cocos-ext.h"
#include "../include/MaskNode.h"
class HerobarWindow : public IWindow
{
private:
	enum
	{
		udMAINBG,
		udPRIORITYLAYER,
		udSCENEEFFECT,
		udTITLETEXTBG,
		udTITLETEXT,
		udQUICKCITYBTN,
		udHEROALTARBTN,
		udHEROBASEBTN1,
		udHEROBASEBTN2,
		udHEROBASEBTN3,
		udSUMMONHALLICON1,
		udSUMMONHALLICON2,
		udSUMMONHALLICON3,
		udHAVESOULNUM,
		udFREEELITECALLTTF,
		udFREEHOLYCALLTTF,
		udSOULSTORNICON1,
		udSOULSTORNICON2,
		udSOULSTORNICON3,
		udSOULNEEDCOUNTTTF1,
		udSOULNEEDCOUNTTTF2,
		udSOULNEEDCOUNTTTF3,
		udELITETIMELTTF,
		udHOLYTIMETTF,
		udHEROLISTBTN,
		udHEROLISTTEXT,
		udCURSOULTEXT,
		udSUMMONNOTICETTF,
		udCALLEXPLAIN1,
		udCALLEXPLAIN2,
		udCALLEXPLAIN3,
		udCALLEXPLAINSTAR1,
		udCALLEXPLAINSTAR2,
		udCALLEXPLAINSTAR3,
		udCALLTITLE1,
		udCALLTITLE2,
		udCALLTITLE3,
		udJEWELFRAME,
		udJEWELICON,
		udJEWELCOUNT,
		udHOLYNODE,
		udJIANTOUMOVE,
	};
	enum{
		udHOLYGRAYLAYER,
		udHOLYBG,
		udHOLYTITLEBG,
		udHOLYCALLONETTF,
		udHOLYCALLTENTTF,
		udHOLYCALLONEBTN,
		udHOLYCALLTENBTN,
		udHOLYEXPLAIN1,
		udHOLYEXPLAIN2,
		udHOLYFREETTTF,
		udHOLYJEWELICON,
		udHOLYTENCALLMONET,
		udHOLYONEMONEYICON,
		udHOLYONEPRICETTF,
		udHOLYCLOSEBTN,
	};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pSummonNode;
	MaskNode* m_pHolyNode;
	std::string m_strLeftTime;
	cocos2d::extension::CCSkeletonAnimation* m_pArrow;  //�׳��ͷ
public:
	HerobarWindow();
	virtual ~HerobarWindow();
public:
	long long  m_iPreelitetime;	//ǰһ����Ӣʱ��
	long long  m_iPreHolytime;		//ǰһ����ʥʱ��
	unsigned char m_isFreeElite;
	unsigned char m_isFreeHoly;
	bool m_isBTick;
	bool m_isShowHolyNode;
public:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setNeedSoulCount();
	inline void _leftHolytime();
	inline void LeftTimeUpdate(cocos2d::CCNode* node,int time,int key);
	void initHolyNode();
	void _mapHolyBtn();
	void showHolyoneMoney(bool type);
	void setFreeElite(bool isfree);
	void setFreeHoly(bool isfree);
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
		��ʾӢ���ٻ�����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		����Ӣ���ٻ�����¼�����
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);

	/*
		����Ӣ���ٻ�����¼�����
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);
private:
	/*
		ˢ�����ʯ�¼�
	*/
	void refreshSoulStoneUIData();
public:
	void On_Click_Summon_Event(cocos2d::CCObject* pSender);
	void On_Click_Event(cocos2d::CCObject* pSender);
	void On_Click_HallBtn_Event(cocos2d::CCObject* pSender);
public:
	void On_Click_HolyBtn(cocos2d::CCObject* pSender);
	void On_Click_Holy_CloseBtn(cocos2d::CCObject* pSender);
};


#endif
