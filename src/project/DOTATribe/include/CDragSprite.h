//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Sprite's copy can be draged
//
#ifndef  _DOTATRIBE_CDRAGSPRITE_H_
#define  _DOTATRIBE_CDRAGSPRITE_H_

#include "cocos2d.h"

class CDragSpriteDelegate{
public:
	virtual void clickEvent(int idx,int type=0)=0;
	virtual bool containsTheCopy(cocos2d::CCSprite* copy,int type=0)=0;
};

class CDragSprite:public cocos2d::CCSprite,public cocos2d::CCTargetedTouchDelegate{
private:
	bool m_bIsDragEnabled;
	cocos2d::CCSprite *m_pCopy;
	cocos2d::CCNode *m_pRootNode;		//the node to add copy
	CDragSpriteDelegate* m_pDelegate;
	short m_sCopyzOrder;			//copy's zOrder
	int m_nDragType;			//used to distinct diff situaiton
	int m_nIdx;		//used to identify the sprite
	cocos2d::CCPoint m_previousPoint;			//record previous point
public:
	CDragSprite(){
		m_bIsDragEnabled=0;
		m_pCopy=0;
		m_pRootNode=0;
		m_pDelegate=0;
		m_sCopyzOrder=0;
		m_nDragType=0;
		m_nIdx=0;
	};
	~CDragSprite(){};
	static CDragSprite* create(const char* filename,cocos2d::CCNode* copyroot,CDragSpriteDelegate* delegate);
	bool initWithFile(const char* filename,cocos2d::CCNode* copyroot,CDragSpriteDelegate* delegate);
	static CDragSprite* create(cocos2d::CCTexture2D* texture,cocos2d::CCNode* copyroot,CDragSpriteDelegate* delegate);
	bool initWithTexture(cocos2d::CCTexture2D* texture,cocos2d::CCNode* copyroot,CDragSpriteDelegate* delegate);
	//
	/*
		Set Delegate
	*/
	void setDelegate(CDragSpriteDelegate* delegate){
		m_pDelegate=delegate;
	}
	/*
		must before onenter()
	*/
	void isDragEabled(bool eabled){
		m_bIsDragEnabled=eabled;
	};
	bool isDragEabled () const{
		return m_bIsDragEnabled;
	};
	/*
		must before touchBegin
	*/
	void copyzOrder(short zOrder){
		m_sCopyzOrder=zOrder;
	};
	int copyzOrder () const{
		return m_sCopyzOrder;
	};
	/*
		must before touchBegin
	*/
	void dragType(int type){
		m_nDragType=type;
	};
	int dragType () const{
		return m_nDragType;
	};
	//
	void setIDX(int idx){
		m_nIdx=idx;
	};
	int getIDX () const{
		return m_nIdx;
	};
protected:
	virtual  void   onEnter();
	virtual  void   onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
	/*
		if the rect contains the point
	*/
	bool cContainsThePoint(cocos2d::CCTouch *pTouch);
};
#endif