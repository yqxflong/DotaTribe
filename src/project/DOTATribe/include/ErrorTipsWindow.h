#ifndef  _DOTATRIBE_ERRORTIPSWINDOW_H_
#define  _DOTATRIBE_ERRORTIPSWINDOW_H_
 
#include "IWindow.h"
#include "AutoFadeOutLable.h"

////////////////////////////////////////////////////////////////
//Name:	 ErrorTipsWindow
//Auchor: 	xiaobo.wu
//Func:	 弱提示窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
  
class   ErrorTipsData;

class ErrorTipsWindow : public IWindow
{
protected:  
	std::list<AutoFadeOutLabelManager *> m_ErrorTipsManagerList;
	ErrorTipsData *    m_pErrorTipsData;
	std::vector<std::string> m_vCacheContent;
	bool				m_bPauseLeapTips;
public:
	ErrorTipsWindow();
	virtual ~ErrorTipsWindow();

public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();

	/*
	清理所有动画
	*/
	void   DestroyAllAction();
	 

	cocos2d::CCNode *  GetErrorTipsRoorNode();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示Top面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新面板所有控件名称事件处理
	*/
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);

	/*
	ShowTipsWithString
	*/
	void  OnShowTipsContent(std::string tipsContent);

}; 

#endif // _DOTATRIBE_ERRORTIPSWINDOW_H

