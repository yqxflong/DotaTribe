//Name: NFCCEditBoxFactory
//Func: Used to Create CCEditBox
//Written by: Johny

#include "../include/NFCCEditBoxFactory.h"

USING_NS_CC;
USING_NS_CC_EXT;

cocos2d::CCNode* NFCCEditBoxFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CCScale9Sprite *pSprite = cocos2d::extension::CCScale9Sprite::create();  
	pSprite->setProperty("File",dd->filepath_);
	CCEditBox* cc=CCEditBox::create(CCSizeMake(dd->width_,dd->height_),pSprite);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setPriorityFromParent(false);
	cc->setPriority(dd->touchpriority_);
	cc->setFont(dd->fontname_,(int)dd->fontsize_);
	cc->setFontColor(ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}