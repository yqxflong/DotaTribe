#ifndef  _DOTATRIBE_COMPNENT_UIDRAGNODE_H
#define  _DOTATRIBE_COMPNENT_UIDRAGNODE_H

//Author: xiaobo.wu
//Description:  拖拽结点类(支持Sprite变灰,延时拖拽)
//Date:  2013.06.30

#include  <cocos2d.h>

class  DragDelegateProtocol
{
public:
     virtual void  onCommandHandler(int eventType,void * ptr)=0;
};

 

class   UIDragNode: public cocos2d::CCSprite,public cocos2d::CCTouchDelegate 
{
public:
	//拖拽结点的状态
	enum
	{
	   _UIDRAGNODE_UNKONW_TYPE_,
	   _UIDRAGNODE_IDLE_TYPE_,                  //空闲状态
	   _UIDRAGNODE_STARTDRAG_TYPE_,             //开始拖拽
	   _UIDRAGENODE_DRAGING_TYPE_,				//正在拖拽
	   _UIDRAGENODE_ENDDRAG_TYPE,				//结束拖拽
	};
	//拖拽结点的对象类型
	enum
	{
		_UIDRAGNODE_UNKONW_OBJTYPE_,  
	};
	
public:
	UIDragNode();
	~UIDragNode();
public:
	/*
	 使用文件纹理创建拖拽结点
	*/
	static  UIDragNode *  createUIDragNodeWithFile(int identify,const char * fileName,bool isDisable=false);    
	
	/*
	 使用帧纹理创建拖拽结点
	*/
	static  UIDragNode *  createUIDragNodeWithFrame(int identify,cocos2d::CCSpriteFrame *  spriteFrame,bool isDisable=false);

	/*
	使用PlistFrameName创建拖拽结点
	*/
	static  UIDragNode *  createUIDragNodeWithFrameName(int identify,const char * frameName,bool isDisable=false);

protected:
	bool   initUIDragNodeWithFile(int identify,const char * fileName,bool isDisable);
	bool   initUIDragNodeWithFrame(int identify,cocos2d::CCSpriteFrame * spriteFrame,bool isDisable);
	bool   initUIDragNodeWithFrameName(int identify,const char * frameName,bool isDisable);

public:
	//注册DragNode的触摸事件
	virtual  void   onEnter();
	virtual  void   onExit();

public:
	cocos2d::CCPoint &  getDragNodeInitPosition();							//获得拖拽结点的初始位置
	void	setDragNodeInitPosition(cocos2d::CCPoint initPosition);			//设置拖拽结点的初始位置
	void    setDragNodeIdentify(int  identify);								//设置拖拽结点的标示
	int		getDragNodeIdentify();											//获得拖拽结点的标示
	void    setDragNodeIsDisable(bool isDisable);	
	bool	getDragNodeIsDisable();
	bool    getIsTouchEnable();
	void    setTouchEnable(bool touchEnable);
	int     getTouchPriority();
	void    setTouchPriirity(int touchPriority);
	float   getDragDelayTime();											    //获得拖拽结点延时时间
	void    setDragDelayTime(float drayDelayTime);							//设置拖拽结点延时时间
	void    setDragNodeType(int nodeType);								    //设置拖拽结点类型
	int     getDragNodeType();												//获得拖拽结点类型
	void    setDelegateNode(DragDelegateProtocol * delegateNode);		    //设置回调者指针
	void    mandatoryMoveToInitPosition();									//强制设置为初始位置	

	bool    checkIsCoverWithRect(float left,float right,float top,float bottom,float offWidth=40.f);
 
//////////////////////////////////////////////////////////////////////////
	void	disableDragSprite();								//图片变灰实现
	 
protected:
	virtual  bool   ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual  void   ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual  void   ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual  void   ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
 

	cocos2d::CCPoint  converTouchToGLLocation(cocos2d::CCTouch *pTouch);
	bool			  ccCheckIsContainsTouchLocation(cocos2d::CCTouch *pTouch);				//判断是否Touch区域是否包含在本结点空间中
	cocos2d::CCRect   ccGetNodeRectWithAnchor(bool isUseAnchor=true);
	bool			  ccCheckIsTouchClick(cocos2d::CCPoint touchPosition);


private:
	bool   isDisable_;						 //是否显示灰色底纹并且禁止拖拽
	bool   isDragEnable_;					 //是否可以拖拽
	bool   isTouchEnable_;					 //触摸使能
	cocos2d::CCPoint	startDragPoint_;	 //开始拖拽的坐标
	cocos2d::CCPoint    initLayoutPoint_;	 //初始化布局坐标
	int    curNodeState_;					 //当前拖拽结点的状态
	int	   nodeIdentify_;					 //结点的Unique的标号
	int    touchPriority_;					 //触摸优先级别
	float  dragDelayTime_;					 //拖拽延时时间
	int	   dragNodeType_;					 //拖拽结点的类型
	DragDelegateProtocol  * pDelegateNode_;	 //回调者
};

#endif