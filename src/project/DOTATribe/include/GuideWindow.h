//Name：GuideWindow
//Function：新手引导窗口
//Written By：尹强

#ifndef  _DOTA_GUIDEWINDOW_H_
#define  _DOTA_GUIDEWINDOW_H_

#include "IWindow.h"
#include "../include/GuideDataManager.h"
#include "../include/CTimeLabel.h"
#include <cocos-ext.h>

class GuideWindow : public IWindow
	,public CTimerEventProtocol
{
private:
	enum{
		kARROW_NORMAL=1,
		kARROW_THUMB,
		kARROW_SMALL,
	};
	enum{
		kBOARD,
		kTEXT,
		kNPC,
		kMASK1,
		kMASK2,
		kMASK3,
		kMASK4,
		kSKIP,
		kTIMELABEL,
		kARROW,
	};
	cocos2d::CCNode* m_pRoot;
	cocos2d::extension::CCSkeletonAnimation* m_pArrow;
	cocos2d::CCSprite* m_pThumb;
	cocos2d::CCSprite* m_pThumb_shadow;
	cocos2d::CCPoint m_cpSrc_thumb;
	cocos2d::CCPoint m_cpDst_thumb;
	float m_fThumbDuring;
private:
	/*
		根据数据表设置当前步骤界面情况
	*/
	void _checkSetting();
	/*
		设置箭头
	*/
	void _clearArrow();
	void _setArrow(GuideItemData* guideData);
	void _thumbAction();

	//检查跳过按钮
	void _checkSkipButton(GuideItemData* data);
public:
	GuideWindow();
	virtual ~GuideWindow();
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

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

public:
	/*
		开始接触操作
	*/
	virtual    bool    ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		移动操作
	*/
	virtual    void    ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		接触结束操作
	*/
	virtual    void    ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		接触取消操作
	*/
	virtual    void    ccTouchCancel(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);

	//Time Label Call Back
	virtual void  TimerEventHandler(int eventType,std::string attachParam);

private:
	/*
		显示新手引导面板事件处理
	*/
	void   OnShowGuideWindowEventHandler(std::list<std::string>& paramList);
	/*
		新手引导下一步操作事件处理
	*/
	void   OnNextGuideStepEventHandler(std::list<std::string>& paramList);
	/*
		更新面板所有空间名称事件处理
	*/
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);

	/*
		显示箭头根据设置
	*/
	void _showArrowBySettings(int type,GuideItemData* guideData,CCNode* logicnode);
public:
	/*
		结束新手引导竞技场按钮操作处理
	*/
	void   OnFinishGuideButtonClick(cocos2d::CCObject* pSender);

	/*
		箭头移动完之后
	*/
	void CallBack_Arrow_Moveto();

protected:
	void CallBack_Thumb_ReachDST();
};


#endif
