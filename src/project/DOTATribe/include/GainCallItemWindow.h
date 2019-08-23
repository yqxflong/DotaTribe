//Name : GainCallItemWindow
//Function : ����ٻ���Ʒ����
//Author : lvyunlong
//Date: 20140522

#ifndef  _DOTATRIBE_GAINCALLITEMWINDOW_H_
#define  _DOTATRIBE_GAINCALLITEMWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/IPopWindow.h"
class GainCallItemWindow : public IWindow, public CPriorityLayerColorDelegate,public IPopWindow
{
private:
	enum{
			udPRIORITY = 0,
			udMAINBG,
			udTITLE,
			udDTAWARDBOARD,
			udCLOSETTF,
			udTITLE1,
			udEFFECT,
			udNAME,
		};
	cocos2d::CCNode* m_pRoot;
	GainHeroOrDebriData* m_pGainData;
public:
	GainCallItemWindow();
	virtual ~GainCallItemWindow();
	
private:
	inline void _initLayout();

	inline void _initControl();

	inline void _setInfoData();
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
};


#endif