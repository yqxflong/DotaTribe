//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Sprite can reflect TouchEvent
//
#ifndef  _DOTATRIBE_CTOUCHSPRITE_H_
#define  _DOTATRIBE_CTOUCHSPRITE_H_

#include "cocos2d.h"

class CTouchSpriteDelegate{
public:
	virtual void rangeTouched(cocos2d::CCObject* pSender)=0;
};

class CTouchSprite:public cocos2d::CCSprite,public cocos2d::CCTargetedTouchDelegate{
private:
	CTouchSpriteDelegate* m_pDelegate;
	int m_nPriority;
	bool m_bSwallow;
	int m_nIDX;
	int m_nSoundID;
public:
	CTouchSprite(){
		m_pDelegate=0;
		m_nPriority=0;
		m_bSwallow=false;
		m_nIDX=0;
		m_nSoundID=-1;
	};
	~CTouchSprite(){};
	static CTouchSprite* create(const char* filename,CTouchSpriteDelegate* delegate,int priority=0,bool swallow=true);
	bool initWithFile(const char* filename,CTouchSpriteDelegate* delegate,int priority,bool swallow);
	//setter
	void setDelegate(CTouchSpriteDelegate* del){
		m_pDelegate=del;
	}
	void setIDX(int idx){
		m_nIDX=idx;
	}
	//getter
	int getIDX()const{
		return m_nIDX;
	}
	//
	void setSoundID(int soundid){
		m_nSoundID=soundid;
	}
protected:
	virtual  void   onEnter();
	virtual  void   onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//
	bool cContainsThePoint(cocos2d::CCTouch *pTouch);
};
#endif