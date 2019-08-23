#ifndef  _DOTATRIBE_UILAYER_H_
#define  _DOTATRIBE_UILAYER_H_


#include <cocos2d.h>

class cyouUILayer : public cocos2d::CCLayer
{
public:
	cyouUILayer();
	virtual ~cyouUILayer();

public:
	/*
		初始化操作
	*/
	virtual  void  onEnter();
	/*
		销毁操作
	*/
	virtual  void  onExit();

public:
	/*
		开始接触操作
	*/
	virtual  bool  ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		移动操作
	*/
	virtual  void  ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		接触结束操作
	*/
	virtual  void  ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		接触结束操作
	*/
	virtual  void  ccTouchCancelled(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		重力感应事件
	*/
	virtual  void  didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

public:
	/*
		返回按键操作处理
	*/
	virtual  void  keyBackClicked();
	/*
		系统按键操作处理
	*/
	virtual  void  keyMenuClicked();
};


#endif
