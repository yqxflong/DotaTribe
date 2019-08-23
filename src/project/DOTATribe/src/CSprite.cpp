//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: A CCSprite but can save more imgs
//
#include "../include/CSprite.h"
#include "../include/UIViewDataManger.h"

USING_NS_CC;

CSprite* CSprite::create(const char* filepath){
	CSprite* cc=new CSprite;
	if (cc&&cc->init(filepath))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
	
bool CSprite::init(const char* filepath){
	if (CCSprite::init())
	{
		setProperty("File",filepath);
		return true;
	}
	return false;
}

void CSprite::changeToImage1(){
	assert(m_strFilePath1!="0");
	setProperty("File",m_strFilePath1);
}

void CSprite::changeToImage2(){
	assert(m_strFilePath2!="0");
	setProperty("File",m_strFilePath2);
}

void CSprite::changeToImage3(){
	assert(m_strFilePath3!="0");
	setProperty("File",m_strFilePath3);
}

//check image existed
//default is 0
bool CSprite::hasImage1(){
	return m_strFilePath1!="0";
}
bool CSprite::hasImage2(){
	return m_strFilePath2!="0";
}
bool CSprite::hasImage3(){
	return m_strFilePath3!="0";
}










/************************************************************************/
/*	                         CTitleSprite                               */
/************************************************************************/
CTitleSprite::CTitleSprite(){
	m_pLabel=NULL;
}

CTitleSprite* CTitleSprite::create(const char* filepath,cocos2d::CCLabelTTF* label){
	CTitleSprite* cc=new CTitleSprite();
	if (cc&&cc->init(filepath,label))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;cc=NULL;
	return cc;
}

bool CTitleSprite::init(const char* filepath,cocos2d::CCLabelTTF* label){
	if (!CCSprite::init())
		return false;



	setProperty("File",filepath);
	m_pLabel=label;
	m_pLabel->setAnchorPoint(ccp(0.5,0.5));
	m_pLabel->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	this->addChild(m_pLabel);
	return true;
}
	
//
void CTitleSprite::SetLabelString(std::string text){
	if (m_pLabel)
	{
		m_pLabel->setString(text.c_str());
	}
}



/************************************************************************/
/*	                         CSpriteInSprite                            */
/************************************************************************/
CSpriteInSprite::CSpriteInSprite(){
	m_pInnerSprite=NULL;
}

CSpriteInSprite* CSpriteInSprite::create(const char* OutterFilePath,cocos2d::CCSprite* innerSprite){
	CSpriteInSprite* cc=new CSpriteInSprite();
	if (cc&&cc->init(OutterFilePath,innerSprite))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;cc=NULL;
	return cc;
}

bool CSpriteInSprite::init(const char* OutterFilePath,cocos2d::CCSprite* innerSprite){
	if (!CCSprite::init())
		return false;

	this->setProperty("File",OutterFilePath);

	m_pInnerSprite=innerSprite;
	m_pInnerSprite->setAnchorPoint(ccp(0.5,0.5));
	m_pInnerSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	this->addChild(m_pInnerSprite);
	return true;
}
//
void CSpriteInSprite::ChangeInnerImage(const char* file){
	m_pInnerSprite->setProperty("File",file);
}

void CSpriteInSprite::ChangeOutterImage(const char* file){
	setProperty("File",file);
}