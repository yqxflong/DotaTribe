//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: image + image =selSprite
//
//	 The Anchor must be 0,0
#ifndef  _DOTATRIBE_CSELECTSPRITE_H_
#define  _DOTATRIBE_CSELECTSPRITE_H_

#include "cocos2d.h"
#include <cocos-ext.h>

class CSpriteSelected:public cocos2d::CCSprite{
public:
	static CSpriteSelected* create(const char* selFile,const char* norFile);
	bool initWithFile(const char* selFile,const char* norFile);
protected:
	void _createInnerImage(const char* selFile);
};

class CSelectedSprite:public cocos2d::extension::CCScale9Sprite{
public:
	static CSelectedSprite* create(const char* selFile,const char* norFile,const cocos2d::CCSize &sz_sel,const cocos2d::CCSize &sz_nor);
	bool initWithFile(const char* selFile,const char* norFile,const cocos2d::CCSize &sz_sel,const cocos2d::CCSize &sz_nor);
protected:
	void _createInnerImage(const char* norFile,const cocos2d::CCSize& sz_nor,const cocos2d::CCSize& sz_sel);
};

#endif