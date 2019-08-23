// Name :		HelpWindow.h
// Function:	°ïÖú´°¿Ú
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_HELPWINDOW_H_
#define  _DOTATRIBE_HELPWINDOW_H_


#include "IWindow.h"
#include "../include/CPriorityLayerColor.h"
class HelpWindow : public IWindow,public CPriorityLayerColorDelegate
{
public:
	HelpWindow();
	virtual ~HelpWindow();
	enum{
		Help_UnKnow,
		Help_MarkLayer,

	};

	void InitLayer();
public:
	CPriorityLayerColor* m_SmallLayer;
	int m_WindowLabel;
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
public:

	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
	virtual	void	touchEvent(CPriorityLayerColor* pLayerColor);
	void On_Close(cocos2d::CCObject* pSender);

private:

	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
};


#endif
