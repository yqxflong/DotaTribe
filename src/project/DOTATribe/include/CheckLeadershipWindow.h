// Name :CheckLeadershipWindow
// Function：查看统率力窗口
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
	cocos2d::CCNode* m_pRoot;//窗口根节点
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
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		遮盖层回调
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		关闭界面
	*/
	void On_Close_Event(cocos2d::CCObject* pSender);
};


#endif
