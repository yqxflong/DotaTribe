//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: CCControlButton
//

#include "../include/CControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

CControlButton* CControlButton::create(CCNode* label, CCScale9Sprite* backgroundSprite){
	CControlButton* cc=new CControlButton();
	if (cc&&cc->initWithLabelAndBackgroundSprite(label,backgroundSprite))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CControlButton::initWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite){
	if (CCControlButton::initWithLabelAndBackgroundSprite(label,backgroundSprite))
	{
		return true;
	}
	return false;
}