#ifndef  _COCOS_CCGRAPSPRITE_H_
#define  _COCOS_CCGRAPSPRITE_H_
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  置灰精灵  
//date:   2013/12/09
///////////////////////////////////////////////// 

#include <cocos2d.h>
#include <string>
 
class  CCGrapSprite: public cocos2d::CCSprite
{
public:
	CCGrapSprite();
	virtual ~CCGrapSprite();
public:
	static CCGrapSprite* createGrapSpriteWithFileName(std::string pszFileName,bool isGrapSprite);
	static CCGrapSprite* createGrapSpriteWithFrameName(std::string frameNames,bool isGrapSprite);
	bool initWithTexture(cocos2d::CCTexture2D* texture, const cocos2d::CCRect&  rect);
	void draw();
	void initProgram();
	void listenBackToForeground(cocos2d::CCObject *obj);
	/*
	置灰 还原 开关
	*/
	void setGrapTexture(bool isGrapEnable);
	/*
	设置纹理 请使用此方法更新纹理 
	*/
	void setProperty(std::string nameType,std::string textureName,bool isGrapTexture=false);
protected:
	bool  initGrapSpriteWithFileName(std::string pszFileName,bool isGrapSprite);
	bool  initGrapSpriteWithFrameName(std::string frameName,bool isGrapSprite);
	void  updateInterTexture();
protected:
	bool  m_bIsGrapTexute;
	bool  m_bIsCreateWithFileName;
	std::string m_sFileName;
	std::string m_sFrameName;
};




#endif