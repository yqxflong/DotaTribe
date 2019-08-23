//Name: NFCCNodeFactory
//Func: Used to Create CCNode
//Written by: Johny

#include "../include/NFCCNodeFactory.h"
#include "../include/MaskNode.h"
#include "../include/CCardsStarProgress.h"
#include "../include/GrapStarsProgress.h"

USING_NS_CC;

cocos2d::CCNode* NFCCNodeFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
    CCNode* cc=CCNode::create();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setScale(dd->scale_);
	cc->setContentSize(CCSizeMake(dd->width_,dd->height_));
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
    return cc;
}

cocos2d::CCNode * NFMaskNodeFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{
	MaskNode * cc = MaskNode::create();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setContentSize(CCSizeMake(dd->width_,dd->height_));
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	cc->setViewData(dd);
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	进阶星级节点
*/
cocos2d::CCNode * NFStarLevelNodeFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{ 
	std::string  advanceStarName=dd->filepath2_;
	CCardsStarProgress* cc=NULL;
	if(advanceStarName!="0")
	cc=CCardsStarProgress::create(dd->filepath_,advanceStarName,dd->colorR_,dd->width_);
	else
	cc=CCardsStarProgress::create(dd->filepath_,"",dd->colorR_,dd->width_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setScale(dd->scale_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	灰色星级节点
*/
cocos2d::CCNode * NFGrapStarsProgressFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{   
	GrapStarsProgress * pGrapStarsProgress = GrapStarsProgress::createGrapStarsProgress(dd->colorR_,dd->colorG_,dd->width_);
	pGrapStarsProgress->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	pGrapStarsProgress->setVisible(isVisible);
	pGrapStarsProgress->setScale(dd->scale_);
	pGrapStarsProgress->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	pGrapStarsProgress->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(pGrapStarsProgress,dd->zorder_);
	return pGrapStarsProgress;
}



