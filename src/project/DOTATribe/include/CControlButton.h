//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: CCControlButton
//
#ifndef  _DOTATRIBE_CCONTROLBUTTON_H_
#define  _DOTATRIBE_CCONTROLBUTTON_H_

#include "cocos2d.h"
#include <cocos-ext.h>

class CControlButton:public cocos2d::extension::CCControlButton{
private:
	int m_nIDX;
public:
	CControlButton(){
		m_nIDX=0;
	};
	~CControlButton(){};
	static CControlButton* create(cocos2d::CCNode* label, cocos2d::extension::CCScale9Sprite* backgroundSprite);
	bool initWithLabelAndBackgroundSprite(cocos2d::CCNode* label, cocos2d::extension::CCScale9Sprite* backgroundSprite);
	//
	void setIDX(unsigned int idx){
		m_nIDX=idx;
	}
	unsigned int getIDX() const{
		return m_nIDX;
	}
};
#endif