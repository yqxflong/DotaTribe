//Name: NFCCLayerFactory
//Func: Used to Create CCLayer
//Written by: Johny

#include "../include/NFCCLayerFactory.h"
#include "../include/CPriorityLayerColor.h"

USING_NS_CC;

cocos2d::CCNode* NFCCLayerFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
    CCLayer* cc=CCLayer::create();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
    return cc;
}

cocos2d::CCNode* NFCCLayerColorFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
    CCLayerColor* cc=CCLayerColor::create(ccc4(dd->colorR_, dd->colorG_, dd->colorB_,dd->alpha_),dd->width_,dd->height_);
    cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
    cc->setPosition(ccp(dd->posx_,dd->posy_));
    parentNode->addChild(cc,dd->zorder_);
    return cc;
}

cocos2d::CCNode* NFCPriorityLayerColorFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CPriorityLayerColor* cc=CPriorityLayerColor::create(ccc4((GLubyte)dd->colorR_, (GLubyte)dd->colorG_, (GLubyte)dd->colorB_,(GLubyte)dd->alpha_),dd->width_,dd->height_,dd->touchpriority_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}