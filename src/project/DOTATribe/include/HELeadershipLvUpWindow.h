//Name：HELeadershipLvUpWindow
//Function：领导力升级弹窗
//Written By：尹强

#ifndef  _DOTATRIBE_HELeadershipLvUpWindow_H_
#define  _DOTATRIBE_HELeadershipLvUpWindow_H_

#include "IWindow.h"
#include "../include/IPopWindow.h"


class HELeadershipLvUpWindow : public IWindow,public IPopWindow
{
private:
	enum{
		kGRAYLAYER,
		kBOXBG,
		kBTN,
		kBTN_LABEL,
		kHINT,
		kHEROLVTEXT,
		kHEROLV_BASE,
		kHEROLV_NEW,
		kIMPROVETEXT1,
		kIMPROVE1_BASE,
		kIMPROVE1_NEW,
		kIMPROVETEXT2,
		kIMPROVE2_BASE,
		kIMPROVE2_NEW,
		kIMPROVETEXT3,
		kIMPROVE3_BASE,
		kIMPROVE3_NEW,
		kARROW1,
		kARROW2,
		kARROW3,
		kARROW4,
	};
	cocos2d::CCNode* m_pRootLayer;
public:
	HELeadershipLvUpWindow();
	virtual ~HELeadershipLvUpWindow(){};
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _setContent();
	//
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


	//需要子类继承并重写
	virtual void ShowPopWindow();
	virtual void PopWindowDidHide();
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
		展示自己的窗口
	*/
	void ShowWindow();
private:
	/*
		按钮事件
	*/
	void   On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
