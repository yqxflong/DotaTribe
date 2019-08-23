#ifndef   _DOTATRIBE_GRADUALCOLOR_H_
#define	  _DOTATRIBE_GRADUALCOLOR_H_

////////////////////////////////////////////////////////////////
//Name:	 GradualColorAction
//Auchor: 	xiaobo.wu
//Func:	 颜色RGBA特效渐变动画(支持变速控制)
//Maintainer: 	xiaobo.wu
//date:  2013/07/28
////////////////////////////////////////////////////////////////
  
#include   <cocos2d.h>

#define   WHITE_COLOR_NO_APHLE   255,255,255,255
#define   BLACK_COLOR_APHLE      0,0,0,0

using namespace cocos2d;

class GradualColorAction : public cocos2d::CCActionInterval
{
public: 
	bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue,GLubyte opacity);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);
	virtual void step(float dt);
	virtual void setSpeedScale(float speedScale);

public: 
	static GradualColorAction* create(float duration, GLubyte red, GLubyte green, GLubyte blue,GLubyte opacity);
protected:
	ccColor3B m_to;
	GLubyte  m_toOpacity;
	ccColor3B m_from;
	GLubyte  m_fromOpacity;
	float    m_fSpeedScale;
};

 
#endif


