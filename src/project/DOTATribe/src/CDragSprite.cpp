//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Sprite can be draged
//
#include "../include/CDragSprite.h"

USING_NS_CC;

CDragSprite* CDragSprite::create(const char* filename,cocos2d::CCNode* copyroot,CDragSpriteDelegate* delegate){
	CDragSprite* drag=new CDragSprite();
	if (drag&&drag->initWithFile(filename,copyroot,delegate))
	{
		drag->autorelease();
		return drag;
	}
	delete drag;
	return drag;
}
bool CDragSprite::initWithFile(const char* filename,cocos2d::CCNode* copyroot,CDragSpriteDelegate* delegate){
	if (CCSprite::init()){
		this->setProperty("File",filename);
		assert(copyroot!=NULL);
		m_pRootNode=copyroot;
		m_pDelegate=delegate;
		return true;
	}
	return false;
}

CDragSprite* CDragSprite::create(CCTexture2D* texture,CCNode* copyroot,CDragSpriteDelegate* delegate){
	CDragSprite* drag=new CDragSprite();
	if (drag&&drag->initWithTexture(texture,copyroot,delegate))
	{
		drag->autorelease();
		return drag;
	}
	delete drag;
	return drag;
}
bool CDragSprite::initWithTexture(CCTexture2D* texture,CCNode* copyroot,CDragSpriteDelegate* delegate){
	if (CCSprite::initWithTexture(texture)){
		assert(copyroot!=NULL);
		m_pRootNode=copyroot;
		m_pDelegate=delegate;
		return true;
	}
	return false;
}

void  CDragSprite::onEnter(){
	CCSprite::onEnter();
	if (m_bIsDragEnabled)
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}
void  CDragSprite::onExit(){
	if (m_bIsDragEnabled)
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool CDragSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	m_previousPoint=pTouch->getLocationInView();
	return cContainsThePoint(pTouch);
}

void CDragSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	CCLOG("CDragSprite::ccTouchMoved");
	CCPoint cp_touch=pTouch->getLocationInView();
	cp_touch=CCDirector::sharedDirector()->convertToGL(cp_touch);
	if (!m_pCopy)
	{
		m_pCopy=CCSprite::createWithTexture(getTexture());
		m_pCopy->setTag(m_nIdx);//used to identify the what the copy from
		m_pCopy->setPosition(getPosition());
		m_pCopy->setScale(this->getScale());
		//need to be added to the bottomest layer
		m_pRootNode->addChild(m_pCopy,m_sCopyzOrder);
	}
	m_pCopy->setPosition(cp_touch);

}

void CDragSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	CCLOG("CDragSprite::ccTouchEnded");
	if (m_pCopy)
	{
		const CCPoint& cp=pTouch->getLocationInView();
		m_pDelegate->containsTheCopy(m_pCopy,m_nDragType);
		m_pCopy->removeFromParentAndCleanup(true);
		m_pCopy=0;
	}else{
		m_pDelegate->clickEvent(m_nIdx,m_nDragType);
	}
}

void CDragSprite::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCLOG("CDragSprite::ccTouchCancelled");
	if (m_pCopy)
	{
		const CCPoint& cp=pTouch->getLocationInView();
		m_pDelegate->containsTheCopy(m_pCopy,m_nDragType);
		m_pCopy->removeFromParentAndCleanup(true);
		m_pCopy=0;
	}else{
		m_pDelegate->clickEvent(m_nIdx,m_nDragType);
	}
}

bool CDragSprite::cContainsThePoint(CCTouch *pTouch){
	CCLOG("idx:::%d",getTag());
	const CCSize& sz = this->getContentSize();
	const CCPoint& anchor = this->getAnchorPoint();
	CCRect rect = CCRectMake(0-sz.width*anchor.x,0-sz.height*anchor.y,sz.width,sz.height);
	const CCPoint &cp_touch=convertTouchToNodeSpaceAR(pTouch);
	bool isContaion=rect.containsPoint(cp_touch);
	bool isVisible=this->isVisible();
	return isContaion&&isVisible;
}