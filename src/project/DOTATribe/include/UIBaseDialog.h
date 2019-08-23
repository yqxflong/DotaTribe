#ifndef   _DOTATRIBE_UICOMPONENT_BASEDIALOG_H_
#define   _DOTATRIBE_UICOMPONENT_BASEDIALOG_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:    基类对话框  (自带遮罩层)
//date:   2013/07/21
///////////////////////////////////////////////// 
#include   <cocos2d.h>

using namespace cocos2d;

//默认的结点

class  UIBaseDialogProtory
{
public:
	 virtual  void   BaseDialogCallBackHandler(int eventType,void * ptr)=0;
};
 

class   UIBaseDialog: public cocos2d::CCLayerMask
{
public:
   enum
   {
	   _UIBASEDIALOG_NORMAL_PRIORITY_=-188,  //较高的触摸优先级别
	   _UIBASEDIALOG_HIGHT_PRIORITY_=0,		 //默认的触摸优先级别
   };
public:
    UIBaseDialog();
	virtual ~UIBaseDialog();
public:
	static UIBaseDialog *  createUIBaseDialog(int priority=_UIBASEDIALOG_NORMAL_PRIORITY_);
	void   setTouchUnCloseRect(cocos2d::CCRect rect); 
	void   setDelegatePrototy(UIBaseDialogProtory * delegatePtr);
protected:
	virtual bool  initUIBaseDialog(int priority);
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool  checkIsTouchInUnClose(cocos2d::CCPoint touchPoint);
	virtual void  setDialogBgColor(ccColor3B & color);
	virtual void  setDialogOpacity(GLubyte & opacity);
	cocos2d::CCRect  rect();

protected:
	int  priority_;
	cocos2d::CCRect unCloseRect_; 
	cocos2d::ccColor3B markColor_;
	int    opacity_;
    UIBaseDialogProtory *   pDelegate_;
};

 

#endif