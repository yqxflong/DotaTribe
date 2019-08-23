//Name : GainSoulDebriWindow
//Function : ��������Ƭ����
//Author : lvyunlong
//Date: 20131208

#ifndef  _DOTATRIBE_GAINSOULDEBRIWINDOW_H_
#define  _DOTATRIBE_GAINSOULDEBRIWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/IPopWindow.h"
class GainSoulDebriWindow : public IWindow, public CPriorityLayerColorDelegate,public AnimationEffectCallBackProtocol,public IPopWindow
{
private:
	enum{
			udPRIORITY = 0,
			udMAINBG,
			udHEROMASKNODE,
			udHEROMASKNODE1,
			udTITLE, 
			udSTARRANKTEXT,
			udHEROTYPE,
			udDESCRIBE,
			udCHANGEDESCRIBE,
			udSURETEXT,
			udHERONAME,
		};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pGSoulNode;
	GainHeroOrDebriData* m_pGainData;
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;//��������
	bool m_isTouch;
public:
	GainSoulDebriWindow();
	virtual ~GainSoulDebriWindow();
	
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setStarRank();
	inline void _setHeroType(int type);
	inline void _setShowHeroDaiji(int heroid);
	inline void _setText();
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

	void ShowWindow();
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
	/*
		���ػ��Ӣ������¼�����	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
public:
	/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);

	/*
		AnimationEffectCallBackProtocol Delegate
	*/
	virtual void EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

};


#endif