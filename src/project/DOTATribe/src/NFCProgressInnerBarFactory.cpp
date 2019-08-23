//Name: NFCProgressInnerBarFactory
//Func: Used to Create NFCProgressInnerBar
//Written by: Johny

#include "../include/NFCProgressInnerBarFactory.h"
#include "../include/CProgressInnerBar.h"
#include "../include/CProgressTimer.h"

USING_NS_CC;

cocos2d::CCNode* NFCProgressInnerBarFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CProgressInnerBar* cc=CProgressInnerBar::create(dd->filepath_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setPercent(0);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CCProgressTimer
*/
cocos2d::CCNode* NFCCProgressTimerFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	//Max length
	CCSprite* cc_inner=CCSprite::create();
	cc_inner->setProperty("File",dd->filepath_);
	//
	CCProgressTimer*cc=CCProgressTimer::create(cc_inner);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	cc->setType(kCCProgressTimerTypeBar);
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CProgressTimer
*/

cocos2d::CCNode* NFCProgressTimerFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	//Max length
	CProgressTimer*cc = CProgressTimer::create(dd->filepath_,dd->width_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	cc->setType(kCCProgressTimerTypeBar);
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}