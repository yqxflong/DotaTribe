#ifndef  _COMPONENT_SCROLLSPRITELAYER_H
#define  _COMPONENT_SCROLLSPRITELAYER_H
#include "cocos2d.h"
#include "vector"
using namespace  cocos2d;

#define   SCROLLNODELAYERITEM     7   //可视节点

////////////////////////////////////////////////////////////////
//Name:	 UIScrollNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 滑动结点层
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

class  UIScrollNodeLayer: public cocos2d::CCLayer
{
public:
	enum
	{
		KCCScrollNodeLayerStateIdle,    //当前ScrollLayer处于空闲状态
		KCCScrollNodeLayerStateSliding, //当前ScrollLayer处于滑动状态
	};

	//layOut 结点数据
	typedef struct  _nodeData_Tag_
	{
		int   roleIndex_;				 //模型ID
		float scaleParam_;				 //放大系数
		cocos2d::CCPoint potionParam_;   //坐标参数
	public:
		_nodeData_Tag_()
		{
			roleIndex_=0;
			scaleParam_=0.0f;
			potionParam_=CCPointZero; 
		}
	}NODEDATA,*PNODEDATA;
	 


public:
	UIScrollNodeLayer();
	~UIScrollNodeLayer();
public:
	static  UIScrollNodeLayer *  CreateScrollNodeLayerWithArray(cocos2d::CCArray * pnodeArray,cocos2d::CCPoint=CCPointZero,cocos2d::CCSize contenSize=CCSizeZero);
private:
	bool   InitWithScrollNodeLayerWithArray(cocos2d::CCArray * pnodeArray,cocos2d::CCPoint=CCPointZero,cocos2d::CCSize contenSize=CCSizeZero);
public:
	virtual void  onEnter();
	virtual void  onExit();
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	//virtual	void visit();         //默认调用基类剪裁区域
private:
	void  claimTouch(cocos2d::CCTouch * pTouch);
	void  cancelAndStoreTouch(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
private:
	void   initNodeLayOut();
	void   initWaitShowNodeArray();
	void   nextWaitShowNodeArrayForLeft();
	void   nextWaitShowNodeArrayForRight();
	
    void   OnInitShowNode();
	void   OnShowNodeLeft();
	void   OnshowNodeRight();
public:
	int GetMiddleSelectRoleIndex();   //获取选中人物索引

protected:
	GLfloat  startSwipe_;			             //用户开始触摸时候的触摸点
	GLfloat  minmumTouchLengthToSlider_;         //最小移动使能 距离
    int      state_;                             //当前Scroll的状态
	cocos2d::CCRect  scissorRect_;               //裁剪区域
    std::vector<NODEDATA>    nodeLayOutVector_;  //结点布局vector
	float middleWidth; 
	float midldleHeight;
	int   initWaitShowRoleIndex[SCROLLNODELAYERITEM];   //初始化时候的显示的角色索引
	int   nextWaitShowRoleIndex[SCROLLNODELAYERITEM];   //一个操作将要显示的角色索引
	int   middleSelectRoleIndex_;

	unsigned int   childrenCount_;  

private:
    int   touchPriority_;     //触摸的优先级别
	bool  isMoveEnable_;      //触摸移动使能
};

 
 



#endif



