#include "../include/ScaleSprite.h"

USING_NS_CC;

ScaleSprite* ScaleSprite::create(const char* filepath){
	ScaleSprite* cc=new ScaleSprite;
	if (cc&&cc->init(filepath))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool ScaleSprite::init(const char* filepath){
	if (CCSprite::init())
	{
		setProperty("File",filepath);
		return true;
	}
	return false;
}
