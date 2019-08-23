//Name: NFCCMenuFactory
//Func: Used to Create CCLabel
//Written by: Johny

#include "../include/NFCCMenuFactory.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CSelectedSprite.h"
#include "../include/HWMoreItems.h"
#include "../include/FAnimationButton.h"
#include "../include/NFControlsManager.h"

USING_NS_CC;
USING_NS_CC_EXT;


/*
	---->CMenuItemSprite  Single Img
	*FilePath2 is Empty
	*width_ is scale
	*the image is large than normal one
*/
cocos2d::CCNode* NFCMenuItemSpriteSIFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CPriorityMenu* menu=CPriorityMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CCSprite* sp1=CCSprite::create();
	sp1->setProperty("File",dd->filepath_);
	sp1->setScale(dd->width_);
	CMenuItemSprite* cc=CMenuItemSprite::create((CCSprite*)NULL,NULL,NULL,NULL);
	cc->setNormalImageAndRelocation(sp1);
	if (strcmp(dd->filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd->filepath3_);
		sp->setScale(dd->width_);
		cc->setDisabledImage(sp);
	}
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
		cc->setRotation(dd->rotation_);
	cc->setTag(0);
	cc->setSelectedType(CMenuItemSprite::kSELECTEDTYPE_SCALETO_BIG);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}


cocos2d::CCNode* NFFAnimationButtonFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	FAPriorityMenu* menu = FAPriorityMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	FAnimationButton* cc=FAnimationButton::create(dd->filepath_,dd->filepath2_,NULL,NULL);
	//cc->InitAnimation();
	if (strcmp(dd->filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd->filepath3_);
		cc->setDisabledImage(sp);
	}
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
		cc->setRotation(dd->rotation_);
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnimationId(dd->colorR_);
	cc->setAnimationPos(dd->width_, dd->height_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}


/*
	---->CMenuItemSprite  Normal
	-->filepath1_ can be empty
	-->filepath2_ can be empty
	TODO:Set the selectedType for item
*/
cocos2d::CCNode* NFCMenuItemSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	return NFC_createMenuItemByViewData(parentNode,*dd);
}

/*
	---->CLabelButton
*/
cocos2d::CCNode* NFCLabelButtonFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	return NFC_createCLabelButtonByViewData(parentNode,*dd);
}

/*
	---->CMenuItemSprite  Normal+Selected
*/
cocos2d::CCNode* NFCMenuItemSpriteSelectedFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CPriorityMenu* menu=CPriorityMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::createWithCompositeSelectedImage(dd->filepath2_,dd->filepath_);
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}

/*
	---->CImMenuItemSpriteSI  Normal
*/
cocos2d::CCNode* CImMenuItemSpriteSIFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CImmovableMenu* menu=CImmovableMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::create(dd->filepath_,NULL,NULL);
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}

/*
	---->CImMenuItemSprite  Normal
*/
cocos2d::CCNode* CImMenuItemSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CImmovableMenu* menu=CImmovableMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::create(dd->filepath_,dd->filepath2_,NULL,NULL);
	if (strcmp(dd->filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd->filepath3_);
		cc->setDisabledImage(sp);
	}
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}

/*
	---->CImMenuItemSprite  Normal+Selected
*/
cocos2d::CCNode* NFCImMenuItemSpriteSelectedFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CImmovableMenu* menu=CImmovableMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::createWithCompositeSelectedImage(dd->filepath2_,dd->filepath_);
	if (strcmp(dd->filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd->filepath3_);
		cc->setDisabledImage(sp);
	}
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}

/*
	---->CTabMenuItemSprite  Normal
*/
cocos2d::CCNode* CTabMenuItemSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CTabMenu* menu=CTabMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::create(dd->filepath_,dd->filepath2_,NULL,NULL);;
	if (strcmp(dd->filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd->filepath3_);
		cc->setDisabledImage(sp);
	}
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}

/*
	---->CTabImmovableMenuItemSprite  Normal+Selected
*/
cocos2d::CCNode* NFCTabImmovableMenuItemSpriteSelectedFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CTabImmovableMenu* menu=CTabImmovableMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::createWithCompositeSelectedImage(dd->filepath2_,dd->filepath_);
	cc->setTag(0);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}




//NFCHWMoreItemFactory
cocos2d::CCNode* NFHWMoreItemFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CPriorityMenu* menu=CPriorityMenu::create(dd->touchpriority_,isSwallow);
	menu->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd->zorder_);
	CCSprite* sp1=CCSprite::create();
	sp1->setProperty("File",dd->filepath_);
	sp1->setScale(dd->width_);
	
	HWMoreItems* cc=HWMoreItems::create(NULL,NULL,NULL);
	cc->setNormalImageAndRelocation(sp1);
	cc->setTag(0);
	cc->setSelectedType(CMenuItemSprite::kSELECTEDTYPE_SCALETO_BIG);
	cc->setSoundID(dd->soundid_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	menu->addChild(cc);
	return cc;
}