//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Sprite can reflect TouchEvent
//
#include "../include/CTouchSprite.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
USING_NS_CC;

CTouchSprite* CTouchSprite::create(const char* filename,CTouchSpriteDelegate* delegate,int priority,bool swallow){
	CTouchSprite* ts=new CTouchSprite();
	if (ts&&ts->initWithFile(filename,delegate,priority,swallow))
	{
		ts->autorelease();
		return ts;
	}
	delete ts;
	return ts;
}

bool CTouchSprite::initWithFile(const char* filename,CTouchSpriteDelegate* delegate,int priority,bool swallow){
	if (CCSprite::init()){
		if (strcmp(filename,"0")!=0)
		{
			setProperty("File",filename);
		}
		m_pDelegate=delegate;
		m_nPriority=priority;
		m_bSwallow=swallow;
		return true;
	}
	return false;
}

void  CTouchSprite::onEnter(){
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_nPriority, m_bSwallow);
}
void  CTouchSprite::onExit(){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool CTouchSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	bool bb=cContainsThePoint(pTouch);
	return bb&&this->isVisible();
}

void CTouchSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	CCLOG("CTouchSprite::ccTouchMoved");
}

void CTouchSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	CCLOG("CTouchSprite::ccTouchEnded");
	bool condition=cContainsThePoint(pTouch);
	if (condition)
	{
		assert(m_pDelegate!=NULL);
		m_pDelegate->rangeTouched(this);
	}
	//play sound
	NFC_playSoundByID(this->m_nSoundID);
}

bool CTouchSprite::cContainsThePoint(CCTouch *pTouch){
	const CCSize& sz = this->getContentSize();
	const CCPoint& anchor = this->getAnchorPoint();
	CCRect rect = CCRectMake(0-sz.width*anchor.x,0-sz.height*anchor.y,sz.width,sz.height);
	const CCPoint &cp_touch=convertTouchToNodeSpaceAR(pTouch);
	bool isContaion=rect.containsPoint(cp_touch);
	return isContaion;
}