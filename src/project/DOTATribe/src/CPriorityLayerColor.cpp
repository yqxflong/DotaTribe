//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The layer can be set priority and AvoidSwallow
//
#include "../include/CPriorityLayerColor.h"

USING_NS_CC;

static const float IGNORE_DIS=50.0;

CPriorityLayerColor* CPriorityLayerColor::create(const ccColor4B& color, GLfloat width, GLfloat height,int priority){
	CPriorityLayerColor* cc=new CPriorityLayerColor();
	if (cc&&cc->initWithColor(color,width,height,priority))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CPriorityLayerColor::initWithColor(const ccColor4B& color, GLfloat width, GLfloat height,int priority){
	if (CCLayerColor::initWithColor(color,width,height))
	{
		m_nPriority=priority;
		this->setTouchEnabled(true);
		return true;
	}
	return false;
}
void CPriorityLayerColor::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_nPriority,true);
}

bool CPriorityLayerColor::cContainsThePoint(CCTouch *pTouch){
	const CCSize& sz = this->getContentSize();
	const CCPoint& anchor = this->getAnchorPoint();
	CCRect rect = CCRectMake(0-sz.width*anchor.x,0-sz.height*anchor.y,sz.width,sz.height);
	const CCPoint &cp_touch=convertTouchToNodeSpaceAR(pTouch);
	bool isContaion=rect.containsPoint(cp_touch);
	return isContaion;
}

bool CPriorityLayerColor::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	m_bIsCallBack=true;
	if (!this->isVisible()) return false;
	return cContainsThePoint(pTouch);
}

void CPriorityLayerColor::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint startPoint   = pTouch->getStartLocation();
	CCPoint currentPoint = pTouch->getLocation();
	float dis1=pow((startPoint.x-currentPoint.x),2);
	float dis2=pow((startPoint.y-currentPoint.y),2);
	float dis3=sqrt(dis1+dis2);
	if (dis3>=IGNORE_DIS)
		m_bIsCallBack=false;
}

void CPriorityLayerColor::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	bool condition=cContainsThePoint(pTouch);
	if (condition&&m_pDelegate&&m_bIsCallBack){
		m_pDelegate->touchEvent(this);
	}
}