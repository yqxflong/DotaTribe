//Name: BlurSprite.h
//Function : 构建能够设置shader的精灵
//Author: Alkaid.FangJun
//Date: 2014-3-28

#ifndef _BLURSPRITE_H_
#define _BLURSPRITE_H_

#include <cocos2d.h>
#include <string>

using namespace cocos2d;

class BlurSprite : public CCSprite
{
private:
	CCPoint blur_;
	GLfloat sub_[4];
	GLuint blurLocation;
	GLuint subLocation;

	std::string fshFilePath;
public:
	BlurSprite();
	~BlurSprite();
public:
	void setBlurSize(float size);
	static BlurSprite * create(const char * pszFileName, std::string fshfilepath);
	bool initWithTexture(CCTexture2D * texture, const CCRect& rect);
	void draw();
	void initProgram();
	void listenBackToForeground(CCObject * obj);

};

#endif