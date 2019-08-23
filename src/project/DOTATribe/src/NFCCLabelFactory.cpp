//Name: NFCCLabelFactory
//Func: Used to Create CCLabel
//Written by: Johny

#include "../include/NFCCLabelFactory.h"
#include "../include/CTimeLabel.h"
#include "../include/NFControlsManager.h"

USING_NS_CC;

cocos2d::CCNode* NFCCLabelTTFFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	return NFC_createLabelByViewData(parentNode,*dd);
}

/*
	---->CCLabelTTF   Mutiline
*/
cocos2d::CCNode* NFCCLabelTTFMultilineFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	return NFC_createLabelMutilineByViewData(parentNode,*dd);
}



cocos2d::CCNode* NFCCTimeLabelFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{
	 CTimeLabel * pTimeLabel = CTimeLabel::CreateWithTimeType(dd->width_);
	 pTimeLabel->setFontName(dd->fontname_);
	 pTimeLabel->setFontSize(dd->fontsize_);
	 pTimeLabel->setTag(dd->idx_);
	 pTimeLabel->setTemplateStrTxtID(dd->touchpriority_);
	 bool isVisible=dd->hide_==0?true:false;
	 pTimeLabel->setVisible(isVisible);
	 pTimeLabel->setColor(ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
	 pTimeLabel->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	 pTimeLabel->setPosition(ccp(dd->posx_,dd->posy_));
	 parentNode->addChild(pTimeLabel,dd->zorder_);
	 return  pTimeLabel;
} 