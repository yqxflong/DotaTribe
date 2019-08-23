#ifndef    _COCOS_EXTENSION_DRAGENODELAYER_
#define    _COCOS_EXTENSION_DRAGENODELAYER_
#include   <cocos2d.h> 
#include   "../include/CCSignSprite.h"

////////////////////////////////////////////////////////////////
//Name:	 CCDragNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 拖拽控制层
//Maintainer: 	xiaobo.wu
//date:   2013/11/20
////////////////////////////////////////////////////////////////
 

class  CCDragLayerProtocol
{
public:
	enum
	{
		_UNKONW_DRAG_END_TYPE_,
		_CLICK_DRAG_END_TYPE_,
		_OTHER_DRAG_END_TYPE_,
	};
	virtual bool delegateDragEndEventHandler(int eventType,CCSignSprite * pSignSprite,cocos2d::CCPoint & touchPoint)=0;
};
   
class    CCDragNodeLayer : public cocos2d::CCLayer
{ 
public:
	CCDragNodeLayer();
	virtual ~CCDragNodeLayer();
    static CCDragNodeLayer * createDragNodeLayer(CCDragLayerProtocol * pDrageDelegte=NULL);
	virtual void  onEnter();
	virtual void  onExit();
	void    addSignSpriteVector(std::vector<CCSignSprite* >  signSpriteVec,int zOrder);
	void    addTargetSignSprite(CCSignSprite * pSignSprite,int zOrder);
	void    removeTargetSignSpriteWithID(int signSpriteUniqueID);
	void    addOtherAttachSprite(cocos2d::CCSprite * pAttachSprite,int zOrder);
	void    addTargetAttachSprite(cocos2d::CCSprite * pTargetAttachSprite,int zOrder);
	/*
	移除所有公共触摸结点
	*/
	 
	/*
	移除所有目标触摸结点
	*/
	void    removeAllTargetSignSprites();
	/*
	移除目标附加精灵
	*/
	void    removeAllOtherAttachSprite();
	/*
	移除公共附加精灵
	*/
	void    removeAllTargetAttachSprite();
	/*
	移除所有数据
	*/
	void    removeAllData();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void  clearAllSignTouchArray();
	void  setDragLayerTouchEnable(bool touchEnable);
	void  setDragLayerTouchPriority(int touchPriority);
	bool  getDragLayerTouchEnabel();
	void  setDefaultTargetSegmentHeight(float targetSegmentHeigh);
	void  setDragEventDelegate(CCDragLayerProtocol * pDrageDelegte);
protected:
	bool  initDragNodeLayer(CCDragLayerProtocol * pDrageDelegte);
	bool  touchSignCheck(cocos2d::CCTouch *pTouch);
	void  dispatchTouchEvent(cocos2d::CCPoint & touchPosition);
protected: 
	bool	 m_bDragEnable;
	int		 m_nTouchPriority;  
	int		 m_nCurActiveSignID;
	size_t   m_nRankCount;
	size_t   m_nColumnCount;
	std::vector< std::vector<CCSignSprite *> >  m_vTouchsArray;		//Common Sign Vector
	std::list<CCSignSprite *>  m_vTargetTouchsArray;				//Target Sign Vector
	std::vector<cocos2d::CCSprite *>	 m_vOtherAttachArray;		//AttachArray Commmon
	std::vector<cocos2d::CCSprite *>	 m_vOtherTargetAttachArray;	//Target Attach Array
	CCSignSprite *  m_pCurActiveSingle;								//Cur Active Sign 
	float    m_fDelayDragTime;
	float    m_fTargetAreaHeight;									//sreach segment
	CCDragLayerProtocol *   m_pDragDelegate;
};


#endif