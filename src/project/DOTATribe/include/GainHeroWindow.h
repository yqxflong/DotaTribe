//Name : GainHeroWindow
//Function : ���Ӣ�۴���
//Author : lvyunlong
//Date: 20131206

#ifndef  _DOTATRIBE_GAINHEROWINDOW_H_
#define  _DOTATRIBE_GAINHEROWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CProgressTimer.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/IPopWindow.h"

class GainHeroWindow : public IWindow 
	,public IPopWindow
	,public CProgressTimerDelegate
	, public CPriorityLayerColorDelegate
	,public AnimationEffectCallBackProtocol
{
private:
	enum{
			udPRIORITY = 0,
			udNEWHEROEFFECTNODE,
			udMAINBG,
			udHEROMASKNODE,
			udTITLE, 
			udSTARRANKTEXT,
			udHEROTYPE,
			udMOMENTUM,
			udLEADERSHIPTEXT,
			udLEADERSHIPVALUE,
			udSCHEDULEBG,
			udSCHEDULE,
			udCLICKCLOSETEXT,
			udHERONAME,
		};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pGHeroNode;
	GainHeroOrDebriData* m_pGainData;
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;//��������
	CProgressTimer *m_pProgress;	//�׼����������
	int m_CurViewHeroLV;
	bool m_isBGainBtn;
	bool m_isEffectTime;
public:
	GainHeroWindow();
	virtual ~GainHeroWindow();
	
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _setStarRank();
	inline void _setHeroType(int type);
	inline void _setShowHeroDaiji(int heroid);
	inline void _initProgressTimer();
	inline void _setProgress(GainHeroOrDebriData* pData);
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

	//��ʾ����
	virtual void ShowPopWindow();
	//�����Ѿ�����
	virtual void PopWindowDidHide();
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		��ʾ���Ӣ������¼�����	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	void ShowWindow();
	/*
		���ػ��Ӣ������¼�����	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);

public:
	void On_Click_Enevnt(cocos2d::CCObject* pSender);
public:
	/*
		Ӣ�۵ȼ��Ļص�
	*/
	void CallbackTTF();
	/*
		��ť�Ƿ�ɰ�
	*/
	void CallbackBtnEnable();
	/*
		�ж��Ƿ�������Ӣ��
	*/
	void StarRankShow();
public:
	virtual void CallBack_NextLevel();
	virtual void CallBack_RunFinish();
public:
	/*
		AnimationEffectCallBackProtocol Delegate
	*/
	virtual void EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

};


#endif