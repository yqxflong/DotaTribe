// Name : HeroAltarWindow.h
// Function:Ӣ���׼�����
// Author : lvyunlong
// Date: 20131130

#ifndef  _DOTATRIBE_HEROALTARWINDOW_H_
#define  _DOTATRIBE_HEROALTARWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
#include "../include/HeroAltarControlDataHandler.h"
#include "../include/CTableView.h"
#include "../include/CProgressTimer.h"
#include "../include/CPriorityLayerColor.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class HeroAltarWindow : public IWindow ,public CProgressTimerDelegate, public CPriorityLayerColorDelegate
{
private:
	enum{
		udPRIORITYLAYER = 0,
		udSCENEEFFECT,
		udMAINBG,
		udBOTTOMBG,
		udTITLETEXTBG,
		udTITLETEXT,
		udQUICKCITYBTN,
		udHEROSUMMONBTN,
		udLEVELTEXTBG1,
		udLEVELTEXTBG2,
		udLEVELTEXTBG3,
		udLEVELTEXT1,
		udLEVELTEXT2,
		udLEVELTEXT3,
		udTOTEMTEXT1,
		udTOTEMTEXT2,
		udTOTEMTEXT3,
		udADDTEXT1,
		udADDTEXT2,
		udADDTEXT3,
		udSCHEDULEBG1,
		udSCHEDULEBG2,
		udSCHEDULEBG3,
		udSCHEDULE1,
		udSCHEDULE2,
		udSCHEDULE3,
		udMASKNODE1,
		udMASKNODE2,
		udMASKNODE3,
		udTOTEMICON1,
		udTOTEMICON2,
		udTOTEMICON3,
		udALTARBTN1,
		udALTARBTN2,
		udALTARBTN3,
		udALTARBTNTTF1,
		udALTARBTNTTF2,
		udALTARBTNTTF3,
	};

	enum
	{
		udVIEWPRIORITYBG,
		udVIEWMAINBG,
		udVIEWTITLETEXT,
		udVIEWTITLELEVELTEXT,
		udVIEWSUREBTN,
		udVIEWCANCELBTN,
		udVIEWSUREBTNTEXT,
		udVIEWCANCELBTNTEXT,
		udVIEWDEBRIS1,
		udVIEWDEBRIS2,
		udVIEWDEBRIS3,
		udVIEWDEBRIS4,
		udVIEWDEBRIS5,
		udVIEWDEBRIS6,
		udVIEWDEBRISCOUNTTTF1,
		udVIEWDEBRISCOUNTTTF2,
		udVIEWDEBRISCOUNTTTF3,
		udVIEWDEBRISCOUNTTTF4,
		udVIEWDEBRISCOUNTTTF5,
		udVIEWDEBRISCOUNTTTF6,
		udVIEWSCHEDULEBG1,
		udVIEWSCHEDULE1,
		udVIEWCURSTRENGTEXT,
		udVIEWNEXTSTRENGTEXT,
		udVIEWALTARTEXT,
	}DEBRISNODE;

	cocos2d::CCNode* m_pRoot;				//��ǰ���ڽڵ�	
	cocos2d::CCNode* m_pHAltarNode;			//�׼�Autococo�ڵ�
	cocos2d::CCNode* m_pDebrisNode;			//��Ƭ�׼��ڵ�
	int m_CurAltarType;						//��ǰ�׼�����
	CProgressTimer *m_pProgress;	//�׼����������
	int m_ViewHerolevel;					//Ӣ�����׼�����ȼ�
	int m_ViewHeroCurExp;					//Ӣ�����׼����澭��
	int m_ViewHeroLaterlevel;				//�����Ƭ����׼�����
	float mAlatrlaterPos;					//�׼����λ��
	bool m_isBAltarDebriBtn;				//����Ƭ��ť�Ƿ�ɰ�	
	int ArrTopNextValue[3];					//����֮���־
	int m_Soulstonetype;
public:
	HeroAltarWindow();
	virtual ~HeroAltarWindow();

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _mapViewBtn();
	inline void _setText();
	inline void _setExp();
	inline void _setBtnViable();
	inline void _initProgressTimer();
	void _setProgress(int expvalue);
	void _setJump();
public:
	void SetfontByViplevel(int level);
	void ShowDebrisView(int type);
	void CallbackTTF(int level);
	void CallbackBtnEnable();
	void setLevelTop();

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

public:
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
private:
	/*
		��ʾͼ������¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		����ͼ������¼�����
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		����ͼ������¼�����
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		�����׼���Ƭ����¼�����
	*/
	inline void OnUpdateDebrisWindowEventHandler(std::list<std::string>& paramList);
	/*
		�����׼�֮���������¼�����
	*/
	inline void OnUpdateOverWindowEventHandler(std::list<std::string>& paramList);
	/*
		�ص��׼�֮���Ƿ��׼�
	*/
	inline void OnCallBackWindowEventHandler(std::list<std::string>& paramList);
	/*
		����������ص�
	*/
	inline void OnInputWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_Event(cocos2d::CCObject* pSender);

	void On_Click_AltarBtn_Event(cocos2d::CCObject* pSender);

	void On_Click_DebrisBtn_Event(cocos2d::CCObject* pSender);

	void On_Click_DebrisView_Enevnt(cocos2d::CCObject* pSender);
public:
	virtual void CallBack_NextLevel();
	virtual void CallBack_RunFinish();
};

#endif
