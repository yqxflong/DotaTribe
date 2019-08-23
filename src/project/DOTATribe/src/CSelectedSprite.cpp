//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: image + image =selSprite
//

#include "../include/CSelectedSprite.h"
#include "../include/CPublicVarReader.h"


USING_NS_CC;
USING_NS_CC_EXT;

//CSpriteSelected		-->CCSprite
CSpriteSelected* CSpriteSelected::create(const char* selFile,const char* norFile){
	CSpriteSelected* cc=new CSpriteSelected();
	if (cc&&cc->initWithFile(selFile,norFile))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CSpriteSelected::initWithFile(const char* selFile,const char* norFile){
	if (CCSprite::init())
	{
		setProperty("File",norFile);
		this->setAnchorPoint(CCPointZero);
		_createInnerImage(selFile);
		return true;
	}
	return false;
}
void CSpriteSelected::_createInnerImage(const char* selFile){
	CCSprite* cc=CCSprite::create();
	cc->setProperty("File",selFile);
	const CCSize &sz_sel=this->getContentSize();
	const CCSize &sz_nor=cc->getContentSize();
	cc->setAnchorPoint(CCPointZero);
	cc->setPosition(ccp((sz_sel.width-sz_nor.width)/2,(sz_sel.height-sz_nor.height)/2));
	this->addChild(cc);
}



//CSelectedSprite		-->CScale9Sprite
CSelectedSprite* CSelectedSprite::create(const char* selFile,const char* norFile,const CCSize& sz_sel,const CCSize& sz_nor){
	CSelectedSprite* cc=new CSelectedSprite();
	if (cc&&cc->initWithFile(selFile,norFile,sz_sel,sz_nor))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CSelectedSprite::initWithFile(const char* selFile,const char* norFile,const CCSize& sz_sel,const CCSize& sz_nor){
	if (CCScale9Sprite::init())
	{
		setProperty("File",selFile);
		this->setAnchorPoint(CCPointZero);
		this->setPreferredSize(sz_sel);
		_createInnerImage(norFile,sz_nor,sz_sel);
		return true;
	}
	return false;
}

void CSelectedSprite::_createInnerImage(const char* norFile,const CCSize& sz_nor,const CCSize& sz_sel){
	CCScale9Sprite* cc=CCScale9Sprite::create();
	cc->setProperty("File",norFile);
	cc->setAnchorPoint(CCPointZero);
	cc->setPreferredSize(sz_nor);
	cc->setPosition(ccp((sz_sel.width-sz_nor.width)/2,(sz_sel.height-sz_nor.height)/2));
	this->addChild(cc);
}

