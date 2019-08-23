// Name :CheckLeadershipWindow
// Function���鿴ͳ��������
// Author : lvyunlong
// Date: 20131223

#ifndef  _DOTATRIBE_CHECKLEADERSHIPWINDOW_H_
#define  _DOTATRIBE_CHECKLEADERSHIPWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/RoleInfoDataHandler.h"
class CheckLeadershipWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum{
		udPRIORITYLAYER,
		udMAINBG,
		udCLOSEBTN,
		udCURLEADERTEXT,
		udCURLEADERVALUE,
		udCURHEROLVTEXT,
		udCURHEROLVVALUE,
		udBASEHPTEXT,
		udBASEHPVALUE,
		udBASEMPTEXT,
		udBASEMPVALUE,
		udBASEATTACKTEXT,
		udBASEATTACKVALUE,
	};

private:
	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�
public:
	CheckLeadershipWindow();
	virtual ~CheckLeadershipWindow();

private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _initValue(RoleInfoData* data);
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
		�ڸǲ�ص�
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		�رս���
	*/
	void On_Close_Event(cocos2d::CCObject* pSender);
};


#endif
