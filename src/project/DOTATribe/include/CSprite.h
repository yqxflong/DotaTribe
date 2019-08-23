//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: A CCSprite but can save more imgs
//
#ifndef _CSPRITE_H_
#define _CSPRITE_H_

#include <cocos2d.h>
#include "../include/MaskNode.h"

/************************************************************************/
/*	                         CSprite                                    */
/************************************************************************/
class CSprite:public cocos2d::CCSprite{
private:
	std::string m_strFilePath1;
	std::string m_strFilePath2;
	std::string m_strFilePath3;
private:
	std::string m_nowShowFile;
public:
	static CSprite* create(const char* filepath);
	bool init(const char* filepath);
	//
	void setFilePath1(const char* fp){
		if (fp!=NULL&&strlen(fp)>0)
			m_strFilePath1=fp;
	}
	void setFilePath2(const char* fp){
		if (fp!=NULL&&strlen(fp)>0)
			m_strFilePath2=fp;
	}
	void setFilePath3(const char* fp){
		if (fp!=NULL&&strlen(fp)>0)
			m_strFilePath3=fp;
	}
	int getNowShowFileIndex()
	{
		if(m_nowShowFile == m_strFilePath1)
			return 1;
		if(m_nowShowFile == m_strFilePath2)
			return 2;
		if(m_nowShowFile == m_strFilePath3)
			return 3;

		return 1;
	}

	//change to image
	void changeToImage1();
	void changeToImage2();
	void changeToImage3();

	//check image existed
	bool hasImage1();
	bool hasImage2();
	bool hasImage3();
	
};




/************************************************************************/
/*	                         CTitleSprite                               */
/************************************************************************/
class CTitleSprite:public cocos2d::CCSprite{
private:
	cocos2d::CCLabelTTF* m_pLabel;
public:
	CTitleSprite();
	static CTitleSprite* create(const char* filepath,cocos2d::CCLabelTTF* label);
	bool init(const char* filepath,cocos2d::CCLabelTTF* label);
	//
	void SetLabelString(std::string text);
};


/************************************************************************/
/*	                         CSpriteInSprite                            */
/************************************************************************/
class CSpriteInSprite:public cocos2d::CCSprite{
private:
	cocos2d::CCSprite* m_pInnerSprite;
public:
	CSpriteInSprite();
	static CSpriteInSprite* create(const char* OutterFilePath,cocos2d::CCSprite* innerSprite);
	bool init(const char* OutterFilePath,cocos2d::CCSprite* innerSprite);
	//
	void ChangeInnerImage(const char* file);
	void ChangeOutterImage(const char* file);
};

#endif