//Name: NFCCTableViewFactory
//Func: Used to Create CCTableView
//Written by: Johny

#include "../include/NFCCTableViewFactory.h"
#include "../include/CTableView.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
	---->CCTableView
*/
cocos2d::CCNode* NFCCTableViewFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CCTableView* cc=new CCTableView();
	cc->initWithViewSize(CCSizeMake(dd->width_,dd->height_));
	cc->autorelease();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CTableView
*/
cocos2d::CCNode* NFCTableViewFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CTableView* cc=new CTableView();
	bool isSwallow=dd->swallow_==0?false:true;
	cc->init(NULL,CCSizeMake(dd->width_,dd->height_),dd->touchpriority_,isSwallow);
	cc->autorelease();
	cc->setVerticalFillOrder(kCCTableViewFillTopDown);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));

	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CScrollView
*/
cocos2d::CCNode* NFCScrollViewFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CScrollView* cc=new CScrollView();
	bool isSwallow=dd->swallow_==0?false:true;
	cc->init(dd->touchpriority_,isSwallow);
	cc->setDirection(kCCScrollViewDirectionVertical);
	cc->setViewSize(CCSizeMake(dd->width_,dd->height_));
	cc->autorelease();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CMapScrollView
*/
cocos2d::CCNode* NFCMapScrollViewFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CMapScrollView* cc=new CMapScrollView();
	bool isSwallow=dd->swallow_==0?false:true;
	cc->initWithViewSize(CCSizeMake(dd->width_,dd->height_),dd->touchpriority_,isSwallow);
	cc->autorelease();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}