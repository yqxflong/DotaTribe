//Name: NFDTBoardFactory
//Func: Used to Create DTBoard
//Written by: Johny

#include "../include/NFDTBoardFactory.h"
#include "../include/DTEquipBoard.h"
#include "../include/DTAwardBoard.h"
#include "../include/DTHeroIcon.h"


USING_NS_CC;

/*
	装备框组合
*/
cocos2d::CCNode * NFDTEquipBoardFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CCSprite* hint=NULL;
	if (strcmp(dd->filepath2_,"0")!=0)
	{
		hint=CCSprite::create();
		hint->setProperty("File",dd->filepath2_);
	}
	CCSprite* corner=CCSprite::create();
	corner->setProperty("File",dd->filepath3_);
	CCLabelTTF* num=CCLabelTTF::create();
	num->setFontName(dd->fontname_);
	num->setColor(ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
	num->setFontSize(dd->fontsize_);
	//
	DTEquipBoard* cc=DTEquipBoard::create(hint,corner,num);
	cc->setTag(dd->idx_);
	cc->setZOrder(dd->zorder_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setTouchPriority(dd->touchpriority_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc);
	return cc;
}

/*
	奖励框组合
*/
cocos2d::CCNode * NFDTAwardBoardFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CCSprite* numBg=CCSprite::create();
	numBg->setProperty("File",dd->filepath_);
	CCLabelTTF* num=CCLabelTTF::create();
	num->setFontName(dd->fontname_);
	num->setColor(ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
	num->setFontSize(dd->fontsize_);
	//
	bool isSwallow=dd->swallow_==1?true:false;
	DTAwardBoard* cc=DTAwardBoard::create(numBg,num,dd->touchpriority_,isSwallow);
	cc->setTag(dd->idx_);
	cc->setIDX(dd->idx_);
	cc->setZOrder(dd->zorder_);
	cc->setScale(dd->scale_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc);
	return cc;
}
 
/*
英雄图像
*/ 
cocos2d::CCNode * NFDTHeroIconFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{    
	bool isLargeIcon = dd->colorR_ > 0 ? true:false;
	DTHeroIcon * pHeroIcon=DTHeroIcon::createHeroIcon(0,0,isLargeIcon,dd->touchpriority_);
	pHeroIcon->setTag(dd->idx_);
	pHeroIcon->setZOrder(dd->zorder_);
	bool isVisible=dd->hide_==0?true:false;
	pHeroIcon->setVisible(isVisible);
	pHeroIcon->setIconScale(dd->scale_);
	pHeroIcon->setAnchorPoint(ccp(0,0));
	pHeroIcon->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(pHeroIcon);
	return pHeroIcon;
} 