#ifndef  _DOTATRIBE_COMPNENT_UISTRETCHNODELAYER_H
#define  _DOTATRIBE_COMPNENT_UISTRETCHNODELAYER_H
#include  <cocos2d.h>
 
////////////////////////////////////////////////////////////////
//Name:	 UITwoSileStretchNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 双向拉伸结点层
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

class  UITowSideStretchNodeLayer: public cocos2d::CCLayer
{
public:
	enum
	{
		_UITWOSIDESTRETCH_UNKONW_TYPE_,
		_UITWOSIDESTRETCH_IDLE_TYPE_,    //空闲
		_UITWOSIDESTRETCH_UNFOLD_TYPE_,  //展开
		_UITWOSIDESTRETCH_SHRINK_TYPE_,  //收缩 
	};
public:
	UITowSideStretchNodeLayer();
	~UITowSideStretchNodeLayer();
public:
	//双向伸展层创建函数
	static  UITowSideStretchNodeLayer *  createTowSideStretchLayer(cocos2d::CCNode * leftNormalNode=NULL,cocos2d::CCNode * leftSelectedNode=NULL,cocos2d::CCNode * rightNormalNode=NULL,cocos2d::CCNode * rightSelectedNode=NULL);
protected:
	bool   initTwoSideStretchLayer(cocos2d::CCNode * leftNormalNode,cocos2d::CCNode * leftSelectedNode,cocos2d::CCNode * rightNormalNode,cocos2d::CCNode * rightSelectedNode);
public:
	virtual  void  onEnter();
	virtual  void  onExit();
public:
	virtual bool  ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void  ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void  ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
public:
    bool   onShowUnfoldNode(bool isLeft);  //展开
	bool   onShowShrinkNode(bool isLeft);  //收缩 
	
	//获取屏幕左半边Rect
	cocos2d::CCRect  getLeftScreenRect();  
	cocos2d::CCRect  getRightScreenRect();

	//判断触摸是否在左边屏幕
	bool   containTouchOnLeftRect(cocos2d::CCTouch * pTouch);
	//判断触摸是否在右边屏幕
	bool   containTouchOnRightRect(cocos2d::CCTouch * pTouch);

	 
public:
//属性的Set
	void   setLeftNormalNode(cocos2d::CCNode * leftNormal);
	void   setleftSelectNode(cocos2d::CCNode * leftSelected);
 	void   setRightNormalNode(cocos2d::CCNode * rightNormal);
	void   setRightSelectNode(cocos2d::CCNode * rightSelected);
	void   setStretchTime(float stretchTime);
	void   setTouchEnable(bool touchEnable);
	void   setTouchPriority(int touchPriority);

	void   setNormalAndSelectWith(float normalWidth,float selectWidth);
	void   setNormalAndSelectYPos(float normalYPos,float selectYPos);
  

//属性的Get
	cocos2d::CCNode *   getLeftNormalNode();
	cocos2d::CCNode *   getleftSelectNode();
	cocos2d::CCNode *   getRightNormalNode();
	cocos2d::CCNode *   getRightSelectedNode();
	float   getStretchTime();
	bool    getTouchEnable();
	int     getTouchPriority();
	 
private:
	int    touchPriority_;				//触摸优先级别
	bool   isTouchEnable_;				//触摸使能
	float  normalstretchTime_;			//延时时间
	float  selectstretchTime_;			//延时时间
	bool   isLeftNormalVisible_;		//左边 开启按钮是否可视
	bool   isLeftSelectedVisible_;    
	bool   isRightNormalVisible_;
	bool   isRIghtSelectedVisible_;

	cocos2d::CCNode * leftNormalNode_; 
	cocos2d::CCNode * leftSelectedNode_;
	cocos2d::CCNode * rightNormalNode_;
	cocos2d::CCNode * rightSelectedNode_;

	float   normalWidth_;
	float   selectedWidth_;
	float   normalYPos_;
	float   selectedYPos_;
 
};

#endif
