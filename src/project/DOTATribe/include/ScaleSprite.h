//  Game:DotaTribe
//  Copyright fangjun. All rights reserved.
//  Writte By:fangjun

//ScaleSprite

#ifndef _SCALESPRITE_H_
#define _SCALESPRITE_H_

#include <cocos2d.h>

class ScaleSprite:public cocos2d::CCSprite{
public:
	static ScaleSprite* create(const char* filepath);
	bool init(const char* filepath);
};

#endif